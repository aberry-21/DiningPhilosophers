//
// Created by Aaron Berry on 5/19/21.
//

#pragma once

#include <memory>
#include <mutex>
#include "includes/timer.h"

class config {
 public:
  config(int number_of_philo,
         int time_to_die,
         int time_to_eat,
         int time_to_sleep,
         int number_of_lunch);
  config() = delete;
  config(const config& other) = delete;
  config(config&& other) noexcept = delete;
  config& operator=(const config& other) = delete;
  config& operator=(config&& other) noexcept = delete;
  [[nodiscard]] int GetNumberOfPhilo() const;
  [[nodiscard]] int GetTimeToDie() const;
  [[nodiscard]] int GetTimeToEat() const;
  [[nodiscard]] int GetTimeToSleep() const;
  [[nodiscard]] int GetNumberOfLunch() const;
  [[nodiscard]] std::mutex &GetIoMutex();
  [[nodiscard]] timer &GetTimer();
  [[nodiscard]] bool IsLimitLunch() const;
 private:
  int number_of_philo_;
  int time_to_die_;
  int time_to_eat_;
  int time_to_sleep_;
  int number_of_lunch_;
  bool limit_lunch_;
  std::mutex io_mutex_;
  timer timer_;
};
