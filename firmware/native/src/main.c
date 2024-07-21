#include <stdio.h>

#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"

#include "display.h"
#include "sleep.h"

void draw(unsigned int offset) {
  static char *message = "Hello World!";

  u8g2_ClearBuffer(&u8g2);

  u8g2_SetFont(&u8g2, u8g2_font_spleen8x16_mf);
  u8g2_DrawStr(&u8g2, offset, 32, "Hello World!");
  // u8g2_DrawBox(&u8g2, 0, 0, offset, 64);

  u8g2_UpdateDisplay(&u8g2);
}

int main() {
  stdio_init_all();

  display_init();
  printf("Display initialized\n");

  unsigned int offset = 0;

  while (true) {
    draw(offset);
    offset = (offset + 1) % 256;
  }

  return 0;
}
