//
// Created by Aaron Berry on 5/19/21.
//

#pragma once

#include <memory>
#include <mutex>
#include <vector>
#include "includes/philosophers.h"
#include "includes/config.h"

class philosophers;

class simulation {
 public:
  explicit simulation(config *config);
  void StartSimulation();
 private:
  bool ready_ = false;
  std::mutex m_;
  std::condition_variable cv_;
  config *config_ = nullptr;
  std::vector<philosophers> philos_;

  void Routine(philosophers &philo);
  void Supervisor();
  bool CheckCountEat();
};
