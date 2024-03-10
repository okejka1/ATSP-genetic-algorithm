# Asymetric travelling salesman problem - genetic algorithm

# Introduction
The project involves designing and implementing a genetic algorithm to solve the traveling salesman problem. The genetic algorithm is based on the process of natural evolution, where individuals represent traveling salesman routes, and their characteristics are evolved to find the best solution.

# Method
- Selection: Choosing the fittest individuals for reproduction through tournament selection
- Crossover: Order crossover (OX)
- Mutation: 2 types of mutations: Scramble mutation / Inverse mutation
- Fitness Scaling: Preserving the best individuals from the population to avoid loss of the best solutions (Elitism)



# Implementation
Programming Language: C++
Tools Used: Standard C++ library, mt19937 for generating pseudo-random numbers, std::chrono::high_resolution_clock for time measurement.
Tested Traveling Salesman Problem Instances: ftv47, ftv170, rbg403.
Parameters: Population size (1000, 2000, 5000), mutation (0.01), and crossover (0.8) rates, time constraints for each problem instance.
