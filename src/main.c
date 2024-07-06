#include <stdio.h>

#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"

#include "display.h"

void draw() {
  u8g2_ClearBuffer(&u8g2);
  u8g2_ClearDisplay(&u8g2);

  /*
  static char *message = "Hello World!";
  u8g2_DrawStr(&u8g2, 10, 10, message);
  u8g2_SetDrawColor(&u8g2, 1);
  */
  u8g2_DrawBox(&u8g2, 0, 0, 256, 64);

  u8g2_UpdateDisplay(&u8g2);
}

int main() {
  stdio_init_all();

  display_init();
  printf("Display initialized\n");

  draw();

  while(true) {
    sleep_ms(1000);
  }

  return 0;
}
