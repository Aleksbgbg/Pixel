#ifndef SRC_INPUT_SDL_KEYBOARD_H_
#define SRC_INPUT_SDL_KEYBOARD_H_

#include <SDL.h>

#include <unordered_set>

#include "keyboard.h"

class SdlKeyboard : public Keyboard {
 public:
  bool KeyDown(SDL_Keycode keycode) const override;
  bool KeyJustReleased(SDL_Keycode keycode) const override;

  void ClearReleasedKeys();
  void ProcessEvent(const SDL_Event& event);

 private:
  std::unordered_set<SDL_Keycode> keys_down_;
  std::unordered_set<SDL_Keycode> keys_just_released_;
};

#endif  // SRC_INPUT_SDL_KEYBOARD_H_
