#pragma once

#include <exception>
#include <iostream>

#define PW_ASSERT_HANDLE_FAILURE(condition_string)                   \
  do {                                                               \
    std::cerr << "Assert failed: " << condition_string << std::endl; \
    std::terminate();                                                \
  } while (0)
