#pragma once

#include <exception>
#include <iostream>

#define PW_HANDLE_CRASH(...)                            \
  do {                                                  \
    std::cerr << "Crash: " << __VA_ARGS__ << std::endl; \
    std::terminate();                                   \
  } while (0)

#define PW_HANDLE_ASSERT_FAILURE(condition_string, ...)             \
  do {                                                              \
    std::cerr << "Check failed: " condition_string ". " __VA_ARGS__ \
              << std::endl;                                         \
    std::terminate();                                               \
  } while (0)

#define PW_HANDLE_ASSERT_BINARY_COMPARE_FAILURE(                             \
    arg_a_str, arg_a_val, comparison_op_str, arg_b_str, arg_b_val, type_fmt, \
    message, ...)                                                            \
  do {                                                                       \
    std::cerr << "Check failed: " arg_a_str " (=" type_fmt                   \
                 ") " comparison_op_str " " arg_b_str " (=" type_fmt         \
                 ")"                                                         \
                 ". " message,                                               \
        PW_DROP_LAST_ARG_IF_EMPTY(arg_a_val, arg_b_val, __VA_ARGS__)         \
            << std::endl;                                                    \
    std::terminate();                                                        \
  } while (0)
