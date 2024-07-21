#include "display.h"

#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"

#include <u8g2.h>

#include "sleep.h"

// According to the datasheet, SSD1322's maximum SPI speed is 10 MHz.
static const unsigned int kSpiSpeed = 10 * 1e6;

static const unsigned int kPinSCK = 2;
static const unsigned int kPinMOSI = 3;
static const unsigned int kPinDC = 4;
static const unsigned int kPinRST = 11;
static const unsigned int kPinCS = 5;

u8g2_t u8g2;

// Based on code by @nordseele (https://github.com/olikraus/u8g2/issues/2159)
static uint8_t u8x8_byte_pico_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,
                              void *arg_ptr) {
  uint8_t *data;
  switch (msg) {
  case U8X8_MSG_BYTE_SEND:
    data = (uint8_t *)arg_ptr;
    spi_write_blocking(DISPLAY_SPI_PORT, data, arg_int);
    break;
  case U8X8_MSG_BYTE_INIT:
    u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
    break;
  case U8X8_MSG_BYTE_SET_DC:
    u8x8_gpio_SetDC(u8x8, arg_int);
    break;
  case U8X8_MSG_BYTE_START_TRANSFER:
    u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level);
    u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO,
                            u8x8->display_info->post_chip_enable_wait_ns, NULL);
    break;
  case U8X8_MSG_BYTE_END_TRANSFER:
    u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO,
                            u8x8->display_info->pre_chip_disable_wait_ns, NULL);
    u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
    break;
  default:
    return 0;
  }
  return 1;
}

static uint8_t u8x8_gpio_and_delay_pico(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,
                                 void *arg_ptr) {
  switch (msg) {
  case U8X8_MSG_GPIO_AND_DELAY_INIT:
    spi_init(DISPLAY_SPI_PORT, kSpiSpeed);
    gpio_set_function(kPinCS, GPIO_FUNC_SIO);
    gpio_set_function(kPinSCK, GPIO_FUNC_SPI);
    gpio_set_function(kPinMOSI, GPIO_FUNC_SPI);
    gpio_init(kPinRST);
    gpio_init(kPinDC);
    gpio_init(kPinCS);
    gpio_set_dir(kPinRST, GPIO_OUT);
    gpio_set_dir(kPinDC, GPIO_OUT);
    gpio_set_dir(kPinCS, GPIO_OUT);
    gpio_put(kPinRST, 1);
    gpio_put(kPinCS, 1);
    gpio_put(kPinDC, 0);
    break;
  case U8X8_MSG_DELAY_NANO: { // delay arg_int * 1 nano second
    sleep_ns(arg_int);
    break;
  }
  case U8X8_MSG_DELAY_100NANO: { // delay arg_int * 100 nano seconds
    sleep_ns(arg_int * 100);
    break;
  }
  case U8X8_MSG_DELAY_10MICRO: // delay arg_int * 10 micro seconds
    sleep_us(arg_int * 10);
    break;
  case U8X8_MSG_DELAY_MILLI: // delay arg_int * 1 milli second
    sleep_ms(arg_int);
    break;
  case U8X8_MSG_GPIO_CS: // CS (chip select) pin: Output level in arg_int
    gpio_put(kPinCS, arg_int);
    break;
  case U8X8_MSG_GPIO_DC: // DC (data/cmd, A0, register select) pin: Output level
    gpio_put(kPinDC, arg_int);
    break;
  case U8X8_MSG_GPIO_RESET:     // Reset pin: Output level in arg_int
    gpio_put(kPinRST, arg_int); // printf("U8X8_MSG_GPIO_RESET %d\n", arg_int);
    break;
  default:
    u8x8_SetGPIOResult(u8x8, 1); // default return value
    break;
  }
  return 1;
}

void display_init() {
  u8g2_Setup_ssd1322_nhd_256x64_f(&u8g2, U8G2_R0, u8x8_byte_pico_hw_spi,
                                  u8x8_gpio_and_delay_pico);
  u8g2_InitDisplay(&u8g2); // Send init sequence to the display. Display is in
                           // sleep mode after this.
  u8g2_SetPowerSave(&u8g2, 0);
}
