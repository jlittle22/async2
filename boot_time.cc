#include "boot_time.h"

#include <chrono>

namespace jsnl {

std::chrono::time_point<std::chrono::system_clock> GetBootTime() {
  static std::chrono::time_point<std::chrono::system_clock> boot_time =
      std::chrono::high_resolution_clock().now();
  return boot_time;
}

}  // namespace jsnl
