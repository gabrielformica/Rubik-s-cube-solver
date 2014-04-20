/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Juliana Leon <julianaleon8@gmail.com>
  *
  * @section Description
  *
  * Rubik's cube node class header
  */

#ifndef RUBIKTREE_HH
#define RUBIKTREE_HH

#include <list>
#include "rubik.hh"

/*
 * Rubik node class
 */
class RubikNode {
    private:
        Rubik *state;                  //cube
        RubikNode *parent;
        char action;
        int cost;
        std::list<RubikNode *> succ;  //successors

    public:
        RubikNode(Rubik *,RubikNode *,char,int);
        RubikNode *init(Rubik *state);
        bool isGoal();
        std::list<char> extractSolution(); 
};

#endif
