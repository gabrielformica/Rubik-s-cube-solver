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
  * Turn the left face clockwise
  */

void turnLeftCW() { 

}


/**
  * Turn the left face counterclockwise
  */

void turnLeftCCW() {

}


/**
  * Turn the right face clockwise
  */

void turnRightCW() {

}


/**
  * Turn the right face counterclockwise
  */

void turnRightCCW() {

}


/**
  * Turn the up face clockwise
  */

void turnUpCW() {

}


/**
  * Turn the up face counterclockwise
  */

void turnUpCCW() {

}


/**
  * Turn the down face clockwise
  */

void turnDownCW() {

}


/**
  * Turn the down face counterclockwise
  */

void turnDownCCW() {

}


/**
  * Turn the front face clockwise
  */

void turnFrontCW() {

}


/**
  * Turn the front face counterclockwise
  */

void turnFrontCCW() {

}


/**
  * Turn the back face clockwise
  */

void turnBackCW() {
    
}


/**
  * Turn the back face counterclockwise
  */

void turnBackCCW() {

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
