cmake_minimum_required(VERSION 3.20)
project(pixel)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SYSTEM_NAME STREQUAL Linux)
  set(LINUX TRUE)
elseif(CMAKE_SYSTEM_NAME STREQUAL Windows)
  set(WINDOWS TRUE)
elseif(CMAKE_SYSTEM_NAME STREQUAL Darwin)
  set(MACOS TRUE)
endif()

set(BINARY_NAME ${CMAKE_PROJECT_NAME})

set(DEPENDENCIES_DIR ${CMAKE_SOURCE_DIR}/dependencies)

add_subdirectory(${DEPENDENCIES_DIR}/sdl)

add_subdirectory(src)
