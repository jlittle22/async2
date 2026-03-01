
#include <chrono>
#include <cstdint>

#include "boot_time.h"
#include "pw_chrono/system_clock.h"

namespace pw::chrono::backend {

inline int64_t GetSystemClockTickCount() {
  return std::chrono::nanoseconds(std::chrono::high_resolution_clock().now() -
                                  jsnl::GetBootTime())
      .count();
}

}  // namespace pw::chrono::backend
