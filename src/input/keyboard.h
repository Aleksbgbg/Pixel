#ifndef SRC_INPUT_KEYBOARD_H_
#define SRC_INPUT_KEYBOARD_H_

#include <SDL.h>

class Keyboard {
 public:
  virtual ~Keyboard() = default;

  virtual bool KeyDown(SDL_Keycode keycode) const = 0;
  virtual bool KeyJustReleased(SDL_Keycode keycode) const = 0;
};

#endif  // SRC_INPUT_KEYBOARD_H_
