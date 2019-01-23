//
// Created by lebrenzi on 08.01.19.
//

#include "Osobnik.h"



int Osobnik::getEnergy() {
    return energy;
}

float Osobnik::getProbabilityOfCrossover() {
    return probability_of_crossover;
}

void Osobnik::setPath(vector<int> &population) {
    this->path = population;
}

void Osobnik::setEnergy(int energy) {
    this->energy = energy;
}

void Osobnik::setProbabilityOfCrossover(float probability_of_crossover) {
    this->probability_of_crossover = probability_of_crossover;
}

Osobnik::Osobnik(vector<int> path) {
    this->path = path;
}

vector<int> &Osobnik::getPath() {
    return path;
}

Osobnik::Osobnik() {
    this->energy = 0;
    this->probability_of_crossover = 0.0f;

}
