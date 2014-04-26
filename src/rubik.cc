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
#include "rubik.hh"
using namespace std;


/**
  * Class constructor
  */

Rubik::Rubik() {};


/**
  * Clones this Rubik's cube
  * @return A clone of this Rubik's cube
  */

Rubik *Rubik::clone() {
    Rubik *clone = new Rubik();
    int i;

    for (i = 0; i < 8; i++) {
        clone->left[i] = this->left[i];
        clone->right[i] = this->right[i];
    }

    for (i = 0; i < 4; i++) {
        clone->middle[i] = this->middle[i];
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
  */

bool Rubik::isSolved() {
    return this->checkLeftFace() && 
           this->checkRightFace() && 
           this->checkMiddleFace();
};


/**
  * Checks that the left face is correctly solved
  * @return True if correctly solved. False in any other case
  *
  * @section Description
  * The left face is correctly solved when:
  *         Cubie           ID         Orientation
  *     this->left[0]     00000            001             
  *     this->left[1]     00001            001             
  *     this->left[2]     00010            001
  *     this->left[3]     00011            010
  *     this->left[4]     00100            001
  *     this->left[5]     00101            001
  *     this->left[6]     00110            001
  *     this->left[7]     00111            010
  */

bool Rubik::checkLeftFace() {
    int i;
    for (i = 0; i < 8 ; i++) {
        //check positions
        if (getId(this->left[i]) != i) 
            return false;

        //check orientations
        if ((i % 4 == 3) && (this->getOrientation(this->left[i]) != 2))
            return false;
        else if ((i % 4 != 3) && (this->getOrientation(this->left[i]) != 1))
            return false;
    } 

    return true;
}


/**
  * Checks that the right face is correctly solved
  * @return True if correctly solved. False in any other case
  *
  * @section Description
  * The right face is correctly solved when:
  *         Cubie           ID         Orientation
  *     this->Right[0]     01000            001             
  *     this->Right[1]     01001            001             
  *     this->Right[2]     01010            001
  *     this->Right[3]     01011            010
  *     this->Right[4]     01100            001
  *     this->Right[5]     01101            001
  *     this->Right[6]     01110            001
  *     this->Right[7]     01111            010
  */

bool Rubik::checkRightFace() {
    int i;

    for (i = 8; i < 16; i++) {
        //check positions
        if (getId(this->right[i % 8]) != i) 
            return false;
        
        //check orientations
        if ((i % 4 == 3) && (this->getOrientation(this->right[i % 8]) != 2))
            return false;
        else if ((i % 4 != 3) && (this->getOrientation(this->right[i % 8]) != 1))
            return false;
    }

    return true;
}


/**
  * Checks that the middle face is correctly solved
  * @return True if correctly solved. False in any other case
  *
  * @section Description
  * The middle face is correctly solved when:
  *         Cubie           ID         Orientation
  *     this->middle[0]     10000            001             
  *     this->middle[1]     10001            001             
  *     this->middle[2]     10010            001
  *     this->middle[3]     10011            001
  */

bool Rubik::checkMiddleFace() {
    int i;

    for (i = 16; i < 20; i++) {
        //check positions
        if (this->getId(this->middle[i % 8]) != i)
            return false;

        //check orientations
        if (this->getOrientation(this->middle[i % 8]) != 1) 
            return false;
    }

    return true;
}

/**
  * Gets last 5 bits from byte
  * @param 'byte': unsigned char that represents identification and orientation
  * @return identification
  */

unsigned int Rubik::getId(unsigned char byte) {
    return (int) byte >> 3;
}


/**
  * Gets last 5 bits from byte
  * @param 'byte': unsigned char that represents identification and orientation
  * @return orientation 
  */

unsigned int Rubik::getOrientation(unsigned char byte) {
    return (int) byte & '\x07';
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
