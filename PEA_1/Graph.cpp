//
// Created by lebrenzi on 14.10.18.
//
#ifdef __cplusplus__
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#include <iostream>
#include <climits>
#include <cmath>
#include <algorithm>
#include "Graph.h"
#define INFINITY 5000



void Graph::ReadFile(string name) {

        ifstream file;
        int size;
        int tmp = 0;
        file.open( name );
        if( !file.good() ){
            cout<<"No such file" << endl;
            return;}
        else{
                file>>size;
				
                this->setGraph(size);
                do
                {
                        for(int i = 0; i<size;i++) {
	
                                for(int j = 0; j<size;j++) {
                                        file >> tmp;
										weighs[i].push_back(tmp);
                                }

						}

                }
                while(!EOF);
                cout << "Reading completed"<< endl;
        }

        return;
    }

void Graph::setGraph(int s) {

        this->size = s;
        weighs.resize(s);
  
}


void Graph::testInstance(int n) {
    this->size = n;

    for(int i = 0; i < n; i++)
    {
        vector<int> tmp;
        for(int j = 0; j < n; j++)
        {
            if(i == j) tmp.push_back(0);
            else tmp.push_back(rand() % 100);
        }

        weighs.push_back(tmp);
    }


}

void Graph::ShowGraph() {
    cout << this->size <<endl;

    for(int i = 0; i < this->size;i++)
    {
        for(int j = 0; j < this->size;j++)
        {
            cout<< weighs[i][j] << " ";
        }
        cout<<endl;
    }
}


Graph::~Graph() {

}

Graph::Graph() {

}



/*
 *
 *
 *
 * Genetic algorithm
 * 1 crossover per population
 * constant population
 * every singleton to mutate in population
 *in 1 generation
 *
 *
 *
 *
 */
float Graph::GeneticAlgorithm(int generations, int population, float crossover_prob, float mutation_prob, int optimum) {
    vector<Osobnik> osobniki;
    for(int i = 0; i<population; i++)
    {
        Osobnik os = GenerateSolution();
        osobniki.push_back(os);
    }
    for(int i = 0; i<generations; i++)
    {
        Selection(osobniki,population);
        CrossoverInterface(crossover_prob, osobniki);
        if(i == generations-1) {
            MutationInterface(mutation_prob, osobniki);
            Selection(osobniki, population);
        }
        else
            MutationInterface(mutation_prob, osobniki);

    }
    return (((float)osobniki[0].getEnergy()-(float)optimum)/(float)optimum) *100.0f;

}

int Graph::CalculateCost(vector<int> &path) {
    int _total_energy = 0;
    _total_energy+=weighs[0][path[0]];
    for(int i = 0 ;i<path.size()-1;i++)
    {
        _total_energy+=weighs[path[i]][path[i+1]];
    }
    _total_energy+=weighs[path[path.size()-1]][0];
    return _total_energy;
}

Osobnik Graph::GenerateSolution() {
    vector<int> _solution;
    for(int i=1; i<size;i++)
    {
        _solution.push_back(i);
    }
    random_shuffle(_solution.begin(), _solution.end());
    int _energy = CalculateCost(_solution);
    Osobnik pop;
    pop.setPath(_solution);
    pop.setEnergy(_energy);
    return pop;
}

void Graph::Mutate(Osobnik &singleton) {

    float first, second;
    first = rand()%singleton.getPath().size();
    second = rand()% singleton.getPath().size();

    std::iter_swap(singleton.getPath().begin() + first, singleton.getPath().begin() + second);
    singleton.setEnergy(CalculateCost(singleton.getPath()));
}

Osobnik Graph::Crossover(Osobnik &first, Osobnik &second) {

    vector<int> child;
    for(int i = 0; i< first.getPath().size()/2;i++)
    {
        child.push_back(first.getPath()[i]);
    }
    for(int i = 0; i< second.getPath().size();i++)
    {   int element = second.getPath()[i];
        if(std::find(child.begin(), child.end(), element) != child.end()) {
            continue;
        } else {
            child.push_back(element);
        }
    }
    Osobnik pop;
    pop.setPath(child);
    pop.setEnergy(CalculateCost(child));
    return pop;

}

