cmake_minimum_required(VERSION 3.24)
project(PEA_genetic_algorithm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(PEA_genetic_algorithm main.cpp structures/Graph.cpp structures/Graph.h utils/Timer.cpp utils/Timer.h algorithm/Solution.cpp algorithm/Solution.h algorithm/GeneticAlgo.cpp algorithm/GeneticAlgo.h)
