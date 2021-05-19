//
// Created by Aaron Berry on 5/19/21.
//

#include <thread>
#include <chrono>
#include "includes/Config.h"
#include "includes/Simulation.h"

int main()
{
  auto conf = Config(5, 600, 200, 200, 0);
  Simulation simulation(&conf);
  std::this_thread::sleep_for(std::chrono::seconds(5));
  simulation.StartSimulation();
  std::this_thread::sleep_for(std::chrono::seconds(1000));
}