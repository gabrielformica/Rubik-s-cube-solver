/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Juliana Leon <julianaleon8@gmail.com>
  *
  * @section Description
  *
  * IDA* algorithm
  */

#include "idastar.hh"
#include "rubik.hh"
#include "rubiknode.hh"


/**
  * Bounded DFS
  * @param 'node'  :  A RubikNode element
  * @param 'cost'  :  Cost of the path
  */

void DFScontour(RubikNode *node, int cost) {
};


/**
  * IDA* algorithm
  * @param 'cube' : problem to be solved
  * @return Optimal solution      
  */


int IDAstar(Rubik problem) {
    RubikNode root;
    root.makeRootNode(problem);
    int cost = 0;

    while (1) {
        DFScontour(&root, cost);
        return cost;
    }
};

