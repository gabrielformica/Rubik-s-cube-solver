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
  * Turn 90 degrees the up face clockwise
  */

void Rubik::turnTopCW() {

}


/**
  * Turn 90 degrees the up face counterclockwise
  */

void Rubik::turnTopCCW() {
    this->turnTopCW();
    this->turnTopCW();
    this->turnTopCW();
}


/**
  * Turn 90 degrees the down face clockwise
  */

void Rubik::turnBottomCW() {

}


/**
  * Turn 90 degrees the down face counterclockwise
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
