/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Juliana Leon <julianaleon8@gmail.com>
  *
  * @section Description
  *
  * Rubik's cube node class definition 
  */

#include <string>
#include "rubiknode.hh"
#include "rubik.hh"

using namespace std;


/**
  * Class constructor
  */

RubikNode::RubikNode(Rubik *state, RubikNode *parent,
                     char action, int cost) {

    this->state = state;
    this->parent = parent;
    this->action = action;
    this->cost = cost;
};


/**
  * Initialize root node
  * @param 'state' : Rubik pointer that represents Rubik's cube 
  * @return root RubikNode
  */

RubikNode *RubikNode::init(Rubik *state) {
    this->state = state;
    this->parent = NULL;
    this->action = '\x00';
    this->cost = 0;
};


/**
  * Check if RubikNode is goal
  * @return True if state is a solved Rubik's cube. False in any other case
  */

bool RubikNode::isGoal() {
    return this->state->isSolved();
};


/**
  * Extract solution to solve Rubik's cube
  * @return Sequence of actions to solve Rubik's cube
  */

list<char> RubikNode::extractSolution() {
    list<char> path; 
    RubikNode *temp;
    temp = this->parent;
    while (temp != NULL) {
        path.push_back(this->action);
        temp = temp->parent;
    }
    return path;
};
