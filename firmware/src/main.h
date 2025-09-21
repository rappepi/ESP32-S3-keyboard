#ifndef main_H
#define main_H
#include <SPI.h>
/*  USB HID  */
#include <USB.h>
#include <USBHIDKeyboard.h>
/*  Accelerometer  */
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
/*  Direct gpio access  */
#include "soc/gpio_struct.h"
/*  Commons functions  */
#include "utils.h"
/*  Keyboard  */
#include "keyboard_matrix_config.h"
#include "led_matrix_config.h"
/*  Led animation effects  */
#include <FastLED.h>
#include "led_animation/color_wave.h"

/*  SPI pin */
#define SPI_CLOCK_PIN     15
#define SPI_MOSI_PIN      16
#define SPI_MISO_PIN      6

/*  Accelerometer   */
#define ACCELEROMETER_LATCH_PIN         5
#define ACCELEROMETER_CLOCK_PIN         SPIClockPin
#define ACCELEROMETER_MOSI_PIN          SPIMOSIPin
#define ACCELEROMETER_MISO_PIN          SPIMISOPin
#define ACCELEROMETER_INTERRUPT_PIN     4
#define ACCELEROMETER_FREQUENCY         10000000

/*  Shift register  */
#define SHIFT_REGISTER_LATCH_PIN    7
#define SHIFT_REGISTER_DATA_PIN     SPIMOSIPin
#define SHIFT_REGISTER_CLOCK_PIN    SPIClockPin
#define SHIFT_REGISTER_FREQUENCY    10000000

/*  Rotary encoder  */
#define ENCODER_A_PIN           40
#define ENCODER_B_PIN           39      
#define ENCODER_BUTTON_PIN      38 

/*  Potentiometer pin  */
#define POTENTIOMETER_1_PIN     10
#define POTENTIOMETER_2_PIN     9

const uint8_t output_pins[] = {ACCELEROMETER_LATCH_PIN, SHIFT_REGISTER_LATCH_PIN};

const uint8_t input_pins[] = {ACCELEROMETER_INTERRUPT_PIN, ENCODER_A_PIN, ENCODER_B_PIN, ENCODER_BUTTON_PIN, POTENTIOMETER_1_PIN, POTENTIOMETER_2_PIN};

#endif