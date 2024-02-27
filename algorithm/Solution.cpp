//
// Created by mhajd on 06.01.2024.
//

#include <numeric>
#include <random>
#include <algorithm>
#include "Solution.h"

Solution Solution::generateRandomSolution(Graph &graph) {
    Solution solution;
    std::vector<int> indices(graph.vertices);
    std::iota(indices.begin(), indices.end(), 0);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(indices.begin(), indices.end(), gen);

    solution.chromosome = indices;
    solution.cost = solution.calculateCost(graph);
    return solution;

}

int Solution::findNearestCity(const Graph &graph, int currentCity, const std::vector<bool> &visited) {
    int numberOfCities = graph.vertices;
    int nearestCity = -1;
    int minDistance = INT_MAX;

    for (int j = 0; j < numberOfCities; ++j) {
        if (!visited[j] && graph.edges[currentCity][j] < minDistance) {
            nearestCity = j;
            minDistance = graph.edges[currentCity][j];
        }
    }

    return nearestCity;
}

Solution Solution::generateGreedySolution(Graph &graph) {
    Solution solution;
    int numberOfCities = graph.vertices;
    std::vector<bool> visited(numberOfCities, false);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> randomCity(0, numberOfCities - 1);
    int currentCity = randomCity(gen);

    solution.chromosome.push_back(currentCity);
    visited[currentCity] = true;
    for (int i = 1; i < numberOfCities; ++i) {
        int nearestCity = solution.findNearestCity(graph, currentCity, visited);
        solution.chromosome.push_back(nearestCity);
        visited[nearestCity] = true;
        solution.cost += graph.edges[currentCity][nearestCity];
        currentCity = nearestCity;
    }
    solution.cost += graph.edges[currentCity][solution.chromosome[0]];
    return solution;
}

int Solution::calculateCost(Graph &graph) {
    int cost = 0;
    for (int i = 0; i < graph.vertices - 1; i++) {
        cost += graph.edges[chromosome[i]][chromosome[i + 1]];
    }
    cost += graph.edges[chromosome[graph.vertices - 1]][chromosome[0]];
    return cost;
}


void Solution::print() {
    cout << "Chromosome:\n";
    for(auto city: chromosome) {
        cout << city << " -> ";
    }
    cout << chromosome.front() << "\n";
    cout << "Cost : " << cost << "\n";

}

Solution Solution::swapMutation(Graph &graph, Solution &currentSolution) {
    Solution mutatedSol;
    int city1, city2;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> randomVertex(0, graph.vertices - 1);

    do {
        city1 = randomVertex(gen);
        city2 = randomVertex(gen);
    } while(city1 == city2);

    if(city1 > city2) {
        std::swap(city1,city2);
    }
    mutatedSol = currentSolution;
//    cout << city1 << " " << city2 << "\n";
    std::swap(mutatedSol.chromosome[city1], mutatedSol.chromosome[city2]);
    mutatedSol.cost = mutatedSol.calculateCost(graph);


    return mutatedSol;
}

Solution Solution::invertMutation(Graph &graph, Solution &currentSolution) {
    Solution mutatedSol = currentSolution;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> randomVertex(0, graph.vertices - 1);
    int beginningOfInv, endOfInv;

    do {
        beginningOfInv = randomVertex(gen);
        endOfInv = randomVertex(gen);
    }while(beginningOfInv == endOfInv);

    if(endOfInv < beginningOfInv)
        swap(beginningOfInv,endOfInv);

    std::reverse(mutatedSol.chromosome.begin() + beginningOfInv, mutatedSol.chromosome.begin() + endOfInv + 1);
    mutatedSol.cost = mutatedSol.calculateCost(graph);
    return mutatedSol;
}

Solution Solution::scrambleMutation(Graph &graph, Solution &solution) {
        Solution mutatedSol = solution;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> randomVertex(0, graph.vertices - 1);
        int beginningOfMutation, endOfMutation;
        do {
            beginningOfMutation = randomVertex(gen);
            endOfMutation = randomVertex(gen);
        } while (beginningOfMutation == endOfMutation);
        if (endOfMutation < beginningOfMutation)
            std::swap(beginningOfMutation, endOfMutation);

        std::vector<int> mutationSubset(mutatedSol.chromosome.begin() + beginningOfMutation, mutatedSol.chromosome.begin() + endOfMutation);
        std::shuffle(mutationSubset.begin(), mutationSubset.end(), gen);

        std::copy(mutationSubset.begin(), mutationSubset.end(), mutatedSol.chromosome.begin() + beginningOfMutation);
        mutatedSol.cost = mutatedSol.calculateCost(graph);
        return mutatedSol;
    }


