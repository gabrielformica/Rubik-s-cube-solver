/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Juliana Leon <julianaleon8@gmail.com>
  *
  * @section Description
  *
  * Rubik's cube pattern database class header
  */

#include "rubikpd.hh"


/**
  * Class constructor
  */

Rubikpd::Rubikpd() {};


/**
  * Get cost of element 'i' in corners array
  * @param 'i' : subindex
  * @return corners[i]
  */

int Rubikpd::getCCost(int i) {
    return this->corners[i];   
};


/**
  * Get the corners IDs permutation represented as an integer between 
  *     0 and 40319 (8!) of a corners permutation represented as an 
  *     integer between 0 and 264.539.520 (8!x3^8)
  * @param 'x' : corners permutation represented as an integer
  * @return The positions permutation of 'x'
  */

int Rubikpd::unrankCIDs(int x) {
    return x / (3^8);
};


/**
  * Get the corners orientations permutation represented as an integer between 
  *     0 and 6560 (3^8) of a corners permutation represented as an 
  *     integer between 0 and 264.539.520 (8!x3^8)
  * @param 'x' : corners permutation represented as an integer
  * @return The orientations permutation of 'x'
  */

int Rubikpd::unrankCO(int x) {
    return x % (3^8);
};


/**
  * Rank a Rubik's cube partly by taking only corners IDs
  * @param 'cube' : Rubik's cube configuration
  * @return IDs permutation (value between 0 and 40319)
  */

int Rubikpd::rankCIDs(Rubik *cube) {
};


/**
  * Rank a Rubik's cube partly by taking only corners orientations 
  *
  * @section Description
  * There are 3 orientations X,Y,Z: 100, 010, 001
  * And they are gonna be represent as 0,1, or 2
  * That's why % 4 is used!
  *
  * @param 'cube' : Rubik's cube configuration
  * @return Orientations permutations (value between 0 and 6560)
  */

int Rubikpd::rankCO(Rubik *cube) {
    int rank = 0;
    int i;
    
    for (i = 0; i < 16; i++) {
        if (i % 2 == 0) {
            unsigned char cubie = cube->getCubie(i);
            int orientation = cube->getOrientation(cubie) % 4;
            rank = (rank*3) + orientation;
        }
    }

    return rank;
};


/**
  * Rank a Rubik's cube 
  * @param 'cube' : Rubik's cube configuration
  * @return Ranked permutation (value between 0 and 264.539.520)
  */

int Rubikpd::rankC(Rubik *cube) {
    int x = this->rankCIDs(cube);     //IDs permutation
    int y = this->rankCO(cube);       //Orientations permutation
    return x*(3^8) + y;
};




