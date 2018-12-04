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
                                        this->weighs[i].push_back(tmp);
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
        VISITED_ALL_BITMAP = (1<<size)-1;
        weighs.resize(s);
        dp.resize(size);
        vector<int> egp (2,INFINITY);
      /*  for(int i = 0; i<size; i++)
        {
                for(int j = 0; j<pow(2,(double)size); j++){

                    this->dp[i].push_back(egp);
                }
        }
        dp[0][1][0] = 0;
        dp[0][1][1] = -1;*/

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



Graph::Graph(){
        starting_point = 0;
        cost_prim = INFINITY;
        cost_second = 0;
}

Graph::~Graph(){

}


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

int Graph::dynamicProgramming(int pos, int bitmap) {

    if(bitmap == VISITED_ALL_BITMAP)
            return weighs[pos][starting_point];

    int result = INFINITY;

        for(int city=0; city<this->size; city++){

                        if(city != pos && !(bitmap & (1 << city))){

                                int newAns = weighs[pos][city] + dynamicProgramming(city,bitmap|(1<<city));
                        result = std::min(result, newAns);
                }

        }
        return result;
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
        cout<< "/***********************Main menu****************************/"<<endl;
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

void Graph::test() {


}

float Graph::decreaseTemperature(float initial_temperature) {


    float rst = initial_temperature * 0.999f;
    return rst;

}

vector<int> Graph::generateStateCandidate(vector<int> &initial_state) {


    int i = rand()%(size-1);

    int j = rand()%(size-1);

    if(i == j) generateStateCandidate(initial_state);
    else{
        if(i>j) iter_swap(initial_state.begin()+i, initial_state.begin()+j);
        else iter_swap(initial_state.begin()+j, initial_state.begin()+i);
    }


    return initial_state;
}

float Graph::getTransitionProbabilty(int delta_energy, float temperature) {
    return exp((((-1)*(float)delta_energy)/temperature));
}

bool Graph::makeTransit(float initial_transition_probability) {
    float ethalone_probability = (float)rand() / (float)RAND_MAX;

    if(ethalone_probability<= initial_transition_probability)
        return true;
    else return false;
}

int Graph::calculateEnergy(vector<int> initial_state) {
    int _energy = 0;
    for(int i = 0; i<size; i++){
        _energy+=(weighs[initial_state[i]][initial_state[i+1]]);
    }
    return _energy;
}

int Graph::simulatedAnnealing(float initial_temperature, float end_temperature) {

    int permutation_set_size = size - 1;
    vector<int> permutation_set;
    for(int i = 1; i<= permutation_set_size; i++)
        permutation_set.push_back(i);
    vector<int> initial_state;
    initial_state = permutation_set;
    initial_state.insert(initial_state.begin()+0,0);
    initial_state.push_back(0);
    int current_energy = calculateEnergy(initial_state);
    float T = initial_temperature;

    //actual algorythm
    for(float i = 0; i<1e70; i++){

        vector<int> state_candidate = generateStateCandidate(permutation_set);

        state_candidate.insert(state_candidate.begin()+0,0);
        state_candidate.push_back(0);
        int candidate_energy = calculateEnergy(state_candidate);

        if(candidate_energy<current_energy)
        {
            current_energy = candidate_energy;
            initial_state = state_candidate;
        }
        else
        {
            float p = getTransitionProbabilty(candidate_energy-current_energy,T);
            if(makeTransit(p))
            {
                current_energy = candidate_energy;
                initial_state = state_candidate;
            }

        }
        T = decreaseTemperature(T);

        //cout<< "Temperature: " << T <<", Current Energy: "<< current_energy<< " Path: ";
      //  for(int i = 0; i<sizecout<<endl;; i++)cout<<initial_state[i]<< " ";
       //cout<< "0"<<endl;

        if(T<end_temperature) break;

    }
    return current_energy;
}


