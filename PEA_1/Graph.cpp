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
        unsigned short tmp = 0;
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
        vector<unsigned short> egp (2,INFINITY);
        for(int i = 0; i<size; i++)
        {
                for(int j = 0; j<pow(2,(double)size); j++){

                    this->dp[i].push_back(egp);
                }
        }
        dp[0][1][0] = 0;
        dp[0][1][1] = -1;

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
    secondary.push(pos);
    if(secondary.size()<this->size){
        for(next = 0; next<this->size;next++) {
            if ((next != pos) && ((bitmask & (1 << next)) == 0)) {
                cost_second += weighs[pos][next];
                bruteForceTest(next, bitmask | (1 << next));
                cost_second -= weighs[pos][next];
            }
        }
    }
    else{
        if(bitmask == VISITED_ALL_BITMAP){
            cost_second += weighs[pos][starting_point];
            if(cost_prim>cost_second)
            {
                cost_prim = cost_second;
                primary = secondary;
            }
            cost_second-=weighs[pos][starting_point];
        }
    }
    secondary.pop();
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
    for(int mask = 1; mask<(1<<size); mask++){
        for(int lastNode = 0; lastNode < size; lastNode++){
            if((mask & (1<<lastNode)) == 0)
                continue;
            for(int nextNode = 0; nextNode < size; nextNode++){
                if((mask &(1<<nextNode)) != 0)
                    continue;
                tmp = dp[nextNode][mask | (1<<nextNode)][0];
                dp[nextNode][mask | (1<<nextNode)][0] = std::min((int)
                        dp[nextNode][mask|(1<<nextNode)][0],
                        dp[lastNode][mask][0] + weighs[lastNode][nextNode]);
                if(dp[nextNode][mask | (1<<nextNode)][0] == tmp) continue;
                else dp[nextNode][mask | (1<<nextNode)][1] = lastNode;

            }

        }
    }
    unsigned short res = INFINITY;
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

                    system("CLS");
                    menu();
                    break;
                }
            }
            case 2:{
                    if(this->size)
                            this->ShowGraph();
                    else cout<<"Read the graph first"<<endl;
                    menu();
                    break;
            }
            case 3:{
                    if(this->size){
                           int rs = this->dynamicProgramming(0,1);
                           cout<<rs<<endl;

                    }
                    else cout<<"Read the graph first"<<endl;
                    menu();
                    break;
            }
            case 4:{
                        if(this->size){
                                cout<< "Result is: ";
                                this->dynamicProgrammingTest();
                                cout<<endl;

                        }
                        else cout<<"Read the graph first"<<endl;
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
    int bitmask = VISITED_ALL_BITMAP;
    int adding_bitmask;
    int res = INFINITY;
    int tmp = 0;
    int min_pos = 0;
    for (int lastNode = 0; lastNode < size; lastNode++) {
        tmp = res;
        res = std::min(res, weighs[lastNode][0] + dp[lastNode][(1 << size) - 1][0]);
        if(tmp>res) min_pos = lastNode;
    }

    while(true){

        tmp = min_pos;
        min_pos = dp[tmp][bitmask][1];
        if(tmp == 0) {
            primary.push(0);
            return;
        }
        primary.push(tmp);
        bitmask = bitmask ^ (1<<tmp);
    }
    cout<< res;
}



