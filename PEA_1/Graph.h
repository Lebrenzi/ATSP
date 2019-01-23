//
// Created by lebrenzi on 14.10.18.
//

#ifndef PEA_1_GRAPH_H
#define PEA_1_GRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stack>
#include <random>
#include <algorithm>
#include "Osobnik.h"

typedef int population[2];

class Graph {
private:
    int size;
    vector<vector<int>> weighs;

    //BF and DP fields
    vector<vector<int>> dp;
    stack<int> primary;
    stack<int> secondary;
    int cost_prim;
    int cost_second;
    int VISITED_ALL_BITMAP;
    int starting_point;

    void setGraph(int);
public:
    Graph();
    ~Graph();
    void ReadFile(string name);
    void ShowGraph();
    void menu();
    void showBestPath(int choose);
    void testInstance(int n);


    //BF function
    void bruteForceTest(int pos, int bitmask);

    //DP function
    void dynamicProgrammingTest();
    void trackPath();



    //Simulated Annealing Functions
    void generateStateCandidate(vector<int> &initial_state);
    float getTransitionProbabilty(int delta_energy, float temperature);
    bool makeTransit(float initial_transition_probability);
    int calculateEnergy(vector<int> &initial_state);
    int simulatedAnnealing(float initial_temperature, float end_temperature, float cooling_factor);
    vector<int> generateGreedyTour();




    //Genetic Algorithm functions
    float GeneticAlgorithm(int generations, int population, float crossover_prob, float mutation_prob, int optimum);
    int CalculateCost(vector<int> &path);

    void MutationInterface(float probability_of_mutation, vector<Osobnik> &population);
    void CrossoverInterface(float probability_of_crossover, vector<Osobnik> &population);

    Osobnik CrossoverFirstCandidate(vector<Osobnik> &population);
    Osobnik CrossoverSecondCandidate(vector<Osobnik> &population, Osobnik &firstone);

    void Mutate(Osobnik &singleton);
    Osobnik Crossover(Osobnik &first, Osobnik &second);
    void Selection(vector<Osobnik> &population, int population_initial_size);

    Osobnik GenerateSolution();


};


#endif //PEA_1_GRAPH_H
