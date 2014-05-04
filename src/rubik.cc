/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Juliana Leon <julianaleon8@gmail.com>
  *
  * @section Description
  *
  * Rubik's cube class header
  */


#include <string>
#include <list>
#include "rubik.hh"

using namespace std;


/**
  * Set all cubies to '\x00'
  */

void Rubik::clean() {
    int i;
    for (i = 0; i < 20; i++)
        this->setCubie(i,'\x00');
};


/**
  * Convert this Rubik's cube configuration into the goal configuration
  */

void Rubik::transformToGoal() {
    int i;
    for (i = 0; i < 16; i++) {
        unsigned char position = i;
        position = position << 3;      //now position is in the right place

        unsigned char orientation = '\x01';
        if (i % 4 == 3) 
            orientation = '\x02';

        this->setCubie(i, position | orientation);
    }

    for (i = 16; i < 20; i++) {
        unsigned char position = i;
        position = position << 3;     //now position is in the right place
        unsigned char orientation = '\x01';
        this->setCubie(i, position | orientation);
    }
};


/**
  * Clones this Rubik's cube
  * @return A clone of this Rubik's cube
  */

Rubik Rubik::clone() {
    Rubik clone;
    int i;

    for (i = 0; i < 20; i++) {
        clone.setCubie(i, this->getCubie(i));
    }

    return clone;
};


/**
  * Sets the i-th cubie (or i % mod 20, if i >= 20)
  * @param 'i' : number of i-th cubie
  */

void Rubik::setCubie(int i, unsigned char cubie) {
    int j = i % 20;

    if ((j >= 0) && (j < 8)) 
        this->left[j]  = cubie;
    else if ((j >= 0) && (j < 16))
        this->right[j % 8] = cubie;
    else if ((j >= 0) && (j < 20))
        this->middle[j % 8] = cubie;
};


/**
  * Gets i-th cubie (or i % mod 20, if i >= 20)
  * @param 'i' : number of i-th cubie
  * @return The i-th Cubie, if i < 20. \xFF, in any other case
  */

unsigned char Rubik::getCubie(int i) {
    int j = i % 20;
    unsigned char cubie = '\xFF';

    if ((j >= 0) && (j < 8)) 
        cubie = this->left[j];
    else if ((j >= 0) && (j < 16))
        cubie = this->right[j % 8];
    else if ((j >= 0) && (j < 20))
        cubie = this->middle[j % 8];

    return cubie;
    
};


/**
  *
  */

void Rubik::changePositionTo(int i, int position) {
    unsigned char orientation;
    orientation = this->getOrientation(i); 
    unsigned char cubie = position;
    cubie = cubie << 3;  //Making place for orientation
    cubie = cubie | orientation;
    this->setCubie(i, cubie);
};


/**
  * Turns 90 degrees the left face clockwise
  */

void Rubik::turnLeft() { 
    //Look up for cubies that are in positions of the left face
    int i;
    for (i = 0; i < 20; i++) {
        if (this->getPosition(i) < 8) {
            this->setCubie(i, this->swapYZ(this->getCubie(i))); //swap in situ 
            int newposition = (this->getPosition(i) + 6) % 8;
            this->changePositionTo(i, newposition);
        }
    }
};


/**
  * Turns 90 degrees the right face clockwise
  */

void Rubik::turnRight() {
    //Look up for cubies that are in positions of the right face
    int i;
    for (i = 0; i < 20; i++) {
        if ((this->getPosition(i) >= 8) && (this->getPosition(i) < 16)) {
            this->setCubie(i, this->swapYZ(this->getCubie(i))); //swap in situ 
            int newposition = ((this->getPosition(i) + 6) % 8) + 8;
            this->changePositionTo(i, newposition);
        }
    }
};


/**
  * Turn 90 degrees the top face clockwise
  */

