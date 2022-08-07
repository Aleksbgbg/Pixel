#include "run.h"

#include <SDL.h>

#include <chrono>
#include <cstring>
#include <vector>

#include "core/types.h"
#include "input/sdl_keyboard.h"
#include "input/sdl_mouse.h"
#include "render.h"

using default_clock = std::chrono::high_resolution_clock;
using time_point = std::chrono::time_point<default_clock>;

namespace {

constexpr u32 kWidth = 1024;
constexpr u32 kHeight = 576;

constexpr u32 kPixelFormat = SDL_PIXELFORMAT_RGB24;
constexpr u32 kChannelsPerPixel = 3;  // RGB

constexpr u32 kTextureSizeBytes = kWidth * kHeight * kChannelsPerPixel;

constexpr u32 kFps = 60;

float CalculateDeltaTimeSeconds(const time_point a, const time_point b) {
  return std::abs(
      std::chrono::duration<float, std::chrono::seconds::period>(a - b)
          .count());
}

}  // namespace

ExitCode Run() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return ExitCode::kGenericError;
  }

  SDL_Window* const window =
      SDL_CreateWindow("Pixel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       kWidth, kHeight, /* flags= */ 0);

  if (window == nullptr) {
    SDL_Log("Unable to create window: %s", SDL_GetError());
    return ExitCode::kGenericError;
  }

  SDL_Renderer* const renderer =
      SDL_CreateRenderer(window, /* index= */ -1,
                         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (renderer == nullptr) {
    SDL_Log("Unable to create renderer: %s", SDL_GetError());
    return ExitCode::kGenericError;
  }

  if (SDL_RenderSetLogicalSize(renderer, kWidth, kHeight) != 0) {
    SDL_Log("Unable to set logical render size: %s", SDL_GetError());
    return ExitCode::kGenericError;
  }

  SDL_Texture* const texture = SDL_CreateTexture(
      renderer, kPixelFormat, SDL_TEXTUREACCESS_STREAMING, kWidth, kHeight);

  if (texture == nullptr) {
    SDL_Log("Unable to create texture: %s", SDL_GetError());
    return ExitCode::kGenericError;
  }

  SdlKeyboard keyboard;
  SdlMouse mouse;

  std::vector<u8> pixels(kTextureSizeBytes);

  time_point last_time = default_clock::now();

  while (true) {
    keyboard.ClearReleasedKeys();
    mouse.ClearReleasedButtons();

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
          keyboard.ProcessEvent(event);
          break;

        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
          mouse.ProcessEvent(event);
          break;

        case SDL_QUIT:
          return ExitCode::kOk;
      }
    }

    std::memset(pixels.data(), 0, kTextureSizeBytes);

    const time_point now = default_clock::now();
    Render({.delta_time = CalculateDeltaTimeSeconds(now, last_time),
            .keyboard = keyboard,
            .mouse = mouse},
           pixels.data());
    last_time = now;

    int texture_pitch = 0;
    void* texture_pixels = nullptr;
    if (SDL_LockTexture(texture, /* rect= */ nullptr, &texture_pixels,
                        &texture_pitch) == 0) {
      std::memcpy(texture_pixels, pixels.data(), kTextureSizeBytes);
      SDL_UnlockTexture(texture);
    } else {
      SDL_Log("Unable to lock texture: %s", SDL_GetError());
    }

    if (SDL_RenderCopy(renderer, texture, /* srcrect= */ nullptr,
                       /* dstrect= */ nullptr) != 0) {
      SDL_Log("Unable to copy texture to render target: %s", SDL_GetError());
    }
    SDL_RenderPresent(renderer);

    SDL_Delay(1000 / kFps);
  }
}
