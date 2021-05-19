//
// Created by Aaron Berry on 5/19/21.
//

#pragma once
#include <chrono>

class Timer {
 public:
  typedef size_t size_type;

  Timer() = default;
  Timer(const Timer& other) = delete;
  Timer(Timer&& other) noexcept;
  Timer& operator=(const Timer& other) = delete;
  Timer& operator=(Timer&& other) noexcept;
  void StartSimulationTime() noexcept;
  size_type GetTimeSimulation() noexcept;
 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> time_start_;
};

