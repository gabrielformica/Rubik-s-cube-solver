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
  * Generate successors of a Rubik node
  * @return List of successors
  *
  * @section Description
  *
  * generateSucc only generates good successors.
  * It takes in count the action of the current Rubik node, reducing 
  * repeated nodes generation
  */

void RubikNode::generateSucc() {
    //Left, Right, Top, Bottom, Front, Back
    char faces[6] = {'L', 'R', 'T', 'B', 'F', 'Z'};

    void (Rubik::*moves[6]) () = {
        &Rubik::turnLeftCW,
        &Rubik::turnRightCW,
        &Rubik::turnTopCW,
        &Rubik::turnBottomCW,
        &Rubik::turnFrontCW,
        &Rubik::turnBackCW,
    };

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

    list<RubikNode *> successors;
    int i;

    for (i = 0; i < 6; i++) {
        if (i == excl1 || i == excl2)
            continue;

        Rubik *newcube= new Rubik();
        newcube = this->state->clone();  

        (newcube->*moves[i])();          //turn 90 degrees
        successors.push_back(new RubikNode(newcube->clone(), this, faces[i],0));

        (newcube->*moves[i])();          //turn 180 degrees
        successors.push_back(new RubikNode(newcube->clone(), this, faces[i],0));

        (newcube->*moves[i])();          //turn 270 or -90 degrees
        successors.push_back(new RubikNode(newcube->clone(), this, faces[i],0));
    }

    this->succ = successors;
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
