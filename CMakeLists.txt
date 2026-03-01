cmake_minimum_required(VERSION 3.10)

project(Async2 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ENV{PW_ROOT} "${CMAKE_CURRENT_SOURCE_DIR}/pigweed")
include($ENV{PW_ROOT}/pw_build/pigweed.cmake)

add_subdirectory(backends)

include($ENV{PW_ROOT}/pw_assert/backend.cmake)
pw_set_backend(pw_assert.assert backends.pw_assert_check_backend)
pw_set_backend(pw_assert.check backends.pw_assert_check_backend)

include($ENV{PW_ROOT}/pw_chrono/backend.cmake)
pw_set_backend(pw_chrono.system_clock backends.pw_chrono_backend)

include($ENV{PW_ROOT}/pw_log/backend.cmake)
pw_set_backend(pw_log backends.pw_log_backend)

add_subdirectory(pigweed)


pw_add_library(boot_time STATIC
  HEADERS
    boot_time.h
  PUBLIC_INCLUDES
    ${CMAKE_SOURCE_DIR}
  SOURCES
    boot_time.cc
)

pw_add_library(root STATIC
  HEADERS
    root.h
  PUBLIC_INCLUDES
    ${CMAKE_SOURCE_DIR}
  SOURCES
    root.cc
  PRIVATE_DEPS
    boot_time
    pw_async2
    pw_async2.basic_dispatcher
    pw_async2.system_time_provider
    pw_log
)

add_executable(main main.cc)
target_link_libraries(main root)
