//
// Created by mhajd on 06.01.2024.
//

#ifndef PEA_GENETIC_ALGORITHM_GENETICALGO_H
#define PEA_GENETIC_ALGORITHM_GENETICALGO_H

#include <iostream>
#include <vector>
#include "Solution.h"



using namespace std;



class GeneticAlgo {

public:


    static std::pair<Solution, long long> apply(int populationSize, int maxDurationInSeconds, double mutationFactor, double crossoverFactor, Graph &graph, int mutationMethod);
    static Solution selectParent(vector<Solution> &population, int tournamentSize);
    static Solution OXCrossover(const Solution &parent1, const Solution &parent2, Graph &graph, int startPos, int endPos);
    static bool compareByCost(const Solution &x, const Solution &y);
    static void calculateFitness(vector<Solution> &currentGeneration);
    static bool containsSolution(const vector<Solution>& nextGeneration, const Solution& solution);
};


#endif //PEA_GENETIC_ALGORITHM_GENETICALGO_H
