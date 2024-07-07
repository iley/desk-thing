add_executable(desk_thing
    main.c
    display.c
    sleep.c
)

target_link_libraries(desk_thing
  pico_stdlib
  pico_bootsel_via_double_reset
  hardware_spi
  u8g2
)

pico_enable_stdio_usb(desk_thing 1)
pico_enable_stdio_uart(desk_thing 0)

pico_add_extra_outputs(desk_thing)
