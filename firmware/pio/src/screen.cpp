#include "screen.h"

#include <SPI.h>

#include "pins.h"

MbedSPI spi(kMISO, kMOSI, kSCK);

// Based on u8x8_byte_arduino_hw_spi() from U8x8lib.cpp.
extern "C" uint8_t u8x8_byte_arduino_hw_spi_pico(u8x8_t *u8x8, uint8_t msg,
                                                 uint8_t arg_int,
                                                 void *arg_ptr) {
  uint8_t *data;
  uint8_t internal_spi_mode;
 
  switch(msg) {
    case U8X8_MSG_BYTE_SEND:
      data = (uint8_t *)arg_ptr;
      while( arg_int > 0 )
      {
        spi.transfer((uint8_t)*data);
        data++;
        arg_int--;
      }
      break;

    case U8X8_MSG_BYTE_INIT:
      if ( u8x8->bus_clock == 0 ) {
        u8x8->bus_clock = u8x8->display_info->sck_clock_hz;
      }
      /* disable chipselect */
      u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
      spi.begin();
      break;
      
    case U8X8_MSG_BYTE_SET_DC:
      u8x8_gpio_SetDC(u8x8, arg_int);
      break;
      
    case U8X8_MSG_BYTE_START_TRANSFER:
      /* SPI mode has to be mapped to the mode of the current controller, at least Uno, Due, 101 have different SPI_MODEx values */
      internal_spi_mode =  0;
      switch(u8x8->display_info->spi_mode)
      {
        case 0: internal_spi_mode = SPI_MODE0; break;
        case 1: internal_spi_mode = SPI_MODE1; break;
        case 2: internal_spi_mode = SPI_MODE2; break;
        case 3: internal_spi_mode = SPI_MODE3; break;
      }
      
      spi.beginTransaction(SPISettings(u8x8->bus_clock, MSBFIRST, internal_spi_mode));
      
      u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level);  
      u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->post_chip_enable_wait_ns, NULL);
      break;
      
    case U8X8_MSG_BYTE_END_TRANSFER:      
      u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->pre_chip_disable_wait_ns, NULL);
      u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
      spi.endTransaction();
      break;

    default:
      return 0;
  }
  
  return 1;
}
