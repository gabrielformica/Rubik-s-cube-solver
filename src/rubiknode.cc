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

void RubikNode::makeNode(Rubik state, RubikNode *parent,
                     char action, int cost) {

    this->state = state;
    this->parent = parent;
    this->action = action;
    this->cost = cost;
};


/**
  * Initializes root node
  * @param 'state' : Rubik pointer that represents Rubik's cube 
  * @return root RubikNode
  */

void RubikNode::makeRootNode(Rubik state) {
    this->makeNode(state, NULL, '\x00',0);
};


/**
  * Checks if RubikNode is goal
  * @return True if state is a solved Rubik's cube. False in any other case
  */

bool RubikNode::isGoal() {
    return this->state.isSolved();
};


/**
  * Generates children of this node 
  *
  * @section Description
  *
  * generateChildren only generates good children.
  * It takes in count the action of the current Rubik node, reducing 
  * repeated nodes generation
  */

void RubikNode::generateChildren() {
    //Left, Right, Top, Bottom, Front, Back
    char faces[6] = {'L', 'R', 'T', 'B', 'F', 'Z'};

    int excl1 = -1;     //face to be excluded in faces array
    int excl2 = -1;     //face to be excluded in faces array

    switch (this->action) {
        case '\x00': break;                           //root node case
        case 'L':    excl1 = 0; excl2 = 0; break;     //action is left
        case 'R':    excl1 = 0; excl2 = 1; break;     //action is right
        case 'T':    excl1 = 2; excl2 = 2; break;     //action is top
        case 'B':    excl1 = 2; excl2 = 3; break;     //action is bottom
        case 'F':    excl1 = 4; excl2 = 4; break;     //action is front
        case 'Z':    excl1 = 4; excl2 = 5; break;     //action is back
    };

    list<Rubik> succ = this->state.getSucc();      //successors of cube
    list<RubikNode> children;                       //children of this node

    int i = 0;
    for (list<Rubik>::iterator it = succ.begin(); it != succ.end(); it++) {
        if ((i / 3) == excl1 || (i / 3) == excl2) {
            i++;
            continue;
        }
        RubikNode node;
        node.makeNode((*it), this, faces[i / 3], 0);
        children.push_back(node);
        i++;
    }

    this->children = children;
};


/**
  * Extracts solution to solve Rubik's cube
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


/**
  * Returns the cost of the path to this node
  * @return The cost of the path
  */

int RubikNode::getCost() {
    return this->cost;
};


/**
  * Returns state
  * @return this->state
  */

Rubik RubikNode::getState() {
    return this->state;
};


/**
  * Returns the list of children
  * @return this->children
  */

list<RubikNode> RubikNode::getChildren() {
    return this->children;
};
