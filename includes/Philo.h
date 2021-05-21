//
// Created by Aaron Berry on 5/19/21.
//

#pragma once

#include <memory>
#include <mutex>
#include <shared_mutex>
#include "includes/Config.h"

class Philo {
 public:
  Philo() = default;
  Philo(const std::shared_ptr<std::mutex> &right_fork,
        const std::shared_ptr<std::mutex> &left_fork,
        Config *config,
        int id);
  Philo(const Philo& other) = delete;
  Philo(Philo&& other) noexcept;
  Philo& operator=(const Philo& other) = delete;
  Philo& operator=(Philo&& other) noexcept;

  void SayTaken() const noexcept;
  void SayEating() noexcept;
  void SaySleeping() const noexcept;
  void SayDied() const noexcept;
  void SayThinking() const noexcept;
  [[nodiscard]] size_t GetTimeLastEat() const;
  [[nodiscard]] int GetCountEat() const;
  void PhiloLive() noexcept;
 private:
  std::shared_ptr<std::mutex> right_fork_ = nullptr;
  std::shared_ptr<std::mutex> left_fork_ = nullptr;
  mutable std::shared_mutex mutex_eat_;
  Config *config_ = nullptr;
  int id_ = 0;
  int count_eat_ = 0;
  size_t time_last_eat = 0;

  inline void SaySomething(const std::string&& str) const noexcept;
};
