//
// Created by Aaron Berry on 5/19/21.
//

#include <iostream>
#include <chrono>
#include "includes/Timer.h"

#include <thread>

void f()
{
  std::this_thread::sleep_for(std::chrono::milliseconds(1200));
}

int main()
{
  Timer timer;
  timer.StartSimulationTime();
  f();
  std::cout << timer.GetTimeSimulation() << std::endl;

}