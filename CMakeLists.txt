
cmake_minimum_required(VERSION 3.13)

project(dining_philosophers VERSION 1.0 LANGUAGES CXX)

add_compile_options("-std=c++2a")

add_compile_options(
    -Werror
    -Wall
    -Wextra
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

aux_source_directory(src DIR_SRCS)
add_executable(${PROJECT_NAME} ${DIR_SRCS} src/Timer.cc includes/Timer.h src/main.cc src/Simulation.cc includes/Simulation.h src/Philo.cc includes/Philo.h src/Config.cc includes/Config.h)

target_include_directories(${PROJECT_NAME} PUBLIC .)