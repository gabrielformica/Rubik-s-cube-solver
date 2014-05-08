/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Juliana Leon <julianaleon8@gmail.com>
  *
  * @section Description
  *
  * Rubik's cube node class header
  */

#ifndef RUBIKNODE_HH
#define RUBIKNODE_HH

#include <list>
#include "rubik.hh"

/*
 * Rubik node class
 */
class RubikNode {
    private:
        Rubik state;
        RubikNode *parent;
        char action;
        int cost;

    public:
        void makeNode(Rubik,RubikNode *,char,int);
        void makeRootNode(Rubik state);
        bool isGoal();
        RubikNode getChild(int);
        int numberOfChildren();
        std::list<char> extractSolution(); 
        int getCost();
        Rubik getState();
};

#endif
