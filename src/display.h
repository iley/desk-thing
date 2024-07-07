#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <u8g2.h>

#define SPI_PORT spi0
// According to the datasheet, SSD1322's maximum SPI speed is 10 MHz.
#define SPI_SPEED (10 * 1e6)

#define PIN_SCK 2
#define PIN_MOSI 3
#define PIN_DC 4
#define PIN_RST 11
#define PIN_CS 5

extern u8g2_t u8g2;

void display_init();

#endif // _DISPLAY_H
