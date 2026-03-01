#pragma once

#include "pw_chrono/epoch.h"

#define PW_CHRONO_SYSTEM_CLOCK_PERIOD_SECONDS_NUMERATOR 1
#define PW_CHRONO_SYSTEM_CLOCK_PERIOD_SECONDS_DENOMINATOR 1'000'000'000

namespace pw::chrono::backend {

constexpr pw::chrono::Epoch kSystemClockEpoch =
    pw::chrono::Epoch::kTimeSinceBoot;
constexpr bool kSystemClockFreeRunning = true;
constexpr bool kSystemClockNmiSafe = true;

}  // namespace pw::chrono::backend
