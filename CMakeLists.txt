cmake_minimum_required(VERSION 3.10)

project(Async2 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ENV{PW_ROOT} "${CMAKE_CURRENT_SOURCE_DIR}/pigweed")
include(toolchain.cmake)
include($ENV{PW_ROOT}/pw_build/pigweed.cmake)

add_subdirectory(pigweed)

pw_add_library(root STATIC
  HEADERS
    root.h
  PUBLIC_INCLUDES
    ${CMAKE_SOURCE_DIR}
  SOURCES
    root.cc
  PRIVATE_DEPS
    pw_async2
    pw_async2.basic_dispatcher
    pw_async2.system_time_provider
    pw_log
)

add_executable(main main.cc)
target_link_libraries(main root)
