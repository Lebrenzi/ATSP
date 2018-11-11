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
using namespace std;

class Graph {
private:
    int size;
    int starting_point;
    int cost_prim;
    int cost_second;
    stack<int> primary;
    stack<int> secondary;
    vector< vector<unsigned short > > weighs;
    vector< vector< vector< unsigned short > > > dp;
    int VISITED_ALL_BITMAP;
    void setGraph(int);
public:
    Graph();
    ~Graph();

    void ReadFile(string name);

    void ShowGraph();
    void showBestPath(int choose); // 1 for BF, 2 for DP
    void menu();

    void trackPath();
    void bruteForceTest(int pos, int bitmask);
    int dynamicProgramming(int start, int bitmap);
    void dynamicProgrammingTest();

};


#endif //PEA_1_GRAPH_H
