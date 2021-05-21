
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
add_executable(${PROJECT_NAME} ${DIR_SRCS} src/timer.cc includes/timer.h src/main.cc src/simulation.cc includes/simulation.h src/philosophers.cc includes/philosophers.h src/config.cc includes/config.h)

target_include_directories(${PROJECT_NAME} PUBLIC .)
