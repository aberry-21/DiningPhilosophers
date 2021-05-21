//
// Created by Aaron Berry on 5/19/21.
//

#include "includes/config.h"
#include "includes/simulation.h"

static bool IsNumber(const std::string &s) {
  return all_of(s.cbegin(), s.cend(), [](const char &c) {
    return isdigit(c);
  });
}

static std::shared_ptr<std::vector<int>> CheckArgv(int argc, char **argv) {
  if (argc < 5 || argc > 6) {
    throw std::runtime_error ("Arguments error");
  }
  auto params = std::make_shared<std::vector<int>>(argc);
  for (int i = 0; i < argc - 1; ++i) {
    int param = std::stoi(argv[i + 1]);
    if (param < 0 || !IsNumber(argv[i + 1])) {
      throw std::runtime_error ("Bad argument");
    }
    (*params)[i] = param;
  }
  return params;
}

int main(int argc, char **argv)
{
  std::shared_ptr<std::vector<int>> params = CheckArgv(argc, argv);
  auto conf = config((*params)[0], (*params)[1],
(*params)[2], (*params)[3], (*params)[4]);
  simulation simulation(&conf);
  simulation.StartSimulation();
}