//
// Created by mhajd on 06.01.2024.
//

#ifndef PEA_GENETIC_ALGORITHM_SOLUTION_H
#define PEA_GENETIC_ALGORITHM_SOLUTION_H

#include <vector>
#include "../structures/Graph.h"
#include <iostream>

using namespace std;
class Solution {
public:

    vector <int> chromosome;
    double fitness;
    int cost = 0;

    static Solution generateRandomSolution(Graph &graph);
    static Solution generateGreedySolution(Graph &graph);
    int calculateCost(Graph &graph);
    void print();
    static Solution swapMutation(Graph &graph, Solution &solution);
    static Solution invertMutation(Graph &graph, Solution &solution);
    static Solution scrambleMutation(Graph &graph, Solution &solution);

    bool operator ==(const Solution& other) const {
        return chromosome == other.chromosome;
    }


    int findNearestCity(const Graph &graph, int currentCity, const vector<bool> &visited);


};


#endif //PEA_GENETIC_ALGORITHM_SOLUTION_H
