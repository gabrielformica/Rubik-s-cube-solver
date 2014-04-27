/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Juliana Leon <julianaleon8@gmail.com>
  *
  * @section Description
  *
  * Rubik's cube pattern database class header
  */

#include <list>
#include "rubikpd.hh"
#include "utils.hh"

using namespace std;


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
    //initialize every corner rank in -1
    int i;
    for (i = 0; i < 264539520; i++) 
        this->corners[i] = -1;

    int goal = this->rankC(this->goalForCorners());
    this->corners[goal] = 0;

    list<int> open;   //open queue
    open.push_back(goal);
    
    while (!open.empty()) {
        int parent = open.front();
        open.pop_front();                      

        Rubik cube = this->unrankC(parent);
        list<Rubik> s = cube.getSucc();    //Successors

        for (list<Rubik>::iterator it = s.begin(); it != s.end(); it++) {
            int child = this->rankC(*it);

            if (this->corners[child] != -1)   //Already closed or in open queue
                continue;
            
            this->corners[child] = this->corners[parent] + 1;
            open.push_back(child);
        }

    }

};


/**
  * Returns the goal Rubik's cube for the corners
  * @return Rubik's cube configurations with solved corners
  */

Rubik Rubikpd::goalForCorners() {
    Rubik cube;

    int i;
    for (i = 0; i < 8; i++) {
        unsigned char id = i*2;
        id << 3;                //now id is in the right position

        unsigned char orientation = '\x01';
        if (i % 4 == 3) 
            orientation = '\x02';

        cube.setCubie(i*2, id || orientation);
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

int Rubikpd::rankC(Rubik cube) {
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

int Rubikpd::rankCIDs(Rubik cube) {
    int cornersid[8];
    int i;
    int k = 0;
    
    //Transforms a Rubik's cube into a permutation of corners
    for(i = 0; i < 16; i++) {
        if (i % 2 == 0) {
            cornersid[k] = (cube.getId(i)) / 2;
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

int Rubikpd::rankCO(Rubik cube) {
    int rank = 0;
    int i;
    
    for (i = 0; i < 16; i++) {
        if (i % 2 == 0) {
            //represent orientations as 0,1, or 2
            int orientation = cube.getOrientation(i) % 4;
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

Rubik Rubikpd::unrankC(int p) {
    int t = 6561;    //3^8
    Rubik cube;  
    Rubik IDs = this->unrankCIDs(p / t);
    Rubik orientations = this->unrankCO(p % t);
    
    int i;
    for (i = 0; i < 20; i++) {
        //Merge ID with orientation to get final cubie
        unsigned char cubie = IDs.getCubie(i) || orientations.getCubie(i);
        cube.setCubie(i, cubie);
    }

    return cube;
};
 

/**
  * Gets a Rubik's cube configuration without orientations (only IDs) 
  * from an integer value between 0 and 40319 (ranked ID permutation)
  * @param 'x' : permutation of corner IDs represented as an int
  * @return Rubik's cube configuration
  */

Rubik Rubikpd::unrankCIDs(int x) {
    Rubik cube;
    int inverse[8] = {0,1,2,3,4,5,6,7};
    int i;

    unrankAux(8, x, inverse);

    //Transform sequence into a Rubik's cube configuration 
    for (i = 0; i < 8; i++) {
        unsigned char cubie = inverse[i];
        cube.setCubie(i*2, cubie);       //i*2 because these are corner cubies
    }

    return cube;
};


/**
  * Gets a Rubik's cube configuration without IDs (only orientations)
  * from an integer value between 0 and 6560 (ranked orientation permutations)
  * @param 'x' : permutation of corner orientations represented as an integer
  * @return Rubik's cube configuration
  */

Rubik Rubikpd::unrankCO(int x) {
    Rubik cube;
    int y = x;
    int i;

    for (i = 0; i < 8; i++) {
        //calculate orientation of di with pure magic
        int di = y / pow(3, i);     
        y = y-(di*pow(3, i));     

        if (di == 0)
            di = 4;    //di was oriented to X-axis, wich is 100 in Rubik class

        unsigned char cubie = di; 
        cube.setCubie(i*2, cubie);
    }

    return cube;
};
