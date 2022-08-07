#ifndef SRC_INPUT_SDL_MOUSE_H_
#define SRC_INPUT_SDL_MOUSE_H_

#include <SDL.h>

#include <unordered_set>

#include "mouse.h"

class SdlMouse : public Mouse {
 public:
  bool ButtonDown(MouseButton button) const override;
  bool ButtonJustReleased(MouseButton button) const override;
  vec2i GetPosition() const override;

  void ClearReleasedButtons();
  void ProcessEvent(const SDL_Event& event);

 private:
  std::unordered_set<MouseButton> mouse_buttons_down_;
  std::unordered_set<MouseButton> mouse_buttons_just_released_;
  vec2i mouse_position_;
};

#endif  // SRC_INPUT_SDL_MOUSE_H_