void Graph::Selection(vector<Osobnik> &population, int population_initial_size) {
    std::sort(population.begin(), population.end(),
              [this](Osobnik& a, Osobnik& b) {
                  return a.getEnergy() < b.getEnergy();
              });
    float _max_fitness = 0.0f;
    for(int i = 0; i<population.size(); i++)
    {
        _max_fitness+=population[i].getEnergy();
    }
    for(int i = 0; i<population.size(); i++)
    {
        population[i].setProbabilityOfCrossover((float)population[i].getEnergy()/_max_fitness);
    }
    if(population.size()>population_initial_size+population_initial_size*0.20)
        {population.erase(population.begin()+population_initial_size,population.end());}

}

void Graph::MutationInterface(float probability_of_mutation, vector<Osobnik> &population) {
    for (int i = 0; i < population.size(); i++) {
        float mutation = (float) rand() / (1.0f * RAND_MAX);
        if (mutation < probability_of_mutation) {

            Mutate(population[i]);
        }
        else continue;
    }

}

void Graph::CrossoverInterface(float probability_of_crossover, vector<Osobnik> &population) {
    float crossover = (float)rand()/(1.0f*RAND_MAX);
    if(crossover<probability_of_crossover){
        Osobnik first = CrossoverFirstCandidate(population);
        Osobnik second = CrossoverSecondCandidate(population,first);

        Osobnik child1 = Crossover(first,second);
        Osobnik child2 = Crossover(second,first);
        population.push_back(child1);
        population.push_back(child2);
    }
    else return;

}

Osobnik Graph::CrossoverFirstCandidate(vector<Osobnik> &population) {
    for(int i = 0; i<population.size(); i++)
    {
        float prob = (float)rand()/(1.0f*RAND_MAX);
        if(prob>population[i].getProbabilityOfCrossover()) return population[i];
    }
    return population[0];
}

Osobnik Graph::CrossoverSecondCandidate(vector<Osobnik> &population, Osobnik &firstone) {
    for(int i = 0; i<population.size(); i++)
    {
        if (population[i].path == firstone.path) continue;
        float prob = (float) rand() / (1.0f * RAND_MAX);
        if (prob > population[i].getProbabilityOfCrossover()) return population[i];
    }
    return population[population.size()-1];
}




/*
 *
 *
 * Simulated Annealing
 * params: T_start, T_end, Cooling_Factor
 *
 *
 *
 */


void Graph::generateStateCandidate(vector<int> &initial_state) {


    int i = rand() % initial_state.size();
    int j;
    do
    {
        j = rand() % initial_state.size();
    } while (i == j); {

    }

    std::swap(initial_state[i], initial_state[j]);

}





float Graph::getTransitionProbabilty(int delta_energy, float temperature) {
    float rst;
    rst = exp((-1.0 * delta_energy) / temperature);
    return rst ;
}




bool Graph::makeTransit(float initial_transition_probability) {

    float ethalone_probability = (float)rand() / (1.0*RAND_MAX);

    return ethalone_probability < initial_transition_probability;
}





int Graph::calculateEnergy(vector<int> &initial_state) {

    int energy = 0;
    int tmp = 0;
    energy = energy + weighs[0][initial_state[0]];
    for(int i = 0; i<initial_state.size()-1; i++){
        tmp = weighs[initial_state[i]][initial_state[i + 1]];
        energy = energy + tmp;
    }
    energy = energy + weighs[initial_state[initial_state.size()-1]][0];
    return energy;
}



int Graph::simulatedAnnealing(float initial_temperature, float end_temperature, float cooling_factor) {

    vector<int> permutation_set = generateGreedyTour();

    permutation_set.erase(permutation_set.begin() + permutation_set.size()-1);

    vector<int> initial_state;

    initial_state = permutation_set;

    int current_energy = calculateEnergy(initial_state);
    float T = initial_temperature;
    cout << current_energy << endl;
    //actual algorythm//
    while (T > end_temperature) {

        for (float i = 0; i < size ; i++) {

            vector<int> state_candidate = initial_state;

            generateStateCandidate(state_candidate);

            int candidate_energy = calculateEnergy(state_candidate);

            cout << "Temp: " << T << " Current Energy: "<<current_energy << " Candidate Energy: " << candidate_energy << endl;

            if (candidate_energy < current_energy)
            {
                current_energy = candidate_energy;
                initial_state = state_candidate;
                break;
            }
            else
            {
                float p = getTransitionProbabilty(candidate_energy - current_energy, T);
                if (makeTransit(p))
                {
                    current_energy = candidate_energy;
                    initial_state = state_candidate;
                    break;
                }
            }

        }

        T = T * cooling_factor;

    }

    return current_energy;
}



