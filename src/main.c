#include <stdio.h>

#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"

#include "display.h"

void draw(unsigned int offset) {
  u8g2_ClearBuffer(&u8g2);
  // u8g2_ClearDisplay(&u8g2);

  static char *message = "Hello World!";
  u8g2_DrawStr(&u8g2, 10, 10, message);
  u8g2_SetDrawColor(&u8g2, 1);

  u8g2_SetFont(&u8g2, u8g2_font_spleen8x16_mf);
  u8g2_FirstPage(&u8g2);
  do {
    u8g2_DrawStr(&u8g2, offset, 24, "Hello World!");
    // u8g2_SetDrawColor(&u8g2, 1);
    // u8g2_DrawBox(&u8g2, 0, 0, 256, 64);
  } while (u8g2_NextPage(&u8g2));

  u8g2_UpdateDisplay(&u8g2);
}

int main() {
  stdio_init_all();

  display_init();
  printf("Display initialized\n");

  unsigned int offset = 0;

  while(true) {
    draw(offset);
    sleep_ms(10);

    offset = (offset + 1) % 256;
  }

  return 0;
}
