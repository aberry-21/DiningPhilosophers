//
// Created by Aaron Berry on 5/19/21.
//

#pragma once

#include <memory>
#include <mutex>
#include "includes/Config.h"

class Philo {
 public:
  Philo() = default;
  Philo(const Philo& other) = delete;
  Philo(Philo&& other) noexcept;
  Philo& operator=(const Philo& other) = delete;
  Philo& operator=(Philo&& other) noexcept;

  void SetPhiloAttributes(Config *config, int id);
  void SayTaken() const noexcept;
  void SayEating() const noexcept;
  void SaySleeping() const noexcept;
  void SayThinking() const noexcept;
  void PhiloLive() noexcept;
  void SetRightFork(const std::shared_ptr<std::mutex> &right_fork);
  void SetLeftFork(const std::shared_ptr<std::mutex> &left_fork);
 private:
  std::shared_ptr<std::mutex> right_fork_ = nullptr;
  std::shared_ptr<std::mutex> left_fork_ = nullptr;
  Config *config_ = nullptr;
  int id_ = 0;
  int count_eat_ = 0;

  inline void SaySomething(const std::string&& str) const noexcept;
};