int vector_min(vector<int> vec, bool visited[])
{
    int min = INT32_MAX;
    int idx = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] < min && !visited[i])
        {
            min = vec[i];
            idx = i;
        }
    }
    return idx;
}

vector<int> Graph::generateGreedyTour()
{
    int min = INT32_MAX;
    vector<int> tour;
    tour.push_back(0);
    bool *visited = new bool [size];
    visited[0] = true;
    for (int i = 1; i < size; i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < size; i++)
    {
        int idx = vector_min(weighs[tour[i]], visited);
        visited[idx] = true;
        tour.push_back(idx);
    }
    tour.erase(tour.begin());
    return tour;
}



/*
 *
 *
 *
 * Brute Force and Dynamic Programming
 *
 *
 *
 */




void Graph::showBestPath(int choose) {

        //BruteForce algorythm
    switch(choose){
        case 1: {
            int tmp = 0;
            int stack_size = primary.size();
            for (int i = 0; i < stack_size; i++) {
                tmp = primary.top();
                secondary.push(tmp);
                primary.pop();
            }
            if (!secondary.empty()) {
                cout << "path: ";
                for (int i = 0; i < stack_size; i++) {
                    tmp = secondary.top();
                    cout << tmp << " ";
                    secondary.pop();
                }
                cout << starting_point << endl;
                cout << "cost : " << cost_prim << endl;

            } else {
                cout << "No cycle" << endl;
            }
            break;
        }
        //Dynamic programming algorithm
        case 2: {
            int stack_size = primary.size();
            int tmp = 0;
            if (!primary.empty()) {

                cout << "path: ";

                for (int i = 0; i < stack_size; i++) {
                    tmp = primary.top();
                    cout << tmp << " ";
                    primary.pop();
                }
                cout << starting_point << endl;
            } else {
                cout << "No cycle" << endl;
            }
            break;
        }
    }


}


void Graph::bruteForceTest(int pos, int bitmask) {
    int next;
    secondary.push(pos); // wrzucamy wierzchołek do stosu tymczasowych rozwiązań
    if(secondary.size()<this->size){ //Sprawdzamy rozwiązania dopóki stos rozmiar stosu nie stanie rozmiarem rozwiązania
        for(next = 0; next<this->size;next++) { //Sprawdzamy sąsiadów naszego miasta
            if ((next != pos) && ((bitmask & (1 << next)) == 0)) { //Sprawdzamy jeśli sąsiad nie jest naszym miastem i nie jest sprawdzony wcześniej
                cost_second += weighs[pos][next]; // Dokładamy drogę do tymczasowego rozwiązania
                bruteForceTest(next, bitmask | (1 << next)); // Rekurencyjnie wywołujemy funkcje stawiąc na pozycję naszego miasta jesgo sąiada, oraz dokładamy że sąsiad jest sprawdzony
                cost_second -= weighs[pos][next]; //przy wyjściu z rekurencji odejmujemy drogę, żeby pójść inną ścieżką
            }
        }
    }
    else{
        if(bitmask == VISITED_ALL_BITMAP){ // Jeśli doszliśmy do końca drogi
            cost_second += weighs[pos][starting_point]; // dokładamy do tymczasowego rozwiązania drogę od ostatniego miasta w zbiorze rozwiązań do miasta startowego
            if(cost_prim>cost_second) //jeśli koszt podstawowy jest większy od kosztu tymczasowego
            {
                cost_prim = cost_second; // to koszt przejścia tymczaswoy staję się kosztem podstawowym
                primary = secondary; // zbiór miast rozwiązania tymczasowego staję się zbiorem rozwiązania podstawowym
            }
            cost_second-=weighs[pos][starting_point]; // przy wyjściu odejmujemy ostatni odcinek drogi dla sprawdzenia innych ścieżek
        }
    }
    secondary.pop(); //kasujemy ostatni wierzchołek w zbiorze rozwiązań dla sprawdzenia innych ścieżek
}



