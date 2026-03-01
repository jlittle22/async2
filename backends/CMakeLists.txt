include($ENV{PW_ROOT}/pw_build/pigweed.cmake)
# Do I really need this include?
include($ENV{PW_ROOT}/pw_assert/backend.cmake)

pw_add_library(backends.pw_assert_check_backend INTERFACE
  HEADERS
    pw_assert_backend/assert_backend.h
    pw_assert_backend/check_backend.h
  PUBLIC_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

pw_add_library(backends.pw_chrono_backend STATIC
  HEADERS
    pw_chrono_backend/system_clock_config.h
  PUBLIC_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/
  PUBLIC_DEPS
    pw_chrono.epoch
  SOURCES
    steady_clock.cc
  PRIVATE_DEPS
    boot_time
    pw_chrono.system_clock.facade
)

pw_add_library(backends.pw_log_backend INTERFACE
  HEADERS
    pw_log_backend/log_backend.h
  PUBLIC_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/
)
