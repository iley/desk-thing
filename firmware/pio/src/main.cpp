#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>
#include <Wire.h>

#include "screen.h"
#include "pins.h"

// Software SPI configuration that works.
// U8G2_SSD1322_NHD_256X64_F_4W_SW_SPI u8g2(U8G2_R0, /*SCLK=*/2, /* MOSI=*/3, /*CS=*/5, /*DC=*/4, /*RST=*/11);

U8G2_SSD1322_NHD_256X64_F_4W_HW_SPI_PICO u8g2(U8G2_R0, kCS, kDC, kRST);

constexpr int kWidth = 256;
constexpr int kHeight = 64;

int offset = 0;

void setup(void) {
  Serial.begin(115200);

  u8g2.begin();
}

void draw() {
  // u8g2.drawBox(0, 0, 128, 16);
  u8g2.setFont(u8g2_font_spleen8x16_mf);
  u8g2.drawStr(offset, 32, "Hello World!");

  offset = (offset + 1) % kWidth;
}

void loop(void) {
  u8g2.clearBuffer();
  draw();
  u8g2.sendBuffer();
}