void Graph::dynamicProgrammingTest() {
    int tmp = 0;
    for(int mask = 1; mask<(1<<size); mask++){ // Sprawdzamy wszytkie podzbiory po kolei zaczynajac od samego wierzchołka startowego
        for(int lastNode = 0; lastNode < size; lastNode++){ //Bierzemy miasto sąsiedzi którego będziemy sprawdzać
            if((mask & (1<<lastNode)) == 0) // Jeśli miasto nie zgadza się z maską sprawdzamy następne
                continue;
            for(int nextNode = 0; nextNode < size; nextNode++){ // Oglądamy sąsiedzi naszego miasta po kolei
                if((mask &(1<<nextNode)) != 0) // Jeśli miasto już jest odwiedzone to nie sprawdzamy jego
                    continue;
                tmp = dp[nextNode][mask | (1<<nextNode)][0];
                dp[nextNode][mask | (1<<nextNode)][0] = std::min((int)
                        dp[nextNode][mask|(1<<nextNode)][0],
                        dp[lastNode][mask][0] + weighs[lastNode][nextNode]); //Jeśli nowa ścieżka jest mniejsza od starej wpisz ją do macierzy rozwiązań
                if(dp[nextNode][mask | (1<<nextNode)][0] == tmp) continue;
                else dp[nextNode][mask | (1<<nextNode)][1] = lastNode; //Jeśli ścieżka się zmieniła, zmień poprzednika

            }

        }
    }
    int res = INFINITY;
    for (int lastNode = 0; lastNode < size; lastNode++)
        res = std::min((int)res, weighs[lastNode][0] + dp[lastNode][(1 << size) - 1][0]);
    cout<< res;
}


void Graph::menu() {
        int choose;
        cout<< "/***********************Main menu****************************"<<endl;*/

cout<< "1. Read graph from file" << endl;
cout<< "2. Show current graph" <<endl;
cout<< "3. Brute Force algorithm on current graph" << endl;
cout<< "4. Dynamic programming algorithm on current graph" << endl;
cout<< "0. Exit"<<endl;
cin >> choose;
switch(choose){
    case 1:{
        if(size>0){cout<<"Graph already readed"; break;}
        else {
            system("CLS");
            string name;
            cout << "Enter filename" << endl;
            cin >> name;
            this->ReadFile(name);
            cout<<endl;
            cout<<endl;
            menu();
            break;
        }
    }
    case 2:{
            if(this->size)
                    this->ShowGraph();
            else cout<<"Read the graph first"<<endl;
            menu();
            cout<<endl;
            break;
    }
    case 3:{
            if(this->size){
                   this->bruteForceTest(0,1);
                   this->showBestPath(1);

            }
            else cout<<"Read the graph first"<<endl;
            cout<<endl;
            cout<<endl;
            menu();
            break;
    }
    case 4:{
                if(this->size){
                        cout<< "Result is: ";
                    this->dynamicProgrammingTest();
                    cout<<endl;
                    this->trackPath();
                    this->showBestPath(2);

                }
                else cout<<"Read the graph first"<<endl;
                cout<<endl;
                cout<<endl;
                menu();
                break;
        }
    case 0:
    {
            return;

    }
}

}

void Graph::trackPath() {
int bitmask = VISITED_ALL_BITMAP; //Sprawdzamy drogę od końca
int res = INFINITY;
int tmp = 0; // następnik min_pos
int min_pos = 0; //tu zapisujemy nasz wierzchołek którym działamy
for (int lastNode = 0; lastNode < size; lastNode++) {
tmp = res;
res = std::min(res, weighs[lastNode][0] + dp[lastNode][(1 << size) - 1][0]);
if(tmp>res) min_pos = lastNode;
} //Wyznaczamy jaki wierzchółek był ostatni przed wierzchólkiem startowym

while(true){

tmp = min_pos;// zapisujemy następnika
min_pos = dp[tmp][bitmask][1]; // wyznaczamy poprzednika
if(tmp == 0) { // jeśli doszliśmy do wierzchołka startowego to kończymy
    primary.push(0);
    return;
}
primary.push(tmp); // wrzucamy wierzchołek do zbioru rozwiązan
bitmask = bitmask ^ (1<<tmp); // wyznaczamy zbiór miast dla poprzedniego kroku
}

}
