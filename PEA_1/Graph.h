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

using namespace std;

class Graph {
private:
    int size;
    int starting_point;
    int cost_prim;
    int cost_second;
    stack<int> primary;
    stack<int> secondary;
    vector< vector<int > > weighs;
    vector< vector< vector< int > > > dp;
    int VISITED_ALL_BITMAP;
    void setGraph(int);
public:
    Graph();
    ~Graph();

    void ReadFile(string name);

    void ShowGraph();
    void showBestPath(int choose); // 1 for BF, 2 for DP
    void menu();
    void test();


    //Local Search Algorythm
    int simulatedAnnealing(float initial_temperature,float end_temperature);
    float decreaseTemperature(float initial_temperature);
    vector<int> generateStateCandidate(vector<int> &initial_state);
    int calculateEnergy(vector<int> initial_state);
    float getTransitionProbabilty(int delta_energy, float temperature);
    bool makeTransit(float initial_transition_probability);

    //Accurate Algorythms
    void trackPath();
    void bruteForceTest(int pos, int bitmask);
    int dynamicProgramming(int start, int bitmap);
    void dynamicProgrammingTest();

};


#endif //PEA_1_GRAPH_H
