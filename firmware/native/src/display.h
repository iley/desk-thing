#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <stdint.h>

#include <u8g2.h>

#define DISPLAY_WIDTH 256
#define DISPLAY_HEIGHT 64

#define DISPLAY_SPI_PORT spi0

extern u8g2_t u8g2;

void display_init();

#endif // _DISPLAY_H
