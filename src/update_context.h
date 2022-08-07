#ifndef SRC_UPDATE_CONTEXT_H_
#define SRC_UPDATE_CONTEXT_H_

#include "input/keyboard.h"
#include "input/mouse.h"

struct UpdateContext {
  float delta_time;

  const Keyboard& keyboard;
  const Mouse& mouse;
};

#endif  // SRC_UPDATE_CONTEXT_H_
