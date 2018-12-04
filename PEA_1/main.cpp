#include <iostream>
#include "Graph.h"
#include <ctime>
#include <chrono>

int main() {


    srand(time(NULL));
  Graph* test = new Graph();
  test->ReadFile("data58.txt");
  int least = 0; int min = INT32_MAX;
  for(int i = 0; i<15000; i++) {
      cout<<i<<endl;
      int result = test->simulatedAnnealing(1e38, 0.0001);
      if(min > result) min = result;

  }
  cout<<min;
  /*  test->ReadFile("test.txt");
    clock_t start = clock();
    test->bruteForceTest(0,1);
    clock_t elapsed = clock() - start;
    cout<<endl<<(1000*elapsed)/CLOCKS_PER_SEC<<endl;
    test->showBestPath();*/

    /*
    test->ReadFile("test.txt");
    cout<<"File read"<<endl;
    clock_t start = clock();
    test->dynamicProgrammingTest();
    clock_t elapsed = clock() - start;
    cout<<endl<<"Time of completion: "<<(1000*elapsed)/CLOCKS_PER_SEC<<" [ms]"<<endl;
    test->trackPath();
    test->showBestPath(2);
*/

/*
    clock_t start = clock();
    test->bruteForce(0);
    clock_t elapsed = clock() - start;
    cout<< (1000*elapsed)/CLOCKS_PER_SEC;
    test->showBestPath();*/

    return 0;
}