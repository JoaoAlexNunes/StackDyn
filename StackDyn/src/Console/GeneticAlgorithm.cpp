#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "Block.h"
#include "Stack.h"

// GeneticAlgorithm class
class GeneticAlgorithm {
private:
    int populationSize;
    double mutationRate;

public:
    GeneticAlgorithm(int popSize, double mutationRate) : populationSize(popSize), mutationRate(mutationRate) {}

    std::vector<int> Run(Stack& arrivalStack, Stack& buffer1, Stack& buffer2, Stack& buffer3) {
        // Generate an initial population
        std::vector<std::vector<int>> population;
        for (int i = 0; i < populationSize; ++i) {
            std::vector<int> solution = GenerateRandomSolution(arrivalStack.GetCurrentSize());
            population.push_back(solution);
        }

        // Perform the optimization iterations
        for (int iter = 0; iter < 100; ++iter) { // Adjust the number of iterations as needed
            // Calculate the fitness scores for the current population
            std::vector<double> fitnessScores = CalculateFitnessScores(population, arrivalStack, buffer1, buffer2, buffer3);

            // Select parents for crossover
            std::vector<std::vector<int>> selectedParents;
            for (int i = 0; i < populationSize; ++i) {
                std::vector<int> parent = Selection(population, fitnessScores);
                selectedParents.push_back(parent);
            }

            // Create the next generation through crossover and mutation
            std::vector<std::vector<int>> nextGeneration;
            for (int i = 0; i < populationSize; i += 2) {
                std::vector<int> parent1 = selectedParents[i];
                std::vector<int> parent2 = selectedParents[i + 1];
                std::vector<int> offspring = Crossover(parent1, parent2);
                Mutate(offspring);
                nextGeneration.push_back(offspring);
            }

            // Replace the current population with the next generation
            population = nextGeneration;

            // Update the buffer stacks based on the best solution in the current population
            int bestIndex = std::distance(fitnessScores.begin(), std::min_element(fitnessScores.begin(), fitnessScores.end()));
            std::vector<int> bestSolution = population[bestIndex];

            for (int i = 0; i < arrivalStack.GetCurrentSize(); ++i) {
                Block* block = arrivalStack.GetBlock(i);
                int bufferIndex = bestSolution[i];
                Stack* targetBuffer = nullptr;

                if (bufferIndex == 1)
                    targetBuffer = &buffer1;
                else if (bufferIndex == 2)
                    targetBuffer = &buffer2;
                else if (bufferIndex == 3)
                    targetBuffer = &buffer3;

                targetBuffer->AddBlock(block);
            }
        }

        // Apply heuristic algorithm to optimize the final solution
        ApplyHeuristic(arrivalStack, buffer1, buffer2, buffer3);

        // Return the best solution found
        int bestIndex = std::distance(fitnessScores.begin(), std::max_element(fitnessScores.begin(), fitnessScores.end()));
        return population[bestIndex];
    }

private:
    // Generate a random solution (chromosome)
    std::vector<int> GenerateRandomSolution(int numBlocks) {
        std::vector<int> solution(numBlocks);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 3);  // Randomly assign each block to one of the three buffers

        for (int i = 0; i < numBlocks; ++i) {
            solution[i] = dis(gen);
        }

        return solution;
    }

    // Calculate the fitness scores of all solutions in the population
    void CalculateFitnessScores(const std::vector<std::vector<int>>& population, Stack& arrivalStack, Stack& buffer1, Stack& buffer2, Stack& buffer3, std::vector<double>& fitnessScores) {
        for (int i = 0; i < populationSize; ++i) {
            std::vector<int> solution = population[i];

            for (int j = 0; j < arrivalStack.blocks.size(); ++j) {
                Block* block = arrivalStack.blocks[j];

                if (solution[j] == 1 && buffer1.GetTotalWeight() + block->weight <= weightLimit) {
                    buffer1.blocks.push_back(block);
                }
                else if (solution[j] == 2 && buffer2.GetTotalWeight() + block->weight <= weightLimit) {
                    buffer2.blocks.push_back(block);
                }
                else if (solution[j] == 3 && buffer3.GetTotalWeight() + block->weight <= weightLimit) {
                    buffer3.blocks.push_back(block);
                }
                else {
                    // Handle the case when a block cannot be added to any buffer
                }
            }

            fitnessScores[i] = CalculateFitnessObjective(buffer1, buffer2, buffer3);

            buffer1.blocks.clear();
            buffer2.blocks.clear();
            buffer3.blocks.clear();
        }
    }

    // Perform selection of parents for crossover
    std::vector<int> Selection(const std::vector<std::vector<int>>& population, const std::vector<double>& fitnessScores) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::discrete_distribution<> dist(fitnessScores.begin(), fitnessScores.end());
        int index = dist(gen);
        return population[index];
    }

    // Perform crossover between two parents to generate an offspring
    std::vector<int> Crossover(const std::vector<int>& parent1, const std::vector<int>& parent2) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        std::vector<int> offspring(parent1.size());

        for (int i = 0; i < parent1.size(); ++i) {
            if (dis(gen) < 0.5)
                offspring[i] = parent1[i];
            else
                offspring[i] = parent2[i];
        }

        return offspring;
    }

    // Perform mutation on the offspring
    void Mutate(std::vector<int>& offspring) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);

        for (int i = 0; i < offspring.size(); ++i) {
            if (dis(gen) < mutationRate) {
                std::uniform_int_distribution<> dis(1, 3);
                offspring[i] = dis(gen);
            }
        }
    }

    // Calculate the fitness objective based on your objective function
    double CalculateFitnessObjective(Stack& buffer1, Stack& buffer2, Stack& buffer3) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        return dis(gen);
    }

    // Apply a heuristic algorithm to optimize the solution
    void ApplyHeuristic(Stack& arrivalStack, Stack& buffer1, Stack& buffer2, Stack& buffer3) {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::shuffle(buffer1.blocks.begin(), buffer1.blocks.end(), gen);
        std::shuffle(buffer2.blocks.begin(), buffer2.blocks.end(), gen);
        std::shuffle(buffer3.blocks.begin(), buffer3.blocks.end(), gen);
    }
};

int main() {
    // Define your input parameters
    int populationSize = 100;
    double mutationRate = 0.1;

    // Create the stacks
    Stack arrivalStack;
    Stack buffer1;
    Stack buffer2;
    Stack buffer3;

    // Perform the optimization using the genetic algorithm
    GeneticAlgorithm ga(populationSize, mutationRate);
    std::vector<int> bestSolution = ga.Run(arrivalStack, buffer1, buffer2, buffer3);

    // Print the best solution found
    std::cout << "Best Solution: ";
    for (int i = 0; i < bestSolution.size(); ++i) {
        std::cout << bestSolution[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}