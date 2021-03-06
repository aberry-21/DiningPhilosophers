# Dining philosophers problem C++
## Problem description:
![Alt text](/images/philos.png?raw=true "Optional Title")
Five silent philosophers sit at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers. Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when they have both left and right forks. Each fork can be held by only one philosopher and so a philosopher can use the fork only if it is not being used by another philosopher. After an individual philosopher finishes eating, they need to put down both forks so that the forks become available to others. A philosopher can only take the fork on their right or the one on their left as they become available and they cannot start eating before getting both forks.  Eating is not limited by the remaining amounts of spaghetti or stomach space; an infinite supply and an infinite demand are assumed.
## How to run it
Using `make` will build the executable and run it with arguments.\
`./dining_philosophers number_of_philos life_time time_eat time_sleep [number_of_lunch]`
## License
Distributed under the MIT License. See `LICENSE` for more information.
## Example
![Alt text](/images/example.png?raw=true "Optional Title")
