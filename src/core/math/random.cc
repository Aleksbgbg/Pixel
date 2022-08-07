#include "random.h"

#include <random>

#include "core/types.h"

i32 RandomIntegerInRange(const i32 start, const i32 end) {
  static std::mt19937 random_engine(std::random_device{}());
  std::uniform_int_distribution distribution(start, end);
  return distribution(random_engine);
}

u8 RandomByte() {
  return static_cast<u8>(RandomIntegerInRange(0, 255));
}