void Rubik::turnTop() {
    //Look up for cubies that are in positions of the top face
    int i;
    for (i = 0; i < 20; i++) {
        int newposition;
        int position = this->getPosition(i);
        switch (position) {
            case 4 :  newposition = 6; 
                      break;
            case 5 :  newposition = 18;
                      break;
            case 6 :  newposition = 12;
                      break;
            case 12:  newposition = 14;
                      break;
            case 13:  newposition = 17;
                      break;
            case 14:  newposition = 4;
                      break;
            case 17:  newposition = 5;
                      break;
            case 18:  newposition = 13;
                      break;
            default:  newposition = -1;  //This cubie isnt in position
                      break;
        }
        if (newposition != -1) {
            this->setCubie(i, this->swapXY(this->getCubie(i))); //swap in situ
            this->changePositionTo(i, newposition);
        }
    }
};


/**
  * Turns 90 degrees the bottom face clockwise
  */

void Rubik::turnBottom() {
    //Look up for cubies that are in positions of the top face
    int i;
    for (i = 0; i < 20; i++) {
        int newposition;
        int position = this->getPosition(i);
        switch (position) {
            case 0 : newposition = 2;
                     break;
            case 1 : newposition = 16;
                     break;
            case 2 : newposition = 8;
                     break;
            case 8 : newposition = 10;
                     break;
            case 9 : newposition = 19;
                     break;
            case 10: newposition = 0;
                     break;
            case 16: newposition = 9;
                     break;
            case 19: newposition = 1;
                     break;
            default: newposition = -1;
                     break;
        }
        if (newposition != -1) {
            this->setCubie(i, this->swapXY(this->getCubie(i))); //swap in situ
            this->changePositionTo(i, newposition);
        }
    }
};


/**
  * Turns 90 degrees the front face clockwise
  */

void Rubik::turnFront() {
    //Look up for cubies that are in positions of the top face
    int i;
    for (i = 0; i < 20; i++) {
        int newposition;
        int position = this->getPosition(i);
        switch (position) {
            case 2 : newposition = 4;
                     break;
            case 3 : newposition = 17;
                     break;
            case 4 : newposition = 14;
                     break;
            case 8 : newposition = 2;
                     break;
            case 14: newposition = 8;
                     break;
            case 15: newposition = 16;
                     break;
            case 16: newposition = 3;
                     break;
            case 17: newposition = 15;
                     break;
            default: newposition = -1;
                     break;
        }
        if (newposition != -1) {
            this->setCubie(i, this->swapXZ(this->getCubie(i)));  //swap in situ
            this->changePositionTo(i, newposition);
        }
    }
};


/**
  * Turns 90 degrees the back face clockwise
  */

void Rubik::turnBack() {
    //Look up for cubies that are in positions of the back face
    int i;
    for (i = 0; i < 20; i++) {
        int newposition;
        int position = this->getPosition(i);
        switch (position) {
            case 0 : newposition = 10;
                     break;
            case 6 : newposition = 0;
                     break;
            case 7 : newposition = 19;
                     break;
            case 10: newposition = 12;
                     break;
            case 11: newposition = 18;
                     break;
            case 12: newposition = 6;
                     break;
            case 18: newposition = 7;
                     break;
            case 19: newposition = 11;
                     break;
            default: newposition = -1;  //This cubie isnt in position
                     break;
        }
        if (newposition != -1) {
            this->setCubie(i, this->swapXZ(this->getCubie(i))); //swap in situ
            this->changePositionTo(i, newposition);
        }
    }
};


/**
  * Checks if cube is solved
  * @return True if cube is solved. False in any other case
  *
  * @section Description
  * The cube is correctly solved when:
  *         Cubie          Position        Orientation
  *     this->left[0]       00000            001             
  *     this->left[1]       00001            001             
  *     this->left[2]       00010            001
  *     this->left[3]       00011            010
  *     this->left[4]       00100            001
  *     this->left[5]       00101            001
  *     this->left[6]       00110            001
  *     this->left[7]       00111            010
  *
  *     this->Right[0]      01000            001             
  *     this->Right[1]      01001            001             
  *     this->Right[2]      01010            001
  *     this->Right[3]      01011            010
  *     this->Right[4]      01100            001
  *     this->Right[5]      01101            001
  *     this->Right[6]      01110            001
  *     this->Right[7]      01111            010
  *
  *     this->middle[0]     10000            001             
  *     this->middle[1]     10001            001             
  *     this->middle[2]     10010            001
  *     this->middle[3]     10011            001
  */

