#include <iostream>
#include "Graph.h"
#include <ctime>

int main() {


    Graph* test = new Graph();
    /*//test->menu();
    test->ReadFile("test.txt");
    clock_t start = clock();
    test->bruteForceTest(0,1);
    clock_t elapsed = clock() - start;
    cout<<endl<<(1000*elapsed)/CLOCKS_PER_SEC<<endl;
    test->showBestPath();*/

    test->ReadFile("test.txt");
    cout<<"File read"<<endl;
    clock_t start = clock();
    test->dynamicProgrammingTest();
    clock_t elapsed = clock() - start;
    cout<<endl<<"Time of completion: "<<(1000*elapsed)/CLOCKS_PER_SEC<<" [ms]"<<endl;
    test->trackPath();
    test->showBestPath(2);


/*
    clock_t start = clock();
    test->bruteForce(0);
    clock_t elapsed = clock() - start;
    cout<< (1000*elapsed)/CLOCKS_PER_SEC;
    test->showBestPath();*/

    return 0;
}