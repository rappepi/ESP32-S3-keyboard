#include "main.h"

SPIClass spi_bus(HSPI); //SPI3 voir https://github.com/espressif/arduino-esp32/issues/9588
Adafruit_LIS3DH accelerometer = Adafruit_LIS3DH(ACCELEROMETER_LATCH_PIN, &spi_bus, 1000000UL);

uint32_t last_frame_time;

USBHIDKeyboard keyboard;

CRGB leds[LED_COUNT];

typedef struct {
    uint32_t key_state;          //Key state after matrix scan
    uint32_t key_press_sent;      //Is the key press event sent
    uint32_t key_press_time;      //Last time the key had a key_state of 1
} keyboard_key_t;

keyboard_key_t keyboard_key_map[ROWS_COUNT][COLUMNS_COUNT] = {0};

// FAST LED I2S LED DRIVER
// https://github.com/FastLED/FastLED/blob/master/examples/Esp32S3I2SDemo/Esp32S3I2SDemo.h

void IRAM_ATTR update_encoder(){
    static bool encoder_clock_state, last_encoder_clock_state;
    encoder_clock_state = digitalRead(ENCODER_B_PIN);
    if(encoder_clock_state != last_encoder_clock_state){
        bool clock_wise = digitalRead(ENCODER_B_PIN) == encoder_clock_state;
    }
}

void IRAM_ATTR update_encoder_button(){
}

void select_column(uint8_t columns){
    uint32_t columns_mask = (uint32_t)1 << columns;
    FAST_WRITE_LOW(SHIFT_REGISTER_LATCH_PIN);
    //10Mhz is the max frequency usable because the signals are routed trought gpio matrix.
    //Any higher frequency like 20/40/80Mhz result in a unusable signal.
    spi_bus.transfer32(columns_mask);
    FAST_WRITE_HIGH(SHIFT_REGISTER_LATCH_PIN); 
    //Delay to let the signal settle. Without it will read last colums and not current one.
    for (uint8_t i = 0; i < 25; i++) {
        __asm__ __volatile__("nop");
    }
}

void enable_all_columns(){
    FAST_WRITE_LOW(SHIFT_REGISTER_LATCH_PIN);
    spi_bus.transfer32(0xFFFFFFFF);
    FAST_WRITE_HIGH(SHIFT_REGISTER_LATCH_PIN);     
    for (uint8_t i = 0; i < 25; i++) {
        __asm__ __volatile__("nop");
    }
}

void setup() {
    //Serial.begin(115200);
    //Implementer SERIAL pour envoyer commandes custom pour changer son spotify et windows via les potentiometres.
    //Possiblement mettre a jours le frameworks dans quelques jours https://github.com/espressif/arduino-esp32/issues/10307

    USB.begin();
    keyboard.begin();
    keyboard.pressRaw(KEY_NUMLOCK);

    attachInterrupt(ENCODER_A_PIN, update_encoder, CHANGE);
    attachInterrupt(ENCODER_B_PIN, update_encoder, CHANGE);
    attachInterrupt(ENCODER_BUTTON_PIN, update_encoder_button, FALLING);

    FastLED.addLeds<LED_TYPE, LED_PIN_1, GRB>(&leds[0],             LED_COUNT_1);
    FastLED.addLeds<LED_TYPE, LED_PIN_2, GRB>(&leds[LED_COUNT_1],   LED_COUNT_2);
    FastLED.setBrightness(DEFAULT_BRIGHTNESS);

    for(uint8_t i = 0; i < ARRAY_SIZE(rows_pin); i++) pinMode(rows_pin[i], INPUT);
    for (uint8_t i = 0; i < ARRAY_SIZE(input_pins); i++) pinMode(input_pins[i], INPUT);
    for (uint8_t i = 0; i < ARRAY_SIZE(output_pins); i++) pinMode(output_pins[i], OUTPUT);
    digitalWrite(ACCELEROMETER_LATCH_PIN, HIGH);
    digitalWrite(SHIFT_REGISTER_LATCH_PIN, HIGH);

    spi_bus.begin(SPI_CLOCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, -1);

    accelerometer.begin();
    accelerometer.setRange(LIS3DH_RANGE_2_G);

}


void update_keyboard_matrix() {

    spi_bus.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    enable_all_columns();    

    //Reset the current key_state of the keyboard_key_map
    for (uint8_t column = 0; column < COLUMNS_COUNT; column++) {
        for (uint8_t row = 0; row < ROWS_COUNT; row++) {
            keyboard_key_map[row][column].key_state = 0;
        }
    }

    //If no inputs return because the keyboard_key_map will remain at 0.
    uint32_t rows_inputs = GPIO.in & rows_mask;
    if(rows_inputs == 0){
        spi_bus.endTransaction();
        return;
    }
    
    uint32_t time = (uint32_t)(esp_timer_get_time() / (uint64_t)1000);

    for (uint8_t column = 0; column < COLUMNS_COUNT; column++) {
        select_column(column);
        rows_inputs = GPIO.in & rows_mask;

        for (uint8_t row = 0; row < ROWS_COUNT; row++) {

            //Check if the current row has is key pressed
            if((rows_inputs & ((uint32_t)1 << rows_pin[row])) != 0){
                keyboard_key_map[row][column].key_state = 1;
                keyboard_key_map[row][column].key_press_time = time;
            }
        }
    }
    spi_bus.endTransaction();
    return;
}

void release_key(uint8_t row, uint8_t column){
    keyboard.releaseRaw(keyboard_map[row][column]);
    return;
}
void press_key(uint8_t row, uint8_t column){
    keyboard.pressRaw(keyboard_map[row][column]);
    return;
}

/*
    Asym Eager Defer debouce algorithms.
    If key is pressed and was not previously pressed, it will immediately send the pressed USB key.
    If key is released it will need to wait for debounce time to send the release key.
*/
void update_usb_key_state(){
    uint32_t time = (uint32_t)(esp_timer_get_time() / (uint64_t)1000);
    for (uint8_t column = 0; column < COLUMNS_COUNT; column++) {
        for (uint8_t row = 0; row < ROWS_COUNT; row++) {

            //Go to the next iteration if the key is not pressed and no usb key press has been sent.
            //Used to avoid doing a lot of if statments for all the unpressed keys.
            if(keyboard_key_map[row][column].key_state == 0 && keyboard_key_map[row][column].key_press_sent == 0){
                continue;
            }

            //Check if key is pressed
            if(keyboard_key_map[row][column].key_state == 1 && keyboard_key_map[row][column].key_press_sent == 0){
                keyboard_key_map[row][column].key_press_sent = 1;
                press_key(row, column); // KeyboardMap[row][column] for keycode
                continue;
            }

            //Check if key is released
            if(keyboard_key_map[row][column].key_state == 0 && keyboard_key_map[row][column].key_press_sent == 1){
                //Check if debounce timeout has elapsed
                if(keyboard_key_map[row][column].key_press_time + DEBOUNCE_TIME_MS <= time){
                    release_key(row, column); // KeyboardMap[row][column] for keycode
                    keyboard_key_map[row][column].key_press_sent = 0;
                }
            }
        }
    }
    return;
}

void loop() {
    update_keyboard_matrix();
    update_usb_key_state();
    
    uint32_t time = (uint32_t)(esp_timer_get_time() / (uint64_t)1000);
    if (now - last_frame_time >= LED_FRAME_INTERVAL_MS) {
        color_wave(leds);
        FastLED.show();
        last_frame_time = time;
    }
}