#pragma once

#include <chrono>

namespace jsnl {

std::chrono::time_point<std::chrono::system_clock> GetBootTime();

}  // namespace jsnl
