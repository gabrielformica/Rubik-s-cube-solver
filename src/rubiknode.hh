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
        Rubik state;                  //cube
        RubikNode *parent;
        char action;
        int cost;
        std::list<RubikNode> children;

    public:
        void makeNode(Rubik,RubikNode *,char,int);
        void makeRootNode(Rubik state);
        bool isGoal();
        void generateChildren();
        std::list<char> extractSolution(); 
        int getCost();
        Rubik getState();
        std::list<RubikNode> getChildren();
};

#endif