bool Rubik::isSolved() {
    int i;

    for (i = 0; i < 20; i++) {
        //check positions
        if (this->getPosition(i) != i) {
            return false;
        }

        //check orientations
        if (i < 16) {
            if ((this->getOrientation(i) != 2) && (i % 4 == 3))
                return false;
            
            if ((this->getOrientation(i) != 1) && (i % 4 != 3))
                return false;
        }
        else {
            if (this->getOrientation(i) != 1)
                return false;
        }
    }
    
    return true;
};


/**
  * Returns its 18 successors
  * @return The list of its 18 successor
  */

list<Rubik> Rubik::getSucc() {
    //Faces you can move
    void (Rubik::*moves[6]) () = {
        &Rubik::turnLeft,
        &Rubik::turnRight,
        &Rubik::turnTop,
        &Rubik::turnBottom,
        &Rubik::turnFront,
        &Rubik::turnBack,
    };

    list<Rubik> successors;

    int i;
    for (i = 0; i < 6; i++) {
        Rubik newcube;
        newcube = this->clone();  

        (newcube.*moves[i])();          //turn 90 degrees
        successors.push_back(newcube.clone());

        (newcube.*moves[i])();          //turn 180 degrees
        successors.push_back(newcube.clone());

        (newcube.*moves[i])();          //turn 270 or -90 degrees
        successors.push_back(newcube);   
    }
    
    return successors;
};


/**
  * Gets last 5 bits from i-th cubie 
  * @param 'i': i-th cubie
  * @return position 
  */

unsigned int Rubik::getPosition(int i) {
    unsigned char cubie = this->getCubie(i);
    return (int) (cubie >> 3);
}


/**
  * Gets last 5 bits from i-th cubie 
  * @param 'i': i-th cubie
  * @return orientation 
  */

unsigned int Rubik::getOrientation(int i) {
    unsigned char cubie = this->getCubie(i);
    return (int) (cubie & '\x07');
}


/**
  * Swaps X and Y axis
  * @param 'byte': unsigned char that represents position and orientation
  * @return new byte with same position but different orientation
  */

unsigned char Rubik::swapXY(unsigned char byte) {
    unsigned char x = byte & '\x04';
    unsigned char y = byte & '\x02';
    unsigned char z = byte & '\x01';
    unsigned char mask = '\xF8';          //11111 000
    unsigned char newbyte = byte & mask;
    x = x >> 1;
    y = y << 1;
    return newbyte | x | y | z;
}


/**
  * Swaps X and Z axis
  * @param 'byte': unsigned char that represents position and orientation
  * @return new byte with same position but different orientation
  */

unsigned char Rubik::swapXZ(unsigned char byte) {
    unsigned char x = byte & '\x04';
    unsigned char y = byte & '\x02';
    unsigned char z = byte & '\x01';
    unsigned char mask = '\xF8';          //11111 000
    unsigned char newbyte = byte & mask;
    x = x >> 2;
    z = z << 2;
    return newbyte | x | y | z;
}


/**
  * Swaps Y and Z axis
  * @param 'byte': unsigned char that represents position and orientation
  * @return new byte with same position but different orientation
  */

unsigned char Rubik::swapYZ(unsigned char byte) {
    unsigned char x = byte & '\x04';
    unsigned char y = byte & '\x02';
    unsigned char z = byte & '\x01';
    unsigned char mask = '\xF8';          //11111 000
    unsigned char newbyte = byte & mask;
    y = y >> 1;
    z = z << 1;
    return newbyte | x | y | z;
}
