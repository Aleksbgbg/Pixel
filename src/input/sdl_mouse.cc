#include "sdl_mouse.h"

#include <SDL.h>

bool SdlMouse::ButtonDown(MouseButton button) const {
  return mouse_buttons_down_.contains(button);
}

bool SdlMouse::ButtonJustReleased(MouseButton button) const {
  return mouse_buttons_just_released_.contains(button);
}

vec2i SdlMouse::GetPosition() const {
  return mouse_position_;
}

void SdlMouse::ClearReleasedButtons() {
  mouse_buttons_just_released_.clear();
}

void SdlMouse::ProcessEvent(const SDL_Event& event) {
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      mouse_buttons_down_.insert(MouseButton::Left);
    } else if (event.button.button == SDL_BUTTON_RIGHT) {
      mouse_buttons_down_.insert(MouseButton::Right);
    }
  } else if (event.type == SDL_MOUSEBUTTONUP) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      mouse_buttons_down_.erase(MouseButton::Left);
      mouse_buttons_just_released_.insert(MouseButton::Left);
    } else if (event.button.button == SDL_BUTTON_RIGHT) {
      mouse_buttons_down_.erase(MouseButton::Right);
      mouse_buttons_just_released_.insert(MouseButton::Right);
    }
  } else if (event.type == SDL_MOUSEMOTION) {
    mouse_position_ = vec2i(event.motion.x, event.motion.y);
  }
}
