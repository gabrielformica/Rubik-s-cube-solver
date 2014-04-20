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
  * Turn 90 degrees the left face clockwise
  */

void Rubik::turnLeftCW() { 
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
  * Turn 90 degrees the left face counterclockwise
  */

void Rubik::turnLeftCCW() {
    this->turnLeftCW();
    this->turnLeftCW();
    this->turnLeftCW();
}


/**
  * Turn 90 degrees the right face clockwise
  */

void Rubik::turnRightCW() {
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
  * Turn 90 degrees the right face counterclockwise
  */

void Rubik::turnRightCCW() {
    this->turnRightCW();
    this->turnRightCW();
    this->turnRightCW();
}


/**
  * Turn 90 degrees the top face clockwise
  */

void Rubik::turnTopCW() {
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
  * Turn 90 degrees the top face counterclockwise
  */

void Rubik::turnTopCCW() {
    this->turnTopCW();
    this->turnTopCW();
    this->turnTopCW();
}


/**
  * Turn 90 degrees the bottom face clockwise
  */

void Rubik::turnBottomCW() {
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
  * Turn 90 degrees the bottom face counterclockwise
  */

void Rubik::turnBottomCCW() {
    this->turnBottomCW();
    this->turnBottomCW();
    this->turnBottomCW();
}


/**
  * Turn 90 degrees the front face clockwise
  */

void Rubik::turnFrontCW() {
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
  * Turn 90 degrees the front face counterclockwise
  */

void Rubik::turnFrontCCW() {
    this->turnFrontCW();
    this->turnFrontCW();
    this->turnFrontCW();
}


/**
  * Turn 90 degrees the back face clockwise
  */

void Rubik::turnBackCW() {
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
  * Turn 90 degrees the back face counterclockwise
  */

void Rubik::turnBackCCW() {
    this->turnBackCW();
    this->turnBackCW();
    this->turnBackCW();
}


/**
  * Get last 5 bits from byte
  * @param 'byte': unsigned char that represents identification and orientation
  * @return identification
  */

unsigned int getId(unsigned char byte) {
    return (int) byte >> 3;
}


/**
  * Get last 5 bits from byte
  * @param 'byte': unsigned char that represents identification and orientation
  * @return orientation 
  */

unsigned int getOrientation(unsigned char byte) {
    return (int) byte & '\x07';
}


/**
  * Swap X and Y axis
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
  * Swap X and Z axis
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
  * Swap Y and Z axis
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
