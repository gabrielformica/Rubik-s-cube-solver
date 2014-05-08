#include <climits>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "rubik.hh"
#include "rubiknode.hh"
#include "rubikpd.hh"
#include "idastar.hh"
#include "utils.hh"

using namespace std;

int main() {

    Rubikpd rpd;
    printf("\nInitializing pattern databases\n\n");
    //rpd.initializeAll();   //Uncomment this if there isn't precalculated rpd
    rpd.initializeAllWithFiles(); //Comment this if you uncomment initializeAll
    
    Rubik cube;
    cube.random();  //Random instance

    printf("-----------------------------------------------\n");
    printf("Solving this random Rubik's cube configuration: \n");
    cube.print();
    printf("-----------------------------------------------\n");

    Solution solution;

    solution = IDAstar(cube, rpd);

    print_solution(solution);
}
