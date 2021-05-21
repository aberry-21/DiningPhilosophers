//
// Created by Aaron Berry on 5/19/21.
//

#include "includes/timer.h"

timer::timer(timer &&other) noexcept : time_start_() {
  std::swap(time_start_, other.time_start_);
}

timer &timer::operator=(timer &&other) noexcept {
  if (this == &other) {
    return *this;
  }
  std::swap(time_start_, other.time_start_);
  return *this;
}

void timer::StartSimulationTime() noexcept {
  time_start_ = std::chrono::high_resolution_clock::now();
}

timer::size_type timer::GetTimeSimulation() const noexcept {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now() - time_start_).count();
}
