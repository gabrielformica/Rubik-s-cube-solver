/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Juliana Leon <julianaleon8@gmail.com>
  *
  * @section Description
  *
  * Rubik's cube pattern database class header
  */

#include <stdlib.h>
#include <list>
#include "rubikpd.hh"
#include "utils.hh"

using namespace std;


/**
  * Class constructor
  */

Rubikpd::Rubikpd() {};


/**
  * Gets cost of element 'i' in 'corners' array
  * @param 'i' : subindex
  * @return corners[i]
  */

int Rubikpd::getCCost(int i) {
    return this->corners[i];   
};


/**
  * Initializes corner pattern database
  */

void Rubikpd::initializeCorners() {
    int cost = 0;
    list<int> open;
    list<int> closed;

    open.push_back(this->rankC(this->goalForCorners()));

    while (!open.empty()) {
        int p = open.front();
        this->corners[p] = cost;
        Rubik *cube = this->unrankC(p);
        list<Rubik *> succ = cube->getSucc();
    }

};


/**
  * Returns the goal Rubik's cube for the corners
  * @return Rubik's cube configurations with solved corners
  */

Rubik *Rubikpd::goalForCorners() {
    Rubik *cube = new Rubik();

    int i;
    for (i = 0; i < 8; i++) {
        unsigned char id = i*2;
        id << 3;                //now id is in the right position

        unsigned char orientation = '\x01';
        if (i % 4 == 3) 
            orientation = '\x02';

        cube->setCubie(i*2, id || orientation);
    }

    return cube;
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
    swap(&seq[n-1], &seq[inverse[n-1]]);
    swap(&inverse[s], &inverse[n-1]);

    return s + n*(this->rankAux(n-1, seq, inverse));
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

    return x*(pow(3,8)) + y;
};


/**
  * Ranks a Rubik's cube partly by taking only corner IDs
  * It uses rankAux to rank a permutation of integers into an integer
  * @param 'cube' : Rubik's cube configuration
  * @return IDs permutation (value between 0 and 40319)
  */

int Rubikpd::rankCIDs(Rubik *cube) {
    int cornersid[8];
    int i;
    int k = 0;
    
    //Transforms a Rubik's cube into a permutation of corners
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
  * Ranks a Rubik's cube partly by taking only corner orientations 
  *
  * @section Description
  *
  * There are 3 orientations X,Y,Z: 100, 010, 001
  * And they are gonna be represent as 0,1, or 2
  * That's why % 4 is used!
  *
  * @param 'cube' : Rubik's cube configuration
  * @return Orientation permutations (value between 0 and 6560)
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
  * Unranks an corner permutation
  * @param 'p' : integer value between 0 and 264.539.519
  * @return Rubik's cube configuration with null values in edge cubies
  */

Rubik *Rubikpd::unrankC(int p) {
    int t = 6561;    //3^8
    Rubik *cube = new Rubik();
    Rubik *IDs = this->unrankCIDs(p / t);
    Rubik *orientations = this->unrankCO(p % t);
    
    int i;
    for (i = 0; i < 20; i++) {
        //Merge ID with orientation to get final cubie
        unsigned char cubie = IDs->getCubie(i) || orientations->getCubie(i);
        cube->setCubie(i, cubie);
    }

    free(IDs);
    free(orientations);
    return cube;
};
 

/**
  * Gets a Rubik's cube configuration without orientations (only IDs) 
  * from an integer value between 0 and 40319 (ranked ID permutation)
  * @param 'x' : permutation of corner IDs represented as an int
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
        cube->setCubie(i*2, cubie);       //i*2 because these are corner cubies
    }

    return cube;
};


/**
  * Gets a Rubik's cube configuration without IDs (only orientations)
  * from an integer value between 0 and 6560 (ranked orientation permutations)
  * @param 'x' : permutation of corner orientations represented as an integer
  * @return Rubik's cube configuration
  */

Rubik *Rubikpd::unrankCO(int x) {
    Rubik *cube = new Rubik();
    int y = x;
    int i;

    for (i = 0; i < 8; i++) {
        //calculate orientation of di with pure magic
        int di = y / pow(3, i);     
        y = y-(di*pow(3, i));     

        if (di == 0)
            di = 4;    //di was oriented to X-axis, wich is 100 in Rubik class

        unsigned char cubie = di; 
        cube->setCubie(i*2, cubie);
    }

    return cube;
};
