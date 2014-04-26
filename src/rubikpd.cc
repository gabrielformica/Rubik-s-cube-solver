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
  * Gets cost of element 'i' in corners array
  * @param 'i' : subindex
  * @return corners[i]
  */

int Rubikpd::getCCost(int i) {
    return this->corners[i];   
};


/**
  * Initializes corners pattern database
  */

void Rubikpd::initializeCorners() {

};


/**
  * Ranks an array (sequence) of int
  * @param 'n'  :   size of any of the permutations 
  * @param 'seq'    : sequence to be rakend
  * @param 'inverse': inverse of the identity
  * @return Ranked permutation int
  */ 

int Rubikpd::rankAux(int n, int *seq, int *inverse) {

    if (n == 1)
        return 0;
    int s = seq [n-1];
    
    //swap
    int temp = seq[n - 1];
    seq[n-1] = seq[inverse[n-1]];
    seq[inverse[n-1]] = temp;

    //swap
    temp = inverse[s];
    inverse[s] = inverse[n-1];
    inverse[n-1] = temp;

    return s + n*(this->rankAux(n-1,seq,inverse));
};


/**
  * Unranks an array (sequence) of int
  * @param 'n'         :   size of any of the permutations 
  * @param 'r'         :   ranked value to be unranked
  * @param 'identity'  :   identity permutation
  */

void Rubikpd::unrankAux(int n, int r, int *identity) {

    if (n > 0) {
        int temp = identity[n-1];
        identity[n-1] = identity[r % n];
        identity[r % n] = temp;
        this->unrankAux(n-1, r / n, identity);
    }
};


/**
  * Ranks a Rubik's cube 
  * @param 'cube' : Rubik's cube configuration
  * @return Ranked permutation (value between 0 and 264.539.519)
  */

int Rubikpd::rankC(Rubik *cube) {
    int x = this->rankCIDs(cube);     //IDs permutation
    int y = this->rankCO(cube);       //Orientations permutation

    return x*(3^8) + y;
};


/**
  * Ranks a Rubik's cube partly by taking only corners IDs
  * It uses rankAux to rank a permutation of integers into an integer
  * @param 'cube' : Rubik's cube configuration
  * @return IDs permutation (value between 0 and 40319)
  */

int Rubikpd::rankCIDs(Rubik *cube) {
    int cornersid[8];
    int i;
    int k = 0;
    
    //Transforms a Rubik's cube into a corners permutation 
    for(i = 0; i < 16; i++) {
        if (i % 2 == 0) {
            cornersid[k] = (cube->getId(i)) / 2;
            k++;
        }
    }

    int inverse[8] = {0,1,2,3,4,5,6,7};
    return (this->rankAux(8, cornersid, inverse));
};


/**
  * Ranks a Rubik's cube partly by taking only corners orientations 
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
            //represent orientations as 0,1, or 2
            int orientation = cube->getOrientation(i) % 4;
            rank = (rank*3) + orientation;
        }
    }

    return rank;
};


/**
  * Unranks an corners permutation
  * @param 'p' : integer value between 0 and 264.539.519
  * @return    : Rubik's cube configuration with null values in edges cubies
  */

Rubik *Rubikpd::unrankC(int p) {

};
 

/**
  * Gets a Rubik's cube configuration without orientations (only IDs) 
  * from an integer value between 0 and 40319
  * @param 'x' : corners IDs permutation represented as an int
  * @return Rubik's cube configuration
  */

Rubik *Rubikpd::unrankCIDs(int x) {
    Rubik *cube = new Rubik();
    int inverse[8] = {0,1,2,3,4,5,6,7};
    int i;

    unrankAux(8, x, inverse);

    //Transform sequence into a Rubik's cube configuration 
    for (i = 0; i < 8; i++) {
        unsigned char cubie = inverse[i];
        cube->setCubie(i*2,cubie);       //i*2 because these are corners cubies
        cube->setCubie((i*2)+1,'\x00');
    }

    return cube;
};


/**
  * Gets the corners orientations permutation represented as an integer between 
  * 0 and 6560 (3^8) of a corners permutation represented as an 
  * integer between 0 and 264.539.519 (8!x3^8)
  * This is an auxiliar function that rankC uses
  * @param 'x' : corners permutation represented as an integer
  * @return The orientations permutation of 'x'
  */

Rubik *Rubikpd::unrankCO(int x) {
};


/**
  * Returns base raised to the power exponent
  * @param 'b'   :  base
  * @param 'e'   :  exponent
  * @return b^e
  */

int Rubikpd::pow(int b, int e) {
    int i;

    int pow = 1;
    for (i = 1; i <= e; i++) {
        pow = pow*b;
    }
    
    return pow;
};
