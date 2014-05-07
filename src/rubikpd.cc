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
#include <stdio.h>
#include "rubikpd.hh"
#include "utils.hh"
#include "rubik.hh"

using namespace std;


/**
  * Returns the maximum value between the three pattern databases
  */

int Rubikpd::heuristic(Rubik cube) {
    int rankc = this->rankC(cube);
    int ranke1 = this->rankE(1, cube);
    int ranke2 = this->rankE(2, cube);

    int hcorners = this->corners[rankc];
    int he1 = this->edges1[ranke1];
    int he2 = this->edges2[ranke2];

    //Get maximum value
    int max;
    if ((hcorners >= he1) && (hcorners >= he2))
        max = hcorners;
    else if ((he1 >= hcorners) && (he1 >= he2))
        max = he1;
    else
        max = he2;

    return max;

};


/**
  * Initializes corners, edges1, and edges2 by reading binary files
  * @param 'c' :  file pointer to binary file of corners 
  * @param 'e1'  :  file pointer to binary file of edges1
  * @param 'e2'  :  file pointer to binary file of edges2
  */

void Rubikpd::initializeAllWithFiles() {
    this->initializeCornersWithFile();
    this->initializeEdgesWithFile(1);
    this->initializeEdgesWithFile(2);
};


/**
  * Initializes corners by reading corners.bin (binary file)
  */

void Rubikpd::initializeCornersWithFile() {
    FILE *fp;
    fp = fopen("corners.bin", "rb");

    int i;
    for (i = 0; i < 264539520; i++) {
        int x;
        fread(&x, sizeof(int), 1, fp);
        this->corners[i] = x;
    }

    fclose(fp);
};


/**
  * Initializes one array of edges by reading edges1.bin 
  * if table = 1, or edges2.bin if table == 2 
  * @param 'table' : 1 for edges1, 2 for edges2
  */

void Rubikpd::initializeEdgesWithFile(int table) {
    unsigned char *edges[2] = {this->edges1, this->edges2}; 
    int t = table - 1;  //index of edges

    FILE *fp;
    if (table == 1) 
        fp = fopen("edges1.bin", "rb");
    else 
        fp = fopen("edges2.bin", "rb");


    int i;
    for (i = 0; i < 42577920; i++) {
        int x;
        fread(&x, sizeof(int), 1, fp);
        edges[t][i] = x;
    }

    fclose(fp);
};


/**
  * Initializes corners, edges1, edges2
  */

void Rubikpd::initializeAll() {
    this->initializeCorners();
    this->initializeEdges(1);  //edges1  
    this->initializeEdges(2);  //edges2
};


/**
  * Initializes pattern database of corner permutations 
  */

void Rubikpd::initializeCorners() {
    //initialize every cost in 255 
    int i;
    for (i = 0; i < 264539520; i++) 
        this->corners[i] = '\xFF';  

    Rubik goalcube;
    goalcube.transformToGoal();
    int goal = this->rankC(goalcube);
    this->corners[goal] = 0;

    list<int> open;   //open queue
    open.push_back(goal);
    
    while (!open.empty()) {
        int parent = open.front();        //top
        open.pop_front();                 //pop 

        Rubik cube = this->unrankC(parent);
        list<Rubik> s = cube.getSucc();    //Successors

        for (list<Rubik>::iterator it = s.begin(); it != s.end(); it++) {
            int child = this->rankC(*it);

            //Already closed or in open queue
            if (this->corners[child] != '\xFF')  
                continue;
            
            this->corners[child] = this->corners[parent] + 1;
            open.push_back(child);
        }
    }

    //Printing to binary file corners.bin
    FILE *fp;
    fp = fopen("corners.bin","wb");

    for (i = 0; i < 264539520; i++) {
        int x = this->corners[i];
        fwrite(&x, sizeof(int), 1, fp);
    }

    fclose(fp); 

};


/**
  * Initializes pattern database of edge permutations 
  * @param 'table' : 1 for edges1, 2 for edges2
  */

