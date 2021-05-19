//
// Created by Aaron Berry on 5/19/21.
//

#pragma once

#include <memory>
#include <mutex>
#include "includes/Philo.h"
#include "includes/Config.h"

class Philo;

class Simulation {

 public:
  bool IsReady() const;
  explicit Simulation(Config *config);
  void StartSimulation();
 private:
  bool ready_ = false;
  std::mutex m_;
  std::condition_variable cv_;
  Config *config_ = nullptr;
  std::unique_ptr<Philo[]> philos_;

  void routine(Philo &philo);
};
