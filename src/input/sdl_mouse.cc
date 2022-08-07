#include "sdl_mouse.h"

#include <SDL.h>

bool SdlMouse::IsButtonDown(const MouseButton button) const {
  return mouse_buttons_down_.contains(button);
}

vec2i SdlMouse::GetPosition() const {
  return mouse_position_;
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
    } else if (event.button.button == SDL_BUTTON_RIGHT) {
      mouse_buttons_down_.erase(MouseButton::Right);
    }
  } else if (event.type == SDL_MOUSEMOTION) {
    mouse_position_ = vec2i(event.motion.x, event.motion.y);
  }
}
