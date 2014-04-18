/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Juliana Leon <julianaleon8@gmail.com>
  *
  * @section Description
  *
  * Rubik's cube class header
  */

#ifndef RUBIK_HH
#define RUBIK_HH
#include <string>

/*
 * Rubik's cube class
 */
class Rubik {
    public:
        /*
         * Leftmost 5 bits are for identification. Rightmost for orientation
         * Orientations is given by X,Y,Z tuple represented with 3 bits 
         */
        unsigned char left[8];   //0 to 7 cubie
        unsigned char right[8];  //12 to 19 cubie
        unsigned char middle[4]; //8 to 11 cubie


	public:
        void turnLeftCW();
        void turnLeftCCW();
        void turnRightCW();
        void turnRightCCW();
        void turnTopCW();
        void turnTopCCW();
        void turnBottomCW();
        void turnBottomCCW();
        void turnFrontCW();
        void turnFrontCCW();
        void turnBackCW();
        void turnBackCCW();
    private:
        unsigned char swapXY(unsigned char);
        unsigned char swapXZ(unsigned char);
        unsigned char swapYZ(unsigned char);
        unsigned int getId(unsigned char);
        unsigned int getOrientation(unsigned char);
};

#endif
