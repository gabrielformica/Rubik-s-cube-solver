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
        unsigned char id = i;
        id = id << 3;                //now id is in the right position

        unsigned char orientation = '\x01';
        if (i % 4 == 3) 
            orientation = '\x02';

        this->setCubie(i, id | orientation);
    }

    for (i = 16; i < 20; i++) {
        unsigned char id = i;
        id = id << 3;                //now id is in the right position
        unsigned char orientation = '\x01';
        this->setCubie(i, id | orientation);
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
}


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
  * Turns 90 degrees the left face clockwise
  */

void Rubik::turnLeft() { 
    //back up corners position
    unsigned char temp1 = this->left[0];

    //turn corners
    this->left[0] = this->swapYZ(this->left[2]);    
    this->left[2] = this->swapYZ(this->left[4]);
    this->left[4] = this->swapYZ(this->left[6]);
    this->left[6] = this->swapYZ(temp1);
    
    //back up edges position
    temp1 = this->left[1];

    //turn edges
    this->left[1] = this->swapYZ(this->left[3]);
    this->left[3] = this->swapYZ(this->left[5]);
    this->left[5] = this->swapYZ(this->left[7]);
    this->left[7] = this->swapYZ(temp1);
}


/**
  * Turns 90 degrees the right face clockwise
  */

void Rubik::turnRight() {
    //back up corners position
    unsigned char temp1 = this->right[0];

    //turn corners
    this->right[0] = this->swapYZ(this->right[2]);    
    this->right[2] = this->swapYZ(this->right[4]);
    this->right[4] = this->swapYZ(this->right[6]);
    this->right[6] = this->swapYZ(temp1);
    
    //back up edges position
    temp1 = this->right[1];

    //turn edges
    this->right[1] = this->swapYZ(this->right[3]);
    this->right[3] = this->swapYZ(this->right[5]);
    this->right[5] = this->swapYZ(this->right[7]);
    this->right[7] = this->swapYZ(temp1);
}


/**
  * Turn 90 degrees the top face clockwise
  */

void Rubik::turnTop() {
    //back up corners
    unsigned char temp1 = this->left[6];
    unsigned char temp2 = this->right[6];

    //turn corners
    this->left[6] = this->swapXY(this->left[4]);    
    this->right[6] = this->swapXY(this->right[4]);

    this->left[4] = this->swapXY(temp2);
    this->right[4] = this->swapXY(temp1);

    //back up edges
    temp1 = this->middle[2];
    temp2 = this->right[5];

    //turn edges
    this->middle[2] = this->swapXY(this->left[5]);
    this->right[5] = this->swapXY(temp1);

    this->left[5] = this->swapXY(this->middle[1]);
    this->middle[1] = this->swapXY(temp2);
}


/**
  * Turns 90 degrees the bottom face clockwise
  */

void Rubik::turnBottom() {
    //back up corners
    unsigned char temp1 = this->left[2];
    unsigned char temp2 = this->right[2];

    //turn corners
    this->left[2] = this->swapXY(this->left[0]);    
    this->right[2] = this->swapXY(this->right[0]);

    this->left[0] = this->swapXY(temp2);
    this->right[0] = this->swapXY(temp1);

    //back up edges
    temp1 = this->middle[0];
    temp2 = this->right[1];

    //turn edges
    this->middle[0] = this->swapXY(this->left[1]);
    this->right[1] = this->swapXY(temp1);

    this->left[1] = this->swapXY(this->middle[3]);
    this->middle[3] = this->swapXY(temp2);
}


/**
  * Turns 90 degrees the front face clockwise
  */

void Rubik::turnFront() {
    //back up corners
    unsigned char temp1 = this->left[2];

    //turn corners
    this->left[2] = this->swapXZ(this->right[0]);
    this->right[0] = this->swapXZ(this->right[6]);
    this->right[6] = this->swapXZ(this->left[4]);
    this->left[4] = this->swapXZ(temp1);

    //back up edges
    temp1 = this->left[3];

    //turn edges
    this->left[3] = this->swapXZ(this->middle[0]);
    this->middle[0] = this->swapXZ(this->right[7]);
    this->right[7] = this->swapXZ(this->middle[1]);
    this->middle[1] = this->swapXZ(temp1);
}


/**
  * Turns 90 degrees the back face clockwise
  */

void Rubik::turnBack() {
    //back up corners
    unsigned char temp1 = this->right[2];

    //turn corners
    this->right[2] = this->swapXZ(this->left[0]);
    this->left[0] = this->swapXZ(this->left[6]);
    this->left[6] = this->swapXZ(this->right[4]);
    this->right[4] = this->swapXZ(temp1);

    //back up edges
    temp1 = this->right[3];

    //turn edges
    this->right[3] = this->swapXZ(this->middle[3]);
    this->middle[3] = this->swapXZ(this->left[7]);
    this->left[7] = this->swapXZ(this->middle[2]);
    this->middle[2] = this->swapXZ(temp1);
}


/**
  * Checks if cube is solved
  * @return True if cube is solved. False in any other case
  *
  * @section Description
  * The cube is correctly solved when:
  *         Cubie             ID         Orientation
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
        if (this->getId(i) != i) {
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
  * @param 'byte': unsigned char that represents identification and orientation
  * @return identification
  */

unsigned int Rubik::getId(int i) {
    unsigned char cubie = this->getCubie(i);
    return (int) (cubie >> 3);
}


/**
  * Gets last 5 bits from i-th cubie 
  * @param 'byte': unsigned char that represents identification and orientation
  * @return orientation 
  */

unsigned int Rubik::getOrientation(int i) {
    unsigned char cubie = this->getCubie(i);
    return (int) (cubie & '\x07');
}


/**
  * Swaps X and Y axis
  * @param 'byte': unsigned char that represents identification and orientation
  * @return new byte with same identification but different orientation
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
  * @param 'byte': unsigned char that represents identification and orientation
  * @return new byte with same identification but different orientation
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
  * @param 'byte': unsigned char that represents identification and orientation
  * @return new byte with same identification but different orientation
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
