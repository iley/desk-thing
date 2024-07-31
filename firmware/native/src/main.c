#include <stdio.h>

#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"

#include "display.h"
#include "sleep.h"

#define ROWS 8
#define ROW_WIDTH 8

void draw() {
  static char *message = "Hello World!";
  static unsigned int offsets[ROWS] = {0};

  u8g2_ClearBuffer(&u8g2);

  // u8g2_SetFont(&u8g2, u8g2_font_spleen8x16_mf);
  u8g2_SetFont(&u8g2, u8g2_font_amstrad_cpc_extended_8f);
  for (int i = 0; i < ROWS; i++) {
    u8g2_DrawStr(&u8g2, offsets[i], ROW_WIDTH * (i + 1), "Hello World!");
    offsets[i] = (offsets[i] + i % 3 + 1) % 256;
  }

  u8g2_SendBuffer(&u8g2);
}

int main() {
  stdio_init_all();

  display_init();

  while (true) {
    draw();
  }

  return 0;
}
