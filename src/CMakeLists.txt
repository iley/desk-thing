add_executable(desk_thing
    main.c
)

target_link_libraries(desk_thing
  pico_stdlib
  pico_bootsel_via_double_reset
)

pico_enable_stdio_usb(desk_thing 1)
pico_enable_stdio_uart(desk_thing 0)

pico_add_extra_outputs(desk_thing)
