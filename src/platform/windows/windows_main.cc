#include <Windows.h>

#include "run.h"

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE previousInstanceHandle,
                   PSTR commandLineParams, const int showCmd) {
  return static_cast<int>(Run());
}
