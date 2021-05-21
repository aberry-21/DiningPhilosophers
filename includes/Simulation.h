//
// Created by Aaron Berry on 5/19/21.
//

#pragma once

#include <memory>
#include <mutex>
#include <vector>
#include "includes/Philo.h"
#include "includes/Config.h"

class Philo;

class Simulation {

 public:
  explicit Simulation(Config *config);
  void StartSimulation();
 private:
  bool ready_ = false;
  std::mutex m_;
  std::condition_variable cv_;
  Config *config_ = nullptr;
  std::vector<Philo> philos_;

  void Routine(Philo &philo);
  void Supervisor();
  bool CheckCountEat();
};
