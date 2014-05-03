/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Juliana Leon <julianaleon8@gmail.com>
  *
  * @section Description
  *
  * IDA* algorithm
  */

#include <climits>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <string>
#include "idastar.hh"
#include "rubik.hh"
#include "rubiknode.hh"

using namespace std;

/**
  * Bounded DFS
  * @param 'node'  :  A RubikNode element
  * @param 'cost'  :  Cost of the path
  */

Solution *DFScontour(RubikNode *node, int limit, Rubikpd rpd) {
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

        RubikNode node = *it;
        sol = DFScontour(&node, limit, rpd);
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
        sol = DFScontour(&node, limit, rpd);
        if  (! sol->path.empty())
            return sol;
    }
    return NULL;
};

