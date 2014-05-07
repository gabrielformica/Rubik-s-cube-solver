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
  * Make a node
  * @param 'sate'  : Rubik's cube
  * @param 'parent': Pointer to RubikNode that represents the parent
  * @param 'action': Move maded by the parent 
  * @param 'cost'  : Cost of the root node to this node
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
  * @param 'state' : Rubik's cube 
  * @return Root RubikNode
  */

void RubikNode::makeRootNode(Rubik state) {
    this->makeNode(state, NULL, '\x00', 0);
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
  *
  * Actions are as follow:
  *    A  -> 90 degrees left face 
  *    B  -> 180 degrees left face
  *    C  -> -90 degrees  left face
  *    .
  *    .
  *    .
  *    P  -> 90 degrees back face
  *    Q  -> 180 degrees back face
  *    R  -> -90 degrees back face
  */

list<RubikNode> RubikNode::generateChildren() {
    //Left: ABC, Right: DEF, Top:GHI, Bottom:JKL, Front:MNO, Back:PQR
    char moves[18] = {
                'A', 'B', 'C',   //Moves for left face
                'D', 'E', 'F',   //Moves for right face
                'G', 'H', 'I',   //Moves for top face
                'J', 'K', 'L',   //Moves for bottom face
                'M', 'N', 'O',   //Moves for front face
                'P', 'Q', 'R',   //Moves for back face
    };

    int excl1 = -1;     //Used for excluding moves
    int excl2 = -1;     //Used for excluding moves

    switch (this->action) {
        case '\x00': break;    //root node case
        case 'A': case 'B': case 'C':  excl1 = 0; excl2 = 0; break;     
        case 'D': case 'E': case 'F':  excl1 = 0; excl2 = 1; break;  
        case 'G': case 'H': case 'I':  excl1 = 2; excl2 = 2; break; 
        case 'J': case 'K': case 'L':  excl1 = 2; excl2 = 3; break;
        case 'M': case 'N': case 'O':  excl1 = 4; excl2 = 4; break;  
        case 'P': case 'Q': case 'R':  excl1 = 4; excl2 = 5; break; 
    };

    list<Rubik> succ = this->state.getSucc();      //successors of cube
    list<RubikNode> children;                      //children of this node

    int i = 0;
    for (list<Rubik>::iterator it = succ.begin(); it != succ.end(); it++) {
        if ((i / 3) == excl1 || (i / 3) == excl2) {
            i++;
            continue;
        }
        RubikNode node;
        node.makeNode((*it), this, moves[i], this->cost + 1);
        children.push_back(node);
        i++;
    }

    return children;
};


/**
  * Gets i-th child
  * @param 'i'  :  valid i-th child
  * @return A valid child
  */

RubikNode RubikNode::getChild(int child) {
    //Left: ABC, Right: DEF, Top:GHI, Bottom:JKL, Front:MNO, Back:PQR
    char moves[18] = {
                'A', 'B', 'C',   //Moves for left face
                'D', 'E', 'F',   //Moves for right face
                'G', 'H', 'I',   //Moves for top face
                'J', 'K', 'L',   //Moves for bottom face
                'M', 'N', 'O',   //Moves for front face
                'P', 'Q', 'R',   //Moves for back face
    };

    int excl1 = -1;     //Used for excluding moves
    int excl2 = -1;     //Used for excluding moves

    switch (this->action) {
        case '\x00': break;    //root node case
        case 'A': case 'B': case 'C':  excl1 = 0; excl2 = 0; break;     
        case 'D': case 'E': case 'F':  excl1 = 0; excl2 = 1; break;  
        case 'G': case 'H': case 'I':  excl1 = 2; excl2 = 2; break; 
        case 'J': case 'K': case 'L':  excl1 = 2; excl2 = 3; break;
        case 'M': case 'N': case 'O':  excl1 = 4; excl2 = 4; break;  
        case 'P': case 'Q': case 'R':  excl1 = 4; excl2 = 5; break; 
    };

    int j;
    int i = -1;
    //Get what is the i-th child to this node!
    for (j = 0; j < 18 && i < child; j++) {
        if ((j/ 3) == excl1 || (j / 3) == excl2) {
            continue;
        }
        i++;
    }

    j--;   //Because the the move would be when i == child
    int face = j / 3;
    int times = (j % 3) + 1;  

    Rubik cube = this->state.clone();
    cube.turn(face, times);

    RubikNode node;
    node.makeNode(cube, this, moves[j], this->cost + 1);

    return node;
};


/**
  * Gets the number of valids children of this node
  * @return The number of children
  */

int RubikNode::numberOfChildren() {
    return this->generateChildren().size();
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
