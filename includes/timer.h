//
// Created by Aaron Berry on 5/19/21.
//

#pragma once
#include <chrono>

class timer {
 public:
  typedef size_t size_type;

  timer() = default;
  timer(const timer& other) = delete;
  timer(timer&& other) noexcept;
  timer& operator=(const timer& other) = delete;
  timer& operator=(timer&& other) noexcept;
  void StartSimulationTime() noexcept;
  [[nodiscard]] size_type GetTimeSimulation() const noexcept;
 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> time_start_;
};

