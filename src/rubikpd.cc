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
  * @param 'n': 
  * 'seq':
  * 'inverse':
  * @return ID corners 
  */ 

int Rubikpd::rankAux(int n, int* seq, int * inverse){
  if (n = 1)
    return 0;
  int s = seq [n-1];
  int temp = seq[n - 1];
  seq[n-1] = seq[inverse[n-1]];
  seq[inverse[n-1]] = temp;
  temp = inverse[s];
  inverse[s] = inverse[n-1];
  inverse[n-1] = temp;
  return s + n*(this->rankAux(n-1,seq,inverse));
};
 
/**
  * Rank a Rubik's cube partly by taking only corners IDs
  * @param 'cube' : Rubik's cube configuration
  * @return IDs permutation (value between 0 and 40319)
  */

int Rubikpd::rankCIDs(Rubik *cube) {
  int cornersid[8];
  int i;
  int k = 0;
  for(i = 0; i < 16; i++) {
    if (i % 2 == 0) {
      unsigned char cubie = cube->getCubie(i);
      cornersid[k] = (cube->getId(cubie)) / 2;
      k++;
    }
  }
  int aux [8] = {0,1,2,3,4,5,6,7};
  return (this->rankAux(8,cornersid,aux));
};


/**
  * Rank a Rubik's cube partly by taking only corners orientations 
  *
  * @section Descriptionint i;
  for (i = 0; i < 8; i++ ){
      this->identityCID[i] = i;
  }
} 
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



