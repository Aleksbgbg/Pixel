#ifndef SRC_CORE_TYPES_H_
#define SRC_CORE_TYPES_H_

#include <cstdint>

using i8 = int8_t;
using u8 = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;

template <typename T>
struct vec2 {
  vec2() : x(static_cast<T>(0)), y(static_cast<T>(0)) {}
  vec2(const T x, const T y) : x(x), y(y) {}

  T x;
  T y;
};

using vec2f = vec2<float>;
using vec2i = vec2<i32>;
using vec2u = vec2<u32>;

#endif  // SRC_CORE_TYPES_H_
