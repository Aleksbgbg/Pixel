#ifndef SRC_INPUT_SDL_MOUSE_H_
#define SRC_INPUT_SDL_MOUSE_H_

#include <SDL.h>

#include <unordered_set>

#include "mouse.h"

class SdlMouse : public Mouse {
 public:
  bool IsButtonDown(MouseButton button) const override;
  vec2i GetPosition() const override;

  void ProcessEvent(const SDL_Event& event);

 private:
  std::unordered_set<MouseButton> mouse_buttons_down_;
  vec2i mouse_position_;
};

#endif  // SRC_INPUT_SDL_MOUSE_H_
