#include "run.h"

#include <SDL.h>

#include <cstring>
#include <vector>

#include "core/types.h"
#include "render.h"

namespace {

constexpr u32 kWidth = 1024;
constexpr u32 kHeight = 576;

constexpr u32 kPixelFormat = SDL_PIXELFORMAT_RGB24;
constexpr u32 kChannelsPerPixel = 3;  // RGB

constexpr u32 kTextureSizeBytes = kWidth * kHeight * kChannelsPerPixel;

}  // namespace

ExitCode Run() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return ExitCode::kGenericError;
  }

  SDL_Window* const window =
      SDL_CreateWindow("Pixel", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       kWidth, kHeight, SDL_WINDOW_RESIZABLE);

  if (window == nullptr) {
    SDL_Log("Unable to create window: %s", SDL_GetError());
    return ExitCode::kGenericError;
  }

  SDL_Renderer* const renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (renderer == nullptr) {
    SDL_Log("Unable to create renderer: %s", SDL_GetError());
    return ExitCode::kGenericError;
  }

  if (SDL_RenderSetLogicalSize(renderer, kWidth, kHeight) != 0) {
    SDL_Log("Unable to set logical render size: %s", SDL_GetError());
    return ExitCode::kGenericError;
  }

  SDL_Texture* texture = SDL_CreateTexture(
      renderer, kPixelFormat, SDL_TEXTUREACCESS_STREAMING, kWidth, kHeight);

  if (texture == nullptr) {
    SDL_Log("Unable to create texture: %s", SDL_GetError());
    return ExitCode::kGenericError;
  }

  std::vector<u8> pixels(kTextureSizeBytes);

  while (true) {
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
      switch (event.type) {
        case SDL_QUIT:
          return ExitCode::kOk;
      }
    }

    std::memset(pixels.data(), 0, kTextureSizeBytes);
    Render(pixels.data());

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
  }
}
