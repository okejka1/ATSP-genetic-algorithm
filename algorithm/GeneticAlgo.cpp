

#include <random>
#include "GeneticAlgo.h"
#include "../utils/Timer.h"


Solution GeneticAlgo::selectParent(vector<Solution> &population, int tournamentSize) { // tournament selection
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, population.size()/3);

    Solution bestParent;

    for (int i = 0; i < tournamentSize; i++) {
        int randomIndex = distribution(gen);
        const Solution &candidate = population[randomIndex];

        if (i == 0 || candidate.cost < bestParent.cost) {
            bestParent = candidate;
        }
    }
    return bestParent;
}

Solution GeneticAlgo::OXCrossover(const Solution &parent1, const Solution &parent2, Graph &graph, int startPos, int endPos) {
    Solution offspring;
    int size = parent1.chromosome.size();

    for (int i = startPos; i <= endPos; i++) {
        offspring.chromosome.push_back(parent1.chromosome[i]);
    }
    int index = (endPos + 1) % size;
    int count = offspring.chromosome.size();

    while (count < size) {
        if (find(offspring.chromosome.begin(), offspring.chromosome.end(), parent2.chromosome[index]) ==
            offspring.chromosome.end()) {
            offspring.chromosome.push_back(parent2.chromosome[index]);
            count++;
        }
        index = (index + 1) % size;
    }
    offspring.cost = offspring.calculateCost(graph);
    return offspring;
}

bool GeneticAlgo::compareByCost(const Solution &x, const Solution &y) {
    return x.cost < y.cost;
}

void GeneticAlgo::calculateFitness(vector<Solution> &currentGeneration) {
    // Sort the population by cost
    sort(currentGeneration.begin(), currentGeneration.end(), compareByCost);

    int currentMinCost = currentGeneration[0].cost;
    int currentMaxCost = currentGeneration.back().cost;
    int generationCostRange = currentMaxCost - currentMinCost;

    if (generationCostRange > 0) {
        // Calculate fitness values between 0 and 1
        for (auto &solution: currentGeneration) {
            double normalizedFitness =
                    1.0 - (static_cast<double>(solution.cost - currentMinCost) / generationCostRange);
            solution.fitness = normalizedFitness;
        }
    } else {
        // Handle the case when all costs are the same (avoid division by zero)
        for (auto &solution: currentGeneration) {
            solution.fitness = 1.0;
        }
    }
}



std::pair<Solution, long long>
GeneticAlgo::apply(int initialPopulationSize, int maxDurationInSeconds, double mutationFactor, double crossoverFactor,
                   Graph &graph, int mutationMethod) {

    double ELITISM = 0.95; // best solutions added to nex gen

    vector<Solution> population;

    Solution bestSolution;
    bestSolution.cost = INT_MAX;
    long long bestSolutionTime = 0;

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_real_distribution<double> distribution(0.0, 1.0);

    std::random_device rdInt; // Generating positions for crossover
    std::mt19937 gen(rdInt());
    std::uniform_int_distribution<> disInt(0, graph.vertices - 1);

    // INITIALISATION OF GA FOR ATSP
    population.push_back(Solution::generateGreedySolution(graph));
    //population.push_back(Solution::generateRandomSolution(graph));
    for (int i = 1; i < initialPopulationSize; i++) {
        population.push_back(Solution::generateRandomSolution(graph));
    }
    calculateFitness(population);

    Timer timer;
    timer.start();

    while (timer.mili() < static_cast<long long>(maxDurationInSeconds) * 1000) {

        calculateFitness(population);
        if (bestSolution.cost > population[0].cost) {
            bestSolution = population[0];
            bestSolutionTime = timer.mili();
            cout << "New best solution:";
            bestSolution.print();
            //cout << "New best solutionTime :" << bestSolutionTime << "\n";
        }

        vector<Solution> nextGeneration;
        for (int i = population.size() - 1; i >= initialPopulationSize; i--) { // reducing population to its initial size
            if (i > initialPopulationSize) {
                population.pop_back();
            } else {
                break;
            }
        }

           for(int i = 0; i < population.size(); i++) {
            if ((population[i].fitness > ELITISM) &&
                !containsSolution(nextGeneration, population[i])) {
                nextGeneration.push_back(population[i]);
            }
            double randVal = distribution(generator);

            if (randVal < crossoverFactor) {
                Solution parent1, parent2;

                parent1 = GeneticAlgo::selectParent(population, 8);
                parent2 = GeneticAlgo::selectParent(population, 8);
                if (parent1.operator==(parent2))
                    continue;

                int startPos = disInt(gen);
                int endPos = disInt(gen);

                if (startPos > endPos)
                    swap(startPos, endPos);

                Solution offspring1 = GeneticAlgo::OXCrossover(parent1, parent2, graph, startPos, endPos);
                if (!containsSolution(nextGeneration, offspring1)) {
                    nextGeneration.push_back(offspring1);
                }

                Solution offspring2 = GeneticAlgo::OXCrossover(parent2, parent1, graph, startPos, endPos);
                if (!containsSolution(nextGeneration, offspring2)) {
                    nextGeneration.push_back(offspring2);
                }
            }
            if (1 - randVal < mutationFactor) {


                Solution mutatedSolution;
                if(mutationMethod == 1) {
                    mutatedSolution = Solution::invertMutation(graph, population[i]);
                    nextGeneration.push_back(mutatedSolution);
                } else {
                    mutatedSolution = Solution::scrambleMutation(graph, population[i]);
                    nextGeneration.push_back(mutatedSolution);
                }

            }

        }
        population = nextGeneration;
        timer.stop();
    }
    timer.stop();
    bestSolution.print();
    cout << "Solution found in " << bestSolutionTime << " ms" << endl;
    return std::make_pair(bestSolution, bestSolutionTime);
}

bool GeneticAlgo::containsSolution(const vector<Solution> &nextGeneration, const Solution &solution) {
    return std::find(nextGeneration.begin(), nextGeneration.end(), solution) != nextGeneration.end();
}















