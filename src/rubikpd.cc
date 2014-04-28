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
  * Initializes pattern database of corners configuration
  */

void Rubikpd::initializeCorners() {
    //initialize every cost in -1
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

        Rubik cube = unrankC(parent);
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
  * Initializes pattern database of edges configuration
  */

void Rubikpd::initializeEdges() {
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
  * Ranks a Rubik's cube partly by taking only corners
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
  * It uses rankAux from utils.hh to rank a permutation of 
  * integers into an integer
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
    return (rankAux(8, cornersid, inverse));  //rank a sequence of integers
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
  * It uses unrankAux from utils.hh to unrank an intenger into
  * a sequence of integers
  * from an integer value between 0 and 40319 (ranked ID permutation)
  * @param 'x' : permutation of corner IDs represented as an int
  * @return Rubik's cube configuration
  */

Rubik Rubikpd::unrankCIDs(int x) {
    Rubik cube;
    int inverse[8] = {0,1,2,3,4,5,6,7};
    int i;

    unrankAux(8, x, inverse);   //Put in inverse the unranked permutation

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


/**
  * Ranks a Rubik's cube partly by taking only edges  (edges1)
  * @param 'table' : Has what table is going to be used
  * @param 'cube'  : Rubik's cube configuration
  * @return Ranked permutation (value between 0 and 42.577.920)
  */

int Rubikpd::rankE(int table, Rubik cube) {
    int x = this->rankEIDs(table, cube);     //IDs permutation
    int y = this->rankEO(table, cube);       //Orientations permutation

    return x*(pow(2,6)) + y;
};


/**
  * Ranks a Rubik's cube partly by taking only six edges IDs
  * It uses rankAux from utils.hh to rank a permutation of 
  * integers into an integer
  * @param 'cube' : Rubik's cube configuration
  * @return IDs permutation (value between 0 and 665.279)
  */

int Rubikpd::rankEIDs(int table, Rubik cube) {
  int edgesid[6];
  int i;
  int k = 0;
  int n;
  //With table 2, first cubie is 8-th cubie 
  //int aux = (table-1)*8;     
  
  //Transforms a Rubik's cube into a permutation of edges1
  if (table == 1){
    i = 0; 
    n = 8;
    // the fist middle
    edgesid[4] = cube.getId(16)/2;
    edgesid[5] = (cube.getId(17)-1)/2;
 
    //Transforms a Rubik's cube into a permutation of edges2
  } else {
    i = 9; 
    n = 16;
    // the last middle 
    edgesid[4] = cube.getId(18)/2;;
    edgesid[5] = (cube.getId(19)-1)/2;;

  }
    while(i < n) {
      if (i % 2 == 1) {
	edgesid[k] = ((cube.getId(i))-1)/2 ;
	k++;
      }
      i++;
    }
  
  int inverse[6] = {0,1,2,3,4,5};
  return (rankAux(6, edgesid, inverse));  //rank a sequence of integers
};


/**
  * Ranks a Rubik's cube partly by taking only six edges orientations 
  * It uses rankAux from utils.hh to rank a permutation of 
  * integers into an integer
  * @param 'cube' : Rubik's cube configuration
  * @return IDs permutation (value between 0 and 63)
  */

int Rubikpd::rankEO(int table, Rubik cube) {
};


/**
  * Gets a Rubik's cube configuration without orientations (only IDs) 
  * It uses unrankAux from utils.hh to unrank an intenger into
  * a sequence of integers
  * from an integer value between 0 and 665.279 (ranked ID permutation)
  * @param 'x' : permutation of corner IDs represented as an int
  * @return Rubik's cube configuration
  */

Rubik Rubikpd::unrankEIDs(int table, int x) {
  Rubik cube;
  int inverse[6] = {0,1,2,3,4,5};
  int i;
  int n;
  unrankAux(6, x, inverse);   //Put in inverse the unranked permutation
  
  //Transform sequence into a Rubik's cube configuration 
    if (table == 1){
      i = 0; 
      n = 4;
      cube.setCubie(16,cubie);
      cube.setCubie(17,cubie);
      
    } else {
      i = 4;
      n = 8;
      cube.setCubie(18,cubie);
      cube.setCubie(19,cubie);	    
    }
    
    while (i < n) {
      unsigned char cubie = inverse[i];
      cube.setCubie(i*2+1, cubie);//i*2+1 because these are edges cubies
      i++;
    }
    
    return cube;
};
