//
// Created by Aaron Berry on 5/19/21.
//

#include "includes/Timer.h"

Timer::Timer(Timer &&other) noexcept : time_start_() {
  std::swap(time_start_, other.time_start_);
}

Timer &Timer::operator=(Timer &&other) noexcept {
  if (this == &other) {
    return *this;
  }
  std::swap(time_start_, other.time_start_);
  return *this;
}

void Timer::StartSimulationTime() noexcept {
  time_start_ = std::chrono::high_resolution_clock::now();
}

Timer::size_type Timer::GetTimeSimulation() const noexcept {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now() - time_start_).count();
}
