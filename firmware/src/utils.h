#ifndef utils_H
#define utils_H

//ONLY FOR GPIO < 32
#define FAST_WRITE_LOW(pin) (GPIO.out_w1tc = (uint32_t)1 << (pin))
#define FAST_WRITE_HIGH(pin) (GPIO.out_w1ts = (uint32_t)1 << (pin))

#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

#endif