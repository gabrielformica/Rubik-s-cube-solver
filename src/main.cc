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
    rpd.initializeAllWithFiles(); 
    
    Rubik cube;
    cube.random();  //Random instance

    printf("\n\n-----------------------------------------------\n");
    printf("Solving this random Rubik's cube configuration: \n");
    cube.print();
    printf("-----------------------------------------------\n");

    Solution solution;
    solution = IDAstar(cube, rpd);
    print_solution(solution);
}
