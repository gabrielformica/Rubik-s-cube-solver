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

void turnLeftCW() { 

}


/**
  * Turn 90 degrees the left face counterclockwise
  */

void turnLeftCCW() {

}


/**
  * Turn 90 degrees the right face clockwise
  */

void turnRightCW() {

}


/**
  * Turn 90 degrees the right face counterclockwise
  */

void turnRightCCW() {

}


/**
  * Turn 90 degrees the up face clockwise
  */

void turnUpCW() {

}


/**
  * Turn 90 degrees the up face counterclockwise
  */

void turnUpCCW() {

}


/**
  * Turn 90 degrees the down face clockwise
  */

void turnDownCW() {

}


/**
  * Turn 90 degrees the down face counterclockwise
  */

void turnDownCCW() {

}


/**
  * Turn 90 degrees the front face clockwise
  */

void turnFrontCW() {

}


/**
  * Turn 90 degrees the front face counterclockwise
  */

void turnFrontCCW() {

}


/**
  * Turn 90 degrees the back face clockwise
  */

void turnBackCW() {
    
}


/**
  * Turn 90 degrees the back face counterclockwise
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


/**
  * Swap X and Y axis
  * @param 'byte': unsigned char that represents position and orientation
  * @return new byte with same position but different orientation
  */

unsigned char swapXY(unsigned char byte) {

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
