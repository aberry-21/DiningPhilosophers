//
// Created by Aaron Berry on 5/19/21.
//

#include <iostream>
#include <thread>
#include "includes/philosophers.h"
#include "includes/config.h"

// Constructor
philosophers::philosophers(const std::shared_ptr<std::mutex> &right_fork,
                           const std::shared_ptr<std::mutex> &left_fork,
                           config *config, int id) :
                           right_fork_(right_fork), left_fork_(left_fork),
                           config_(config), id_(id) {
  count_eat_ = config_->IsLimitLunch() ? config_->GetNumberOfLunch() : 1;
}

// Move constructor
philosophers::philosophers(philosophers &&other) noexcept {
  std::swap(left_fork_, other.left_fork_);
  std::swap(right_fork_, other.right_fork_);
}

// Move operator
philosophers &philosophers::operator=(philosophers &&other) noexcept {
  if (this == &other) {
    return *this;
  }
  left_fork_ = right_fork_ = nullptr;
  std::swap(left_fork_, other.left_fork_);
  std::swap(right_fork_, other.right_fork_);
  return *this;
}

// The philosopher speaks from the fact that he took the fork
void philosophers::SayTaken() const noexcept {
  SaySomething("has taken a fork");
}

// The philosopher speaks from the fact that he began to eat
void philosophers::SayEating() noexcept {
  SaySomething("\x1b[32mis eating\x1b[0m");
  std::this_thread::sleep_for(
      std::chrono::milliseconds (config_->GetTimeToEat()));
  if (config_->IsLimitLunch()) {
    --count_eat_;
  }
}

// The philosopher speaks from the fact that he began to sleep
void philosophers::SaySleeping() const noexcept {
  SaySomething("is sleeping");
  std::this_thread::sleep_for(
      std::chrono::milliseconds (config_->GetTimeToSleep()));
}

// The philosopher speaks from the fact that he began to think
void philosophers::SayThinking() const noexcept {
  SaySomething("is thinking");
}

// The philosopher says he is dying
void philosophers::SayDied() const noexcept {
  config_->GetIoMutex().lock();
  std::cout << "["<< config_->GetTimer().GetTimeSimulation() << "]"
            << ' ' << id_ << ' ' << "died" <<std::endl;
}

// The life of a philosopher
void philosophers::PhiloLive() noexcept {
  if (id_ % 2) {
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
  }
  while(true) {
    SayThinking();
    {
      std::lock_guard<std::mutex> l_fork(*left_fork_);
      SayTaken();
      std::lock_guard<std::mutex> r_fork(*right_fork_);
      SayTaken();
      {
        std::unique_lock lock(mutex_eat_);
        time_last_eat = config_->GetTimer().GetTimeSimulation();
      }
      SayEating();
    }
    if (!count_eat_) {
      return;
    }
    SaySleeping();
    std::this_thread::yield();
  }
}

// Get the time of the last dinner of the philosopher
size_t philosophers::GetTimeLastEat() const {
  std::shared_lock lock(mutex_eat_);
  return time_last_eat;
}

// Get the number of philosopher's dinners
int philosophers::GetCountEat() const {
  return count_eat_;
}

//                            Private functions

// The philosopher speaks
void philosophers::SaySomething(const std::string &&str) const noexcept {
  std::lock_guard<std::mutex> lock(config_->GetIoMutex());
  std::cout << "["<< config_->GetTimer().GetTimeSimulation() << "]"
            << ' ' << id_ << ' ' << str <<std::endl;
}
