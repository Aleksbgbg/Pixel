set(SOURCE_FILES core/types.h run.cc run.h render.cc render.h UpdateContext.h)

if(LINUX)
  set(LINUX_SOURCE_FILES platform/linux/linux_main.cc)

  list(APPEND SOURCE_FILES ${LINUX_SOURCE_FILES})

  add_executable(${BINARY_NAME} ${SOURCE_FILES})
  target_link_libraries(${BINARY_NAME} PRIVATE SDL2::SDL2)
elseif(WINDOWS)
  set(WINDOWS_SOURCE_FILES platform/windows/windows_main.cc)

  list(APPEND SOURCE_FILES ${WINDOWS_SOURCE_FILES})

  add_executable(${BINARY_NAME} ${SOURCE_FILES})
  target_link_libraries(${BINARY_NAME} PRIVATE SDL2::SDL2-static)
elseif(MACOS)
  set(MACOS_SOURCE_FILES platform/macos/macos_main.cc)

  list(APPEND SOURCE_FILES ${MACOS_SOURCE_FILES})

  add_executable(${BINARY_NAME} ${MACOS_SOURCE_FILES})
  target_link_libraries(${BINARY_NAME} PRIVATE SDL2::SDL2)
endif()

target_include_directories(${BINARY_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${DEPENDENCIES_DIR}/sdl/include)
