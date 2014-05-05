#include <climits>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "rubik.hh"
#include "rubiknode.hh"
#include "rubikpd.hh"
#include "utils.hh"

using namespace std;

typedef struct Solution Solution;

struct Solution {
    std::list<char> path;
    int cost;
};


Solution *IDdfs(RubikNode *,int,Rubikpd);

Solution *IDAstar(Rubik,Rubikpd);

void print_solution(Solution *);

/**
  * Main function
  */

int main() {
    Rubikpd rpd;
    rpd.initializeAll();   //Uncomment this if there isn't precalculated rpd
    //rpd.initializeAllWithFiles(); //Comment this if you uncomment initializeAll
    Rubik cube;
    cube.random();  //Random instance

    Solution *solution;

    if ((solution = (Solution *) malloc(sizeof(Solution))) == NULL) {
        perror("Malloc Failed");
        exit(1);
    }

    solution = IDAstar(cube, rpd);

    print_solution(solution);
}


/**
  * Bounded DFS
  * @param 'node'  :  A RubikNode element
  * @param 'cost'  :  Cost of the path
  */

Solution *IDdfs(RubikNode *node, int limit, Rubikpd rpd) {
    Solution *sol;

    if ((sol = (Solution *) malloc(sizeof(Solution))) == NULL) {
        perror("Malloc Failed");
        exit(1);
    }

    int gcost = node->getCost();
    int hcost = rpd.heuristic(node->getState());

    if (gcost + hcost > limit) {
        sol->cost = gcost + hcost;
        return sol;
    }

    if (node->isGoal()) {
        sol->path = node->extractSolution();
        sol->cost = gcost;
        return sol;
    }

    node->generateChildren();
    list<RubikNode> children = node->getChildren();
    int newlimit = INT_MAX;
    for (list<RubikNode>::iterator it = children.begin(); 
                                    it != children.end(); 
                                    it++) {

        RubikNode node1 = *it;
        sol = IDdfs(&node1, limit, rpd);
        if (sol != NULL) 
            return sol;

        newlimit = min(newlimit, sol->cost);
    }
    return sol;
    
};


/**
  * IDA* algorithm
  * @param 'cube' : problem to be solved
  * @return Optimal solution      
  */

Solution *IDAstar(Rubik problem, Rubikpd rpd) {
    RubikNode node;
    node.makeRootNode(problem);
    int limit = rpd.heuristic(node.getState());

    while (node.getCost() < INT_MAX) {
        Solution *sol;
        sol = IDdfs(&node, limit, rpd);
        if  (! sol->path.empty())
            return sol;
    }
    return NULL;
};


/**
  *  Print solution
  */

void print_solution(Solution *solution) {
    if (solution == NULL) {
        printf("This cube can't be solved\n");
        return;
    }

    printf("-------Total number of moves maded :  %d\n",solution->path.size());

    for (list<char>::iterator it = solution->path.begin();
                              it != solution->path.end();
                              it++) {
        char move = *(it);
        switch (move) {
            //left face
            case 'A': printf("Move left face 90 degrees clockwise\n");
                      break;
            case 'B': printf("Move left face 180 degrees clockwise\n");
                      break;
            case 'C': printf("Move left face 90 degrees counter clockwise\n");
                      break;

            //right face
            case 'D': printf("Move right face 90 degrees clockwise\n");
                      break;
            case 'E': printf("Move right face 180 degrees clockwise\n");
                      break;
            case 'F': printf("Move right face 90 degrees counter clockwise\n");
                      break;

            //top face
            case 'G': printf("Move top face 90 degrees clockwise\n");
                      break;
            case 'H': printf("Move top face 180 degrees clockwise\n");
                      break;
            case 'I': printf("Move top face 90 degrees counter clockwise\n");
                      break;

            //bottom face
            case 'J': printf("Move bottom face 90 degrees clockwise\n");
                      break;
            case 'K': printf("Move bottom face 180 degrees clockwise\n");
                      break;
            case 'L': printf("Move bottom face 90 degrees counter clockwise\n");
                      break;

            //front face
            case 'M': printf("Move front face 90 degrees clockwise\n");
                      break;
            case 'N': printf("Move front face 180 degrees clockwise\n");
                      break;
            case 'O': printf("Move front face 90 degrees counter clockwise\n");
                      break;

            //back face
            case 'P': printf("Move back face 90 degrees clockwise\n");
                      break;
            case 'Q': printf("Move back face 180 degrees clockwise\n");
                      break;
            case 'R': printf("Move back face 90 degrees counter clockwise\n");
                      break;

        }
    }
}

