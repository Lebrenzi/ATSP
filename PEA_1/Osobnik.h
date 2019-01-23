//
// Created by lebrenzi on 08.01.19.
//
#include <vector>

#ifndef PEA_1_POPULATION_H
#define PEA_1_POPULATION_H
using namespace std;

class Osobnik {
public:
    vector<int> path;
    int energy;
    float probability_of_crossover;
    Osobnik(vector<int> path);
    Osobnik();

    void setPath(vector<int> &population);

    void setEnergy(int energy);

    void setProbabilityOfCrossover(float probability_of_crossover);

    vector<int> &getPath();

    int getEnergy();

    float getProbabilityOfCrossover();

};


#endif //PEA_1_POPULATION_H
