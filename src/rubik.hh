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
    private:
        unsigned char left[8];
        unsigned char right[8];
        unsigned char middle[4];
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
        unsigned int getPosition(unsigned char);
        unsigned int getOrientation(unsigned char);
};

#endif