void Rubikpd::initializeEdges(int table) {
    unsigned char *edges[2] = {this->edges1, this->edges2}; 
    int t = table - 1;  //index of edges

    //Default values
    int i;
    for (i = 0; i < 42577920; i++) {
        edges[t][i] = '\xFF';   
    }

    Rubik goalcube;
    goalcube.transformToGoal();
    int goal = this->rankE(table, goalcube);

    edges[t][goal] = 0;

    list<int> open;     //open queue for edges1
    open.push_back(goal);

    while (!open.empty()) {
        int parent = open.front();  //top
        open.pop_front();           //pop

        //Get cube
        Rubik cube = this->unrankE(table, parent);

        list<Rubik> s = cube.getSucc();  //successors

        for (list<Rubik>::iterator it = s.begin(); it != s.end(); it++) {
            int child = this->rankE(table, (*it));

            //Already close or in open queue
            if (edges[t][child] != '\xFF')
                continue;
            
            edges[t][child] = edges[t][parent] + 1;

            open.push_back(child);
        }
    }

    //Printing to binary file edges1.bin or edges2.bin
    FILE *fp;
    if (table == 1) 
        fp = fopen("edges1.bin","wb");
    else
        fp = fopen("edges2.bin","wb");

    for (i = 0; i < 42577920; i++) {
        int x = edges[t][i];
        fwrite(&x, sizeof(int), 1, fp);
    }

    fclose(fp); 
};


/**
  * Ranks a Rubik's cube partly by taking only corners
  * @param 'cube' : Rubik's cube configuration
  * @return Ranked permutation (value between 0 and 264.539.519)
  */

int Rubikpd::rankC(Rubik cube) {
    int x = this->rankCornersP(cube);     //Permutation of positions
    int y = this->rankCornersO(cube);     //Permutation of orientations

    return x*(pow(3,8)) + y;
};


/**
  * Ranks a Rubik's cube partly by taking only corner positions 
  * It uses rankAux from utils.hh to rank a permutation of 
  * integers into an integer
  * @param 'cube' : Rubik's cube configuration
  * @return Permutation of the corner positions (value between 0 and 40319)
  */

