#include "sleep.h"

#include "pico/platform.h"
#include "hardware/clocks.h"

#include "math_utils.h"

void sleep_ns(uint64_t ns) {
  busy_wait_at_least_cycles(uint64_div_ceil(ns * clock_get_hz(clk_sys), 1e9));
}
