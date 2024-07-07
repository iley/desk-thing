#ifndef _MATH_UTILS_H
#define _MATH_UTILS_H

inline uint64_t uint64_div_ceil(uint64_t a, uint64_t b) {
  return (a - 1) / b + 1;
}
inline uint32_t uint32_div_ceil(uint32_t a, uint32_t b) {
  return (a - 1) / b + 1;
}

#endif // _MATH_UTILS_H