int Rubikpd::rankCornersP(Rubik cube) {
    int positions[8];
    int k = 0;
    
    //Transforms a Rubik's cube into a permutation of corners
    int i;
    for (i = 0; i < 16; i++) {
        if (i % 2 == 0) {
            positions[k] = (cube.getPosition(i)) / 2;
            k++;
        }
    }

    //Pre calculate inverse
    int inverse[8];
    for (i = 0; i < 8; i++)
      inverse[positions[i]] = i;

    return (rankAux(1, 8, positions, inverse));  //rank a sequence of integers
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

int Rubikpd::rankCornersO(Rubik cube) {
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
  * Unranks a permutation of corner cubies
  * @param 'p' : integer value between 0 and 264.539.519
  * @return Rubik's cube configuration with null values in edge cubies
  */

Rubik Rubikpd::unrankC(int p) {
    int t = 6561;    //3^8
    Rubik cube;  
    cube.clean();

    Rubik positions = this->unrankCornersP(p / t);
    Rubik orientations = this->unrankCornersO(p % t);
    
    int i;
    for (i = 0; i < 20; i++) {
        //Merge ID with orientation to get final cubie
        unsigned char cubie = positions.getCubie(i) | orientations.getCubie(i);
        cube.setCubie(i, cubie);
    }

    return cube;
};
 

/**
  * Gets a Rubik's cube configuration without orientations (only positions) 
  * It uses unrankAux from utils.hh to unrank an intenger into
  * a sequence of integers
  * from an integer value between 0 and 40319 (ranked ID permutation)
  * @param 'x' : permutation of corner positions represented as an int
  * @return Rubik's cube configuration
  */

Rubik Rubikpd::unrankCornersP(int x) {
    Rubik cube;
    cube.clean();
    int identity[8] = {0,1,2,3,4,5,6,7};
    int i;

    unrankAux(0, 8, x, identity);   //Put in identity the unranked permutation

    //Transform sequence into a Rubik's cube configuration 
    for (i = 0; i < 8; i++) {
        unsigned char cubie = identity[i]*2;
        cubie = cubie << 3;
        cube.setCubie(i*2, cubie);       //i*2 because these are corner cubies
    }

    return cube;
};


/**
  * Gets a Rubik's cube configuration without positions (only orientations)
  * from an integer value between 0 and 6560 (ranked orientation permutations)
  * @param 'x' : permutation of corner orientations represented as an integer
  * @return Rubik's cube configuration
  */

Rubik Rubikpd::unrankCornersO(int x) {
    Rubik cube;
    cube.clean();
    int y = x;
    int i;
    int k = 0;

    for (i = 7; i >= 0; i--) {
        //calculate orientation of di with pure magic
        int power = pow(3, i);
        int di = y / power;     
        y = y-(di*power);     

        if (di == 0)
            di = 4;    //di was oriented to X-axis, wich is 100 in Rubik class

        unsigned char cubie = di; 
        cube.setCubie(k*2, cubie);
        k++;
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
    int x = this->rankEdgesP(table, cube);     //Permutation of positions
    int y = this->rankEdgesO(table, cube);     //Permutation of orientations

    return x*(pow(2,6)) + y;
};


/**
  * Ranks a Rubik's cube partly by taking only the positions of six edges 
  * It uses rankAux from utils.hh to rank a permutation of 
  * integers into an integer
  *
  * @param 'table' : Table we are ranking (1 for edges1, or 2 for edges2)
  * @param 'cube'  : Rubik's cube configuration
  * @return Permutation of positions (value between 0 and 665.279)
  */

int Rubikpd::rankEdgesP(int table, Rubik cube) {
    int positions[6];

    //With table 2, first cubie is 8-th cubie 
    int offset = (table-1)*8;     
    int i;
    int k = 0;
    for (i = offset; i < 8 + offset; i++) {
        if (i % 2 != 0) {
            int p = cube.getPosition(i);
            int elem = p / 2;
            if (p > 16) {
                elem = p - 8;
            }
            positions[k] = elem;
            k++;
        }
    }

    //Same goes for edges in middle face
    int firstmiddle = 16 + (offset / 4); 
    k =  4;
    for (i = firstmiddle; i <= firstmiddle + 1; i++) {
        int p = cube.getPosition(i);
        int elem = p / 2;
        if (p > 16) {
            elem = p - 8;
        }
        positions[k] = elem;
        k++;
    }

    int set[12], inverse[12];
    this->auxiliaryRankEdgesP(positions, set, inverse);

    return (rankAux(6, 12, set, inverse));  //rank a sequence of integers
};


/**
  * Set the three elementes necessary to do k-permutations of an n-set
  * @param 'positions' :   K elements to be permuted
  * @param 'set'       :   Array of integers to be ranked
  * @param 'inverse'   :   Invers of set
  */

void Rubikpd::auxiliaryRankEdgesP(int *positions, int *set, int *inverse) {
    int i, k;
    //Get subset
    int appear[12];

    for (i = 0; i < 12; i++)
        appear[i] = 0;

    for (i = 0; i < 6; i++)
        appear[positions[i]] = 1;

    //Edgesid elements are the last K-elements 
    for (i = 6; i < 12; i++)    
        set[i] = positions[i % 6];

    k = 0;
    for (i = 0; i < 12; i++) {
        if (appear[i] == 0) {
            set[k] = i;
            k++;
        }
    }

    //Calculate inverse 
    for (i = 0; i < 12; i++)
        inverse[set[i]] = i;
};


/**
  * Ranks a Rubik's cube partly by taking only six edges orientations 
  *
  * @section Description
  * Edge cubies have only two possible directions in a certain position
  * @param 'cube' : Rubik's cube configuration
  * @return Permutation of orientations (value between 0 and 63)
  */

int Rubikpd::rankEdgesO(int table, Rubik cube) {
    int offset = (table-1)*8;
    int rank = 0;

    //Left or Right face
    int i;
    for (i = 1; i <= 7; i = i + 2) {
        if (cube.getOrientation(i + offset) == 4) 
            rank = rank + 1;
        rank = rank*2;
    }

    //Middle face
    for (i = 0; i < 2; i++) {
        if (cube.getOrientation(16 + i + (offset / 4)) == 2)
            rank = rank + 1;
        rank = rank * 2;
    }

    rank = rank / 2;

    return rank;
};


/**
  * Unranks a permutation of edge cubies
  * @param 'p' : integer value between 0 and 42.577.919
  * @return Rubik's cube configuration 
  */

Rubik Rubikpd::unrankE(int table, int p) {
    int t = 64;   //2^6
    Rubik cube;
    cube.clean();

    Rubik positions = this->unrankEdgesP(table, p / t);
    Rubik orientations = this->unrankEdgesO(table, p % t);

    int i;
    for (i = 0; i < 20; i++) {
        //Merge ID with orientation to get final cubie
        unsigned char cubie = positions.getCubie(i) | orientations.getCubie(i);
        cube.setCubie(i, cubie);
    }

    return cube;
};


/**
  * Gets a Rubik's cube configuration without orientations (only position) 
  * It uses unrankAux from utils.hh to unrank an intenger into
  * a sequence of integers
  * from an integer value between 0 and 665.279 (ranked permutation
  * of positions)
  * @param 'x' : permutation of corner positions represented as an int
  * @return Rubik's cube configuration
  */

Rubik Rubikpd::unrankEdgesP(int table, int x) {
    Rubik cube;
    cube.clean();
    
    int offset = (table-1)*8;
    int identity[12] = {0,1,2,3,4,5,6,7,8,9,10,11};

    unrankAux(6, 12, x, identity);

    //Transform sequence into a Rubik's cube configuration
    int k = 0;
    int i;
    for (i = 6; i < 10; i++) {
        unsigned char cubie = identity[i]*2 + 1;
        if (identity[i] >= 8) {
            cubie = identity[i] + 8;  
        }
        cubie = cubie << 3;
        cube.setCubie(k*2 + 1 + offset, cubie);
        k++;
    }
    
    int middle = 16 + (offset / 4);
    for (i = 10; i < 12; i++) {
        unsigned char cubie = identity[i]*2 + 1;
        if (identity[i] >= 8)
            cubie = identity[i] + 8;

        cubie = cubie << 3;
        cube.setCubie(middle, cubie);
        middle++;
    } 

    return cube;
};


/**
  * Gets a Rubik's cube configuration without positions (only orientations)
  * from an integer value between 0 and 63 (ranked orientation permutations)
  * @param 'x' : permutation of corner orientations represented as an integer
  * @return Rubik's cube configuration
  */

Rubik Rubikpd::unrankEdgesO(int table, int x) {
    Rubik cube;
    cube.clean();
    int i;
    int y = x;
    int offset = (table-1)*8;
    int k = 1 + offset;
    for (i = 5; i > 1; i--) {
        //calculate orientation of di with pure magic
        int power = pow(2, i);
        int di = y / power;
        y = y - (di*power);
        
        unsigned char cubie;

        if  ((k == 1 + offset) || (k == 5 + offset)) {
            cubie = 1;
            if (di == 1) 
                cubie = 4;
        }
        else if ((k == 3 + offset) || (k == 7 + offset)) {
            cubie = 2;
            if (di == 1) 
                cubie = 4;
        }

        cube.setCubie(k, cubie);
        k = k + 2;
    }

    //Last two cubies this->middle[x], this->middle[x+1]
    unsigned char cubie;
    int di = y / 2;
    y = y - (di*2);
    cubie = 1;
    if (di == 1)
        cubie = 2;

    cube.setCubie(16 + (offset /4), cubie);
    di = y;
    cubie = 1;
    if (di == 1)
        cubie = 2;
    
    cube.setCubie(17 + (offset /4), cubie);
    
    return cube;
};
