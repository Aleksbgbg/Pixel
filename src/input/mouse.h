#ifndef SRC_INPUT_MOUSE_H_
#define SRC_INPUT_MOUSE_H_

#include "core/types.h"

enum class MouseButton {
  Left,
  Right,
};

class Mouse {
 public:
  virtual ~Mouse() = default;

  virtual bool IsButtonDown(MouseButton button) const = 0;
  virtual vec2i GetPosition() const = 0;
};

#endif  // SRC_INPUT_MOUSE_H_
