//
// Created by Aaron Berry on 5/19/21.
//

#include <thread>
#include <vector>
#include "includes/simulation.h"
#include "includes/philosophers.h"

// Constructor (initialization threads and mutexes)
simulation::simulation(config *config) : config_(config) {
  auto size = config_->GetNumberOfPhilo();
  philos_.reserve(size);
  std::vector<std::shared_ptr<std::mutex>> mtx;
  mtx.reserve(size);
  for (int i = 0; i < size; ++i) {
    std::shared_ptr<std::mutex> fork = std::make_shared<std::mutex>();
    mtx.emplace_back(fork);
  }
  for (int i = 0; i < size; ++i) {
    philos_.emplace_back(mtx[i], mtx[(i + 1) % size], config_, i + 1);
  }
  for (int i = 0; i < size; ++i) {
    std::thread(&simulation::Routine, this, std::ref(philos_[i])).detach();
  }
}

// Start all thread and supervisor
void simulation::StartSimulation() {
  config_->GetTimer().StartSimulationTime();
  ready_ = true;
  cv_.notify_all();
  std::thread(&simulation::Supervisor, this).join();
}

//                            Private functions

// Start live philosophers
void simulation::Routine(philosophers& philo) {
  std::unique_lock<std::mutex> lk(m_);
  cv_.wait(lk, [this](){return ready_;});
  lk.unlock();
  philo.PhiloLive();
}

// Check number of philosopher's dinners
bool simulation::CheckCountEat() {
  for (int i = 0; i < config_->GetNumberOfPhilo(); ++i) {
    if (philos_[i].GetCountEat() != 0) {
      return false;
    }
  }
  return true;
}

// Start live thread supervisor
void simulation::Supervisor() {
  std::unique_lock<std::mutex> lk(m_);
  cv_.wait(lk, [this](){return ready_;});
  lk.unlock();
  while (true) {
    for (int i = 0; i < config_->GetNumberOfPhilo(); ++i) {
      if (static_cast<int>(config_->GetTimer().GetTimeSimulation() -
          philos_[i].GetTimeLastEat()) >= config_->GetTimeToDie() + 5) {
        philos_[i].SayDied();
        return;
      }
    }
    if (config_->IsLimitLunch() && CheckCountEat()) {
      return;
    }
  }
}
