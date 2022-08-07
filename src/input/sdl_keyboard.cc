#include "sdl_keyboard.h"

bool SdlKeyboard::KeyDown(const SDL_Keycode keycode) const {
  return keys_down_.contains(keycode);
}

bool SdlKeyboard::KeyJustReleased(const SDL_Keycode keycode) const {
  return keys_just_released_.contains(keycode);
}

void SdlKeyboard::ClearReleasedKeys() {
  keys_just_released_.clear();
}

void SdlKeyboard::ProcessEvent(const SDL_Event& event) {
  if (event.type == SDL_KEYDOWN) {
    keys_down_.insert(event.key.keysym.sym);
  } else if (event.type == SDL_KEYUP) {
    keys_down_.erase(event.key.keysym.sym);
    keys_just_released_.insert(event.key.keysym.sym);
  }
}
