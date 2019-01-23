#include <iostream>
#include "Graph.h"
#include <ctime>
#include <chrono>

int main() {



	srand(time(NULL));


	fstream file;
    file.open("Tests.txt");

	int generations[] = {1000000, 500000, 1000000, 1000000, 1000000, 1000000 , 1000000, 1000000, 1000000 , 1000000 ,1000000 ,1000000 };
    int population[] =  {50,        50,     50,     20,         50,     100,    50,   50,    50, 50, 50 ,50};
    float crossover[] = {0.9f,      0.9f,    0.9f,  0.9f,      0.9f,    0.9f,   0.5f, 0.7f, 0.9f, 0.9f, 0.9f, 0.9f};
    float mutation[] = {0.1f,      0.1f,    0.1f,  0.1f,      0.1f,    0.1f,   0.1f, 0.1f, 0.1f,    0.01f,0.05f, 0.1f};

    float rst = 0.0f;
	float perc = 0.0f;
	float opt_perc = 0.0f;
	int opt34 = 1286;
    int opt58 = 25395;
    int opt171 = 2755;
    int opt443 = 2720;


	int min = INT32_MAX;


    file<<"443 miast"<<endl;
    //city2
    Graph* test2 = new Graph();
    test2->ReadFile("data171.txt");

        float best_perc = 100.0f;
        float worst_perc = 0.0f;
        file << "Parameters: " << generations[2] << " " << population[2] << " " << crossover[2] << " " << mutation[2]
             << endl;
        clock_t start = clock();
        rst = test2->GeneticAlgorithm(generations[0], population[0], crossover[0], mutation[0], opt171);
        clock_t elapsed = clock() - start;
        file << (1000 * elapsed) / CLOCKS_PER_SEC << " ";
        if (rst < best_perc) best_perc = rst;
        if (rst > worst_perc) worst_perc = rst;
        file << endl;
        if (rst > 100.0f) file << "Best PRD: " << rst << "%, Worst PRD:  " << worst_perc << " %" << endl;
        else file << "Best PRD: " << best_perc << "%, Worst PRD:  " << worst_perc << " %" << endl;

   	return 0;
}