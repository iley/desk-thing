#ifndef _SCREEN_H
#define _SCREEN_H

#include <U8g2lib.h>

extern "C" uint8_t u8x8_byte_arduino_hw_spi_pico(u8x8_t *u8x8, uint8_t msg,
                                                 uint8_t arg_int,
                                                 void *arg_ptr);

// Override the hardware SPI callback to make use of the custom SPI configuration.
class U8G2_SSD1322_NHD_256X64_F_4W_HW_SPI_PICO : public U8G2 {
public:
  U8G2_SSD1322_NHD_256X64_F_4W_HW_SPI_PICO(const u8g2_cb_t *rotation,
                                           uint8_t cs, uint8_t dc,
                                           uint8_t reset = U8X8_PIN_NONE)
      : U8G2() {
    u8g2_Setup_ssd1322_nhd_256x64_f(&u8g2, rotation,
                                    u8x8_byte_arduino_hw_spi_pico,
                                    u8x8_gpio_and_delay_arduino);
    u8x8_SetPin_4Wire_HW_SPI(getU8x8(), cs, dc, reset);
  }
};

#endif // _SCREEN_H
