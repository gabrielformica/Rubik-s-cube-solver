/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Juliana Leon <julianaleon8@gmail.com>
  *
  * @section Description
  *
  * IDA* implementation
  */
 
#include <stdlib.h>
#include <stdio.h>
#include <climits>
#include "idastar.hh"
#include "rubiknode.hh"
#include "rubikpd.hh"
#include "rubik.hh"
#include "utils.hh"

using namespace std;

Rubikpd rpd;


/**
  * Bounded DFS
  * @param 'node'  :  A RubikNode element
  * @param 'cost'  :  Cost of the path
  */

Solution IDdfs(RubikNode node, int limit) {
    int gcost = node.getCost();
    int hcost = rpd.heuristic(node.getState());

    if (gcost + hcost > limit) {
        Solution sol;
        sol.cost = gcost + hcost;
        return sol;
    }

    if (node.isGoal()) {
        Solution sol;
        sol.path = node.extractSolution();
        sol.cost = gcost;
        return sol;
    }

    int newlimit = INT_MAX;
    int number_children = node.numberOfChildren();
    int i;
    for (i = 0; i < number_children; i++) {
        RubikNode node1 = node.getChild(i);
        Solution sol = IDdfs(node1, limit);
        if (! sol.path.empty()) 
            return sol;

        newlimit = min(sol.cost, newlimit);
    }

    Solution sol;

    sol.cost = newlimit;

    return sol;
    
};


/**
  * IDA* algorithm
  * @param 'cube' : problem to be solved
  * @return Optimal solution      
  */

Solution IDAstar(Rubik problem, Rubikpd pdb) {
    rpd = pdb;
    RubikNode node;
    node.makeRootNode(problem);
    int limit = rpd.heuristic(node.getState());

    while (limit < INT_MAX) {
        Solution sol = IDdfs(node, limit);
        if  (! sol.path.empty()) 
            return sol;
        limit  = sol.cost;
    }

    Solution fail;
    fail.cost = INT_MAX;

    return fail;
};


/**
  *  Print solution
  */

void print_solution(Solution solution) {
    //When cube can't be solved
    if (solution.cost == INT_MAX) {
        printf("The cube can't be solved\n");
        return;
    }

    int moves_maded = solution.path.size() - 1;
    printf("-------Total number of moves maded :  %d\n", moves_maded);
    for (list<char>::reverse_iterator it = solution.path.rbegin();
                              it != solution.path.rend();
                              ++it) {
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
