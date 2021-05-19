//
// Created by Aaron Berry on 5/19/21.
//

#pragma once

#include <memory>
#include <mutex>
#include "includes/Timer.h"

class Config {
 public:
  Config(int number_of_philo,
         int time_to_die,
         int time_to_eat,
         int time_to_sleep,
         int number_of_lunch);
  Config() = delete;
  Config(const Config& other) = delete;
  Config(Config&& other) noexcept = delete;
  Config& operator=(const Config& other) = delete;
  Config& operator=(Config&& other) noexcept = delete;
  [[nodiscard]] int GetNumberOfPhilo() const;
  [[nodiscard]] int GetTimeToDie() const;
  [[nodiscard]] int GetTimeToEat() const;
  [[nodiscard]] int GetTimeToSleep() const;
  [[nodiscard]] int GetNumberOfLunch() const;
  [[nodiscard]] std::mutex &GetIoMutex();
  [[nodiscard]] Timer &GetTimer();
  [[nodiscard]] bool IsLimitLunch() const;
 private:
  int number_of_philo_;
  int time_to_die_;
  int time_to_eat_;
  int time_to_sleep_;
  int number_of_lunch_;
  bool limit_lunch_;
  std::mutex io_mutex_;
  Timer timer_;
};
