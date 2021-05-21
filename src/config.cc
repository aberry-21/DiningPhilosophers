//
// Created by Aaron Berry on 5/19/21.
//

#include "includes/config.h"

config::config(int number_of_philo, int time_to_die, int time_to_eat,
               int time_to_sleep, int number_of_lunch) :
               number_of_philo_(number_of_philo), time_to_die_(time_to_die),
               time_to_eat_(time_to_eat), time_to_sleep_(time_to_sleep),
               number_of_lunch_(number_of_lunch) {
  if (number_of_lunch > 0) {
    limit_lunch_ = true;
  }
}

int config::GetNumberOfPhilo() const {
  return number_of_philo_;
}

int config::GetTimeToDie() const {
  return time_to_die_;
}

int config::GetTimeToEat() const {
  return time_to_eat_;
}

int config::GetTimeToSleep() const {
  return time_to_sleep_;
}

int config::GetNumberOfLunch() const {
  return number_of_lunch_;
}

std::mutex &config::GetIoMutex(){
  return io_mutex_;
}

timer &config::GetTimer(){
  return timer_;
}

bool config::IsLimitLunch() const {
  return limit_lunch_;
}
