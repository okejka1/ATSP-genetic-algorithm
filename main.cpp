#include <iostream>
#include <random>
#include <fstream>
#include "structures/Graph.h"
#include "algorithm/Solution.h"
#include "algorithm/GeneticAlgo.h"


using namespace std;

void test() {
    string fileName = "ftv47.atsp";
    Graph graph(1);
    graph.readGraphDirected(fileName);
    int cost = 0;

//    cout << "INITIAL SOL:\n";
//    Solution solution = Solution::generateRandomSolution(graph);
//    solution.print();
//    cout << "MUTATED SOL:\n";
//    Solution mutatedSol = Solution::scrambleMutation(graph,solution);
//    mutatedSol.print();

//    for(int i = 0; i < 10; i++) {

//        Solution sol = Solution::generateSolution(graph);
//        sol.calculateCost(graph);
//        sol.print();
//    }
//    vector<Solution> population;
//    for(int i = 0; i < 10; i++) {
//        population.push_back(Solution::generateRandomSolution(graph));
//    }
//
//    for(auto sol: population) {
//        sol.print();
//    }
//
//    cout << "Winner of tournament:";
//    Solution parent1 = GeneticAlgo::selectParent(population,5);
//    Solution parent2 = GeneticAlgo::selectParent(population,3);
//
//    parent1.print();
//    parent2.print();
//    vector<Solution> newGen;
//    for(int i = 0; i < population.size(); i++) {
//        std::random_device rd;
//        std::mt19937 gen(rd());
//        std::uniform_int_distribution<> distribution(0, graph.vertices - 1);
//        int startPos = distribution(gen);
//        int endPos = distribution(gen);
//        if(startPos > endPos)
//            swap(startPos,endPos);
//        Solution offspring1 = GeneticAlgo::OXCrossover(parent1, parent2, graph, startPos, endPos);
//        Solution offspring2 = GeneticAlgo::OXCrossover(parent2, parent1, graph, startPos, endPos);
//        //offspring1.print();
//        //offspring2.print();
//        newGen.push_back(offspring1);
//        newGen.push_back(offspring2);
//    }
//    GeneticAlgo::calculateFitness(newGen);
//    cout << "Printing sorted nextGen\n";
//    for(auto sol : newGen) {
//        sol.print();
//    }

//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_real_distribution<> dis(0.0, 1.0);
//    double randomDouble = dis(gen);
//
//
//    std::random_device rdInt;
//    std::mt19937 genss(rd());
//    std::uniform_int_distribution<> disss(0, graph.vertices-1);
//    int randomInt = disss(genss);
//
//    cout << " RANDOM DOUBLE:" << randomDouble << "\n";
//    cout << " RANDOM INT:" << randomInt << "\n";
};

void run() {
    cout << "Genetic algorithm for ATSP\n";
    int option;
    int optimalCost;
    int endConditionInSeconds = 120;
    int initPopulationSize = 1200;
    double mutationFactor = 0.01;
    double crossoverFactor = 0.8;
    int mutationMethod = 1; // inversion mutation as default
    string fileName = "rbg403.atsp";
    Graph graph(1);
    graph.readGraphDirected(fileName);


    do {
        cout << "1.Load graph from file\n";
        cout << "2.Change stop condition\n";
        cout << "3.Change initial population size\n";
        cout << "4.Change mutation factor\n";
        cout << "5.Change crossover factor\n";
        cout << "6.Change mutation method\n";
        cout << "7.Start genetic algorithm\n";
        cout << "8.Automatic tester\n";
        cout << "9.Exit\n";
        cout << "Choose an option:";

        cin >> option;
        cin.clear(); //This corrects the stream.
        cin.ignore(); //This skips the left over stream data.

        switch (option) {
            case 1:
                do {
                    cout << "Choose a file that you want to conduct test.atsp on\n";
                    cout << "1.ftv47.atsp\n";
                    cout << "2.ftv170.atsp\n";
                    cout << "3.rbg403.atsp\n";
                    cin >> option;
                    cin.clear();
                    cin.ignore();

                } while (option < 1 || option > 3);

                if (option == 1) {
                    fileName = "ftv47.atsp";
                    optimalCost = 1776;
                }
                if (option == 2) {
                    fileName = "ftv170.atsp";
                    optimalCost = 2755;
                }
                if (option == 3) {
                    fileName = "rbg403.atsp";
                    optimalCost = 2465;
                }
                graph.readGraphDirected(fileName);
                break;

            case 2:
                cout << "Enter your stop criteria (time in seconds):\n";
                cin >> endConditionInSeconds;
                cin.clear();
                cin.ignore();
                break;
            case 3:
                cout << "Enter new initial population size:\n";
                cin >> mutationFactor;
                cin.clear();
                cin.ignore();
                break;
            case 4:
                cout << "Enter new mutation factor:\n";
                cin >> mutationFactor;
                cin.clear();
                cin.ignore();
                break;
            case 5:
                cout << "Change new crossover factor:\n";
                cin >> crossoverFactor;
                cin.clear();
                cin.ignore();
                break;
            case 6:
                cout << "Choose your mutation method:\n";
                cout << "1.Inversion mutation\n";
                cout << "2.Scramble mutation\n";
                cin >> mutationMethod;
                cin.clear();
                cin.ignore();
                break;
            case 7:
                GeneticAlgo::apply(initPopulationSize, endConditionInSeconds, mutationFactor, crossoverFactor, graph,
                                   mutationMethod);
                break;
            case 8: { // autotests
                cout << "Enter initial population size for your autotest:\n";
                cin >> initPopulationSize;
                cin.clear();
                cin.ignore();
                cout << "Choose your mutation method:\n";
                cout << "1.Inversion mutation\n";
                cout << "2.Scramble mutation\n";
                cin >> mutationMethod;
                cin.clear();
                cin.ignore();
                ofstream file((R"(..\output\results_)" + fileName + "_" + to_string(initPopulationSize) + "_" +
                               to_string(mutationMethod) + ".csv"));
                if (file.is_open()) {
                    if (fileName == "ftv47.atsp") {
                        endConditionInSeconds = 120;
                        optimalCost = 1776;
                    } else if (fileName == "ftv170.atsp") {
                        endConditionInSeconds = 240;
                        optimalCost = 2755;
                    } else if (fileName == "rbg403.atsp") {
                        endConditionInSeconds = 360;
                        optimalCost = 2465;
                    }
                }
                file << "cost;" << "time;" << "% error;" << optimalCost << "\n";

                Solution testSolution;
                testSolution.cost = INT_MAX;
                int numOfTests = 5;
                for (int i = 0; i < numOfTests; i++) {
                    pair<Solution, long> resultOfTest = GeneticAlgo::apply(initPopulationSize, endConditionInSeconds,
                                                                           mutationFactor, crossoverFactor, graph,
                                                                           mutationMethod);

                    int actualCost = resultOfTest.first.cost;
                    int percentageError = static_cast<int>(((actualCost - optimalCost) * 100.0) / optimalCost);

                    file << actualCost << ";" << resultOfTest.second << ";" << percentageError << "%" << ";"
                         << optimalCost << endl;
                    if (resultOfTest.first.cost < testSolution.cost) {
                        testSolution = resultOfTest.first;
                    }
                }
                file << "path of best solution" << endl;
                for (int item: testSolution.chromosome)
                    file << item << "->";
                file << testSolution.chromosome[0] << endl;
                file.close();
                break;
            }
            case 9:
                break;
            default:
                cout << "Invalid input\n\n";
                break;
        }

    } while (option != 9);

};

int main() {
    //test();
    run();


    return 0;
}
