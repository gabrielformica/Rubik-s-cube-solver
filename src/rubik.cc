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
  * Turn 90 degrees the left face clockwise
  */

void Rubik::turnLeftCW() { 

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
    //back up corners with new orientation
    unsigned char temp1 = this->left[6];
    unsigned char temp2 = this->right[6];

    //turn corners
    this->left[6] = this->swapXY(this->left[4]);    
    this->right[6] = this->swapXY(this->right[4]);

    this->left[4] = this->swapXY(temp2);
    this->right[4] = this->swapXY(temp1);

    //back up edges with new orientation
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
  * @param 'byte': unsigned char that represents position and orientation
  * @return position
  */

unsigned int getPosition(unsigned char byte) {
    return (int) byte >> 3;
}


/**
  * Get last 5 bits from byte
  * @param 'byte': unsigned char that represents position and orientation
  * @return orientation 
  */

unsigned int getOrientation(unsigned char byte) {
    return (int) byte & '\x07';
}


/**
  * Swap X and Y axis
  * @param 'byte': unsigned char that represents position and orientation
  * @return new byte with same position but different orientation
  */

unsigned char swapXY(unsigned char byte) {
    unsigned char x = byte & '\x04';
    unsigned char y = byte & '\x02';
    unsigned char z = byte & '\x01';
    unsigned char mask = '\xF8';          //11111 000
    unsigned char newbyte = byte & mask;
    x = x >> 1;
    y = y << 1;
    return newbyte = newbyte | x | y | z;
}


/**
  * Swap X and Z axis
  * @param 'byte': unsigned char that represents position and orientation
  * @return new byte with same position but different orientation
  */

unsigned char swapXZ(unsigned char byte) {

}


/**
  * Swap Y and Z axis
  * @param 'byte': unsigned char that represents position and orientation
  * @return new byte with same position but different orientation
  */

unsigned char swapYZ(unsigned char byte) {

}
