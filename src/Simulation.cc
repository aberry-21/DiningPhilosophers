//
// Created by Aaron Berry on 5/19/21.
//

#include <thread>
#include "includes/Simulation.h"
#include "includes/Philo.h"

void Simulation::routine(Philo& philo) {
  std::unique_lock<std::mutex> lk(m_);
  while (!IsReady()) {
    cv_.wait(lk);
  }
  lk.unlock();
  philo.PhiloLive();
}

Simulation::Simulation(Config *config) : config_(config) {
  philos_ = std::make_unique<Philo[]>(config_->GetNumberOfPhilo());
  std::shared_ptr<std::mutex> left_fork;
  std::shared_ptr<std::mutex> right_fork;
  for (int i = 0; i < config_->GetNumberOfPhilo(); ++i) {
    philos_[i].SetPhiloAttributes(config_, i + 1);
    if (i == 0) {
      left_fork = std::make_shared<std::mutex>();
      philos_[i].SetLeftFork(left_fork);
      philos_[config_->GetNumberOfPhilo() - 1].SetRightFork(left_fork);
      right_fork = std::make_shared<std::mutex>();
      philos_[i].SetRightFork(right_fork);
      philos_[i + 1].SetLeftFork(right_fork);
    } else {
      right_fork = std::make_shared<std::mutex>();
      philos_[i].SetRightFork(right_fork);
      philos_[i + 1].SetLeftFork(right_fork);
    }
  }
  for (int i = 0; i < config_->GetNumberOfPhilo(); ++i) {
    std::thread(&Simulation::routine, this,  std::ref(philos_[i])).detach();
  }
}

bool Simulation::IsReady() const {
  return ready_;
}
void Simulation::StartSimulation() {
  //thread supervisor
  ready_ = true;
  config_->GetTimer().StartSimulationTime();
  cv_.notify_all();
}

