//
// Created by Aaron Berry on 5/19/21.
//

#include <iostream>
#include <thread>
#include "includes/Philo.h"
#include "includes/Config.h"

Philo::Philo(Philo &&other) noexcept {
  std::swap(left_fork_, other.left_fork_);
  std::swap(right_fork_, other.right_fork_);
}
Philo &Philo::operator=(Philo &&other) noexcept {
  if (this == &other) {
    return *this;
  }
  left_fork_ = right_fork_ = nullptr;
  std::swap(left_fork_, other.left_fork_);
  std::swap(right_fork_, other.right_fork_);
  return *this;
}

void Philo::SaySomething(const std::string &&str) const noexcept {
  std::lock_guard<std::mutex> lock(config_->GetIoMutex());
  std::cout << "["<< config_->GetTimer().GetTimeSimulation() << "]"
            << ' ' << id_ << ' ' << str <<std::endl;
}

void Philo::SayTaken() const noexcept {
  SaySomething("has taken a fork");
}

void Philo::SayEating() const noexcept {
  SaySomething("is eating");
  std::this_thread::sleep_for(
      std::chrono::milliseconds (config_->GetTimeToSleep()));
}

void Philo::SaySleeping() const noexcept {
  SaySomething("is sleeping");
  std::this_thread::sleep_for(
      std::chrono::milliseconds (config_->GetTimeToSleep()));
}

void Philo::SayThinking() const noexcept {
  SaySomething("is thinking");
}

void Philo::PhiloLive() noexcept {
  while(count_eat_) {
    {
      using Lock = std::unique_lock<std::mutex>;
      Lock lock_right(*right_fork_, std::defer_lock);
      Lock lock_left(*left_fork_, std::defer_lock);
      std::lock(lock_right, lock_left);
      SayTaken();
      SayTaken();
      SayEating();
    }
    if (config_->IsLimitLunch()) {
      --count_eat_;
    }
    SaySleeping();
    std::this_thread::yield();
  }
}
void Philo::SetRightFork(const std::shared_ptr<std::mutex> &right_fork) {
  right_fork_ = right_fork;
}
void Philo::SetLeftFork(const std::shared_ptr<std::mutex> &left_fork) {
  left_fork_ = left_fork;
}

void Philo::SetPhiloAttributes(Config *config, int id) {
  config_ = config;
  id_ = id;
  count_eat_ = config_->IsLimitLunch() ? config_->GetTimeToEat() : 1;
}
