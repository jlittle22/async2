#pragma once

#include <iostream>

// Helper to convert level integers to strings for display
inline const char* _pw_log_level_name(int level) {
  switch (level) {
    case 1:
      return "DEBUG";
    case 2:
      return "INFO";
    case 3:
      return "WARN";
    case 4:
      return "ERROR";
    case 5:
      return "CRITICAL";
    default:
      return "LOG";
  }
}

// The core PW_LOG macro
// Note: We use a 'do { ... } while(0)' block to make the macro
// safe for use in if/else statements without braces.
#define PW_LOG(level, verbosity, module, flags, fmt, ...)                   \
  do {                                                                      \
    if (level >= verbosity) {                                               \
      std::cout << "[" << _pw_log_level_name(level) << "] "                 \
                << "[" << module << "] "                                    \
                << (flags != 0 ? "[F:" + std::to_string(flags) + "] " : "") \
                << fmt << std::endl;                                        \
    }                                                                       \
  } while (0)

// Optional: Specific level overrides for cleaner syntax
#define PW_LOG_DEBUG(fmt, ...) \
  PW_LOG(1, PW_LOG_LEVEL, PW_LOG_MODULE_NAME, 0, fmt, ##__VA_ARGS__)

#define PW_LOG_INFO(fmt, ...) \
  PW_LOG(2, PW_LOG_LEVEL, PW_LOG_MODULE_NAME, 0, fmt, ##__VA_ARGS__)

#define PW_LOG_WARN(fmt, ...) \
  PW_LOG(3, PW_LOG_LEVEL, PW_LOG_MODULE_NAME, 0, fmt, ##__VA_ARGS__)

#define PW_LOG_ERROR(fmt, ...) \
  PW_LOG(4, PW_LOG_LEVEL, PW_LOG_MODULE_NAME, 0, fmt, ##__VA_ARGS__)

#define PW_LOG_CRITICAL(fmt, ...) \
  PW_LOG(5, PW_LOG_LEVEL, PW_LOG_MODULE_NAME, 0, fmt, ##__VA_ARGS__)
