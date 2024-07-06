cmake_minimum_required(VERSION 3.13)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(vendor/pico-sdk/pico_sdk_init.cmake)

project(desk_thing)

pico_sdk_init()

add_compile_definitions(PICO_STDIO_USB_ENABLE_RESET_VIA_BAUD_RATE=1)

add_subdirectory(src)
add_subdirectory(vendor/u8g2)
