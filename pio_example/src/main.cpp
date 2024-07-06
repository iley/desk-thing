#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>
#include <Wire.h>

// Make sure to define U8G2_16BIT.
// U8G2_SSD1322_NHD_256X64_1_4W_SW_SPI u8g2(U8G2_R0, /*SCLK=*/18, /* MOSI=*/19, /*CS=*/16, /*DC=*/15, /*RST=*/14);
U8G2_SSD1322_NHD_256X64_1_4W_HW_SPI u8g2(U8G2_R0, /*CS=*/16, /*DC=*/15, /*RST=*/14);

void setup(void) {
  Serial.begin(115200);
  SPI.begin();
  u8g2.begin();
}

void loop(void) {
  u8g2.firstPage();
  do {
    // u8g2.drawBox(0, 0, 128, 16);
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(0, 24, "Hello World!");
  } while (u8g2.nextPage());

  Serial.print("MOSI: ");
  Serial.println(MOSI);
  Serial.print("MISO: ");
  Serial.println(MISO);
  Serial.print(" SCK: ");
  Serial.println(SCK);
  Serial.print("  SS: ");
  Serial.println(SS);
  Serial.println();

  delay(1000);
}
