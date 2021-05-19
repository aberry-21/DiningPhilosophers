
cmake_minimum_required(VERSION 3.13)

project(dining_philosophers VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(
#    -Werror
#    -Wall
#    -Wextra
)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

aux_source_directory(src DIR_SRCS)
add_executable(${PROJECT_NAME} ${DIR_SRCS} src/Timer.cc includes/Timer.h src/main.cc)

target_include_directories(${PROJECT_NAME} PUBLIC .)