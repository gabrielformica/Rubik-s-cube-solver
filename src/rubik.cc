/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Juliana Leon <julianaleon8@gmail.com>
  *
  * @section Description
  *
  * Rubik's cube class header
  */


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include "rubik.hh"

using namespace std;


/**
  * Sets all cubies to '\x00'
  */

void Rubik::clean() {
    int i;
    for (i = 0; i < 20; i++)
        this->setCubie(i,'\x00');
};


/**
  * Prints This Rubik's cube configuration
  */

void Rubik::print() {
    int i;
    printf("                     position          orientation\n");
    for (i = 0; i < 8; i++) {
        int position = this->getPosition(i);
        int orientation = this->getOrientation(i);
        printf("     Left[%d]   =         %d                   %d\n",
               i, position, orientation);
    }
    printf("\n");

    for (i = 8; i < 16; i++) {
        int position = this->getPosition(i);
        int orientation = this->getOrientation(i);
        printf("     Right[%d]   =        %d                   %d\n",
                i % 8, position, orientation);
    }

    printf("\n");

    for (i = 16; i < 20; i++) {
        int position = this->getPosition(i);
        int orientation = this->getOrientation(i);
        printf("     Middle[%d]   =       %d                   %d\n", 
               i % 8, position, orientation);
    }

    printf("\n");
};


/**
  * Converts this Rubik's cube configuration into the goal configuration
  */

void Rubik::transformToGoal() {
    int i;
    for (i = 0; i < 16; i++) {
        unsigned char position = i;
        position = position << 3;      //now position is in the right place

        unsigned char orientation = '\x01';
        if (i % 4 == 3) 
            orientation = '\x02';

        this->setCubie(i, position | orientation);
    }

    for (i = 16; i < 20; i++) {
        unsigned char position = i;
        position = position << 3;     //now position is in the right place
        unsigned char orientation = '\x01';
        this->setCubie(i, position | orientation);
    }
};


/**
  * Generates random Rubik's cube configuration
  */

void Rubik::random() {
    this->clean();
    this->transformToGoal();
    int moves = 50;

    int i;
    srand(time(NULL));
    int face = (rand() % 6) + 1;
    for (i = 0; i < moves; i++) {
        int random = rand();
        srand(random);
        face = (rand() % 6) + 1;
        int degrees = (rand() % 3) + 1;
        int j;
        for (j = 0; j < degrees; j++) {
            switch (face) {
                case 1 : this->turnLeft();
                         break;
                case 2 : this->turnRight();
                         break;
                case 3 : this->turnTop();
                         break;
                case 4 : this->turnBottom();
                         break;
                case 5 : this->turnFront();
                         break;
                case 6 : this->turnBack();
                         break;
            }
        }
    }
};


/**
  * Clones this Rubik's cube
  * @return A clone of this Rubik's cube
  */

Rubik Rubik::clone() {
    Rubik clone;
    int i;

    for (i = 0; i < 20; i++) {
        clone.setCubie(i, this->getCubie(i));
    }

    return clone;
};


/**
  * Sets the i-th cubie (or i % mod 20, if i >= 20)
  * @param 'i' : number of i-th cubie
  */

void Rubik::setCubie(int i, unsigned char cubie) {
    int j = i % 20;

    if ((j >= 0) && (j < 8)) 
        this->left[j]  = cubie;
    else if ((j >= 0) && (j < 16))
        this->right[j % 8] = cubie;
    else if ((j >= 0) && (j < 20))
        this->middle[j % 8] = cubie;
};


/**
  * Gets i-th cubie (or i % mod 20, if i >= 20)
  * @param 'i' : number of i-th cubie
  * @return The i-th Cubie, if i < 20. \xFF, in any other case
  */

unsigned char Rubik::getCubie(int i) {
    int j = i % 20;
    unsigned char cubie = '\xFF';

    if ((j >= 0) && (j < 8)) 
        cubie = this->left[j];
    else if ((j >= 0) && (j < 16))
        cubie = this->right[j % 8];
    else if ((j >= 0) && (j < 20))
        cubie = this->middle[j % 8];

    return cubie;
    
};


/**
  * Change position i i-th cubie to 'position'
  */

void Rubik::changePositionTo(int i, int position) {
    unsigned char orientation;
    orientation = this->getOrientation(i); 
    unsigned char cubie = position;
    cubie = cubie << 3;  //Making place for orientation
    cubie = cubie | orientation;
    this->setCubie(i, cubie);
};


/**
  * Turns the face 'times' times
  * @param 'face'    :     face to be moved
  * @param 'times'   :     times the face is gonna be moved (1,2,3)
  */

void Rubik::turn(int face, int times) {
    //Moves that can be maded
    void (Rubik::*moves[6]) () = {
      &Rubik::turnLeft,     
      &Rubik::turnRight, 
      &Rubik::turnTop,  
      &Rubik::turnBottom,
      &Rubik::turnFront,
      &Rubik::turnBack,
    };

    int i;
    for (i = 0; i < times; i++)
        (this->*moves[face])();

}


/**
  * Turns 90 degrees the left face clockwise
  */

void Rubik::turnLeft() { 
    //Look up for cubies that are in positions of the left face
    int i;
    for (i = 0; i < 20; i++) {
        if (this->getPosition(i) < 8) {
            this->setCubie(i, this->swapYZ(this->getCubie(i))); //swap in situ 
            int newposition = (this->getPosition(i) + 6) % 8;
            this->changePositionTo(i, newposition);
        }
    }
};


/**
  * Turns 90 degrees the right face clockwise
  */

void Rubik::turnRight() {
    //Look up for cubies that are in positions of the right face
    int i;
    for (i = 0; i < 20; i++) {
        if ((this->getPosition(i) >= 8) && (this->getPosition(i) < 16)) {
            this->setCubie(i, this->swapYZ(this->getCubie(i))); //swap in situ 
            int newposition = ((this->getPosition(i) + 6) % 8) + 8;
            this->changePositionTo(i, newposition);
        }
    }
};


/**
  * Turn 90 degrees the top face clockwise
  */

void Rubik::turnTop() {
    //Look up for cubies that are in positions of the top face
    int i;
    for (i = 0; i < 20; i++) {
        int newposition;
        int position = this->getPosition(i);
        switch (position) {
            case 4 :  newposition = 6; 
                      break;
            case 5 :  newposition = 18;
                      break;
            case 6 :  newposition = 12;
                      break;
            case 12:  newposition = 14;
                      break;
            case 13:  newposition = 17;
                      break;
            case 14:  newposition = 4;
                      break;
            case 17:  newposition = 5;
                      break;
            case 18:  newposition = 13;
                      break;
            default:  newposition = -1;  //This cubie isnt in position
                      break;
        }
        if (newposition != -1) {
            this->setCubie(i, this->swapXY(this->getCubie(i))); //swap in situ
            this->changePositionTo(i, newposition);
        }
    }
};


/**
  * Turns 90 degrees the bottom face clockwise
  */

void Rubik::turnBottom() {
    //Look up for cubies that are in positions of the top face
    int i;
    for (i = 0; i < 20; i++) {
        int newposition;
        int position = this->getPosition(i);
        switch (position) {
            case 0 : newposition = 2;
                     break;
            case 1 : newposition = 16;
                     break;
            case 2 : newposition = 8;
                     break;
            case 8 : newposition = 10;
                     break;
            case 9 : newposition = 19;
                     break;
            case 10: newposition = 0;
                     break;
            case 16: newposition = 9;
                     break;
            case 19: newposition = 1;
                     break;
            default: newposition = -1;
                     break;
        }
        if (newposition != -1) {
            this->setCubie(i, this->swapXY(this->getCubie(i))); //swap in situ
            this->changePositionTo(i, newposition);
        }
    }
};


/**
  * Turns 90 degrees the front face clockwise
  */

void Rubik::turnFront() {
    //Look up for cubies that are in positions of the top face
    int i;
    for (i = 0; i < 20; i++) {
        int newposition;
        int position = this->getPosition(i);
        switch (position) {
            case 2 : newposition = 4;
                     break;
            case 3 : newposition = 17;
                     break;
            case 4 : newposition = 14;
                     break;
            case 8 : newposition = 2;
                     break;
            case 14: newposition = 8;
                     break;
            case 15: newposition = 16;
                     break;
            case 16: newposition = 3;
                     break;
            case 17: newposition = 15;
                     break;
            default: newposition = -1;
                     break;
        }
        if (newposition != -1) {
            this->setCubie(i, this->swapXZ(this->getCubie(i)));  //swap in situ
            this->changePositionTo(i, newposition);
        }
    }
};


/**
  * Turns 90 degrees the back face clockwise
  */

void Rubik::turnBack() {
    //Look up for cubies that are in positions of the back face
    int i;
    for (i = 0; i < 20; i++) {
        int newposition;
        int position = this->getPosition(i);
        switch (position) {
            case 0 : newposition = 10;
                     break;
            case 6 : newposition = 0;
                     break;
            case 7 : newposition = 19;
                     break;
            case 10: newposition = 12;
                     break;
            case 11: newposition = 18;
                     break;
            case 12: newposition = 6;
                     break;
            case 18: newposition = 7;
                     break;
            case 19: newposition = 11;
                     break;
            default: newposition = -1;  //This cubie isnt in position
                     break;
        }
        if (newposition != -1) {
            this->setCubie(i, this->swapXZ(this->getCubie(i))); //swap in situ
            this->changePositionTo(i, newposition);
        }
    }
};


/**
  * Checks if cube is solved
  * @return True if cube is solved. False in any other case
  *
  * @section Description
  * The cube is correctly solved when:
  *         Cubie          Position        Orientation
  *     this->left[0]       00000            001             
  *     this->left[1]       00001            001             
  *     this->left[2]       00010            001
  *     this->left[3]       00011            010
  *     this->left[4]       00100            001
  *     this->left[5]       00101            001
  *     this->left[6]       00110            001
  *     this->left[7]       00111            010
  *
  *     this->Right[0]      01000            001             
  *     this->Right[1]      01001            001             
  *     this->Right[2]      01010            001
  *     this->Right[3]      01011            010
  *     this->Right[4]      01100            001
  *     this->Right[5]      01101            001
  *     this->Right[6]      01110            001
  *     this->Right[7]      01111            010
  *
  *     this->middle[0]     10000            001             
  *     this->middle[1]     10001            001             
  *     this->middle[2]     10010            001
  *     this->middle[3]     10011            001
  */

bool Rubik::isSolved() {
    int i;

    for (i = 0; i < 20; i++) {
        //check positions
        if (this->getPosition(i) != i) {
            return false;
        }

        //check orientations
        if (i < 16) {
            if ((this->getOrientation(i) != 2) && (i % 4 == 3))
                return false;
            
            if ((this->getOrientation(i) != 1) && (i % 4 != 3))
                return false;
        }
        else {
            if (this->getOrientation(i) != 1)
                return false;
        }
    }
    
    return true;
};


/**
  * Returns its 18 successors
  * @return The list of its 18 successor
  */

list<Rubik> Rubik::getSucc() {
    //Faces you can move
    void (Rubik::*moves[6]) () = {
        &Rubik::turnLeft,
        &Rubik::turnRight,
        &Rubik::turnTop,
        &Rubik::turnBottom,
        &Rubik::turnFront,
        &Rubik::turnBack,
    };

    list<Rubik> successors;

    int i;
    for (i = 0; i < 6; i++) {
        Rubik newcube;
        newcube = this->clone();  

        (newcube.*moves[i])();          //turn 90 degrees
        successors.push_back(newcube.clone());

        (newcube.*moves[i])();          //turn 180 degrees
        successors.push_back(newcube.clone());

        (newcube.*moves[i])();          //turn 270 or -90 degrees
        successors.push_back(newcube);   
    }
    
    return successors;
};


/**
  * Says if i-th cubie has its maximum value for orientation
  * @param 'i'  :   i-th cubie  
  * @return True, if its orientation is the max value. False in any other case
  */

bool Rubik::isMaxOriented(int i) {
    int position = this->getPosition(i);
    int orientation = this->getOrientation(i);

    if (position < 16) {
        if (orientation == 4)
            return true;
        return false;
    }
    else {
        if (orientation == 2)
            return true;
        return false;
    }
};


/**
  * Sets maximum orientation i-th cubie
  * @param 'i'  :  i-th edge cubie
  */

void Rubik::setMaxOrientation(int i) {
    int position = this->getPosition(i);
    unsigned char mask = '\xF8';  // 1111 1 000
    unsigned char cubie = this->getCubie(i) & mask;

    if (position < 16) {
        this->setCubie(i, cubie | '\x04');  //x-axis oriented
    }
    else {
        this->setCubie(i, cubie | '\x02');  //y-axis oriented
    }
};


/**
  * Sets minimun orientation i-th 
  * @param 'i'  :  i-th cubie
  */

void Rubik::setMinOrientation(int i) {
    int position = this->getPosition(i);
    unsigned char mask = '\xF8';  // 1111 1 000
    unsigned char cubie = this->getCubie(i) & mask;

    switch (position) {
        case 0: case 1: case 2: case 4: case 5: case 6:      //Left face
        case 8: case 9: case 10: case 12: case 13: case 14:  //Right face
        case 16: case 17: case 18: case 19:                  //Middle face
            this->setCubie(i, cubie | '\x01');    //z-axis oriented
            break;
        default :                                 //3 , 7, 11, 15
            this->setCubie(i, cubie | '\x02');
            break;
    }
};


/**
  * Gets last 5 bits from i-th cubie 
  * @param 'i': i-th cubie
  * @return position 
  */

unsigned int Rubik::getPosition(int i) {
    unsigned char cubie = this->getCubie(i);
    return (int) (cubie >> 3);
}


/**
  * Gets last 5 bits from i-th cubie 
  * @param 'i': i-th cubie
  * @return orientation 
  */

unsigned int Rubik::getOrientation(int i) {
    unsigned char cubie = this->getCubie(i);
    return (int) (cubie & '\x07');
}


/**
  * Swaps X and Y axis
  * @param 'byte': unsigned char that represents position and orientation
  * @return new byte with same position but different orientation
  */

unsigned char Rubik::swapXY(unsigned char byte) {
    unsigned char x = byte & '\x04';
    unsigned char y = byte & '\x02';
    unsigned char z = byte & '\x01';
    unsigned char mask = '\xF8';          //11111 000
    unsigned char newbyte = byte & mask;
    x = x >> 1;
    y = y << 1;
    return newbyte | x | y | z;
}


/**
  * Swaps X and Z axis
  * @param 'byte': unsigned char that represents position and orientation
  * @return new byte with same position but different orientation
  */

unsigned char Rubik::swapXZ(unsigned char byte) {
    unsigned char x = byte & '\x04';
    unsigned char y = byte & '\x02';
    unsigned char z = byte & '\x01';
    unsigned char mask = '\xF8';          //11111 000
    unsigned char newbyte = byte & mask;
    x = x >> 2;
    z = z << 2;
    return newbyte | x | y | z;
}


/**
  * Swaps Y and Z axis
  * @param 'byte': unsigned char that represents position and orientation
  * @return new byte with same position but different orientation
  */

unsigned char Rubik::swapYZ(unsigned char byte) {
    unsigned char x = byte & '\x04';
    unsigned char y = byte & '\x02';
    unsigned char z = byte & '\x01';
    unsigned char mask = '\xF8';          //11111 000
    unsigned char newbyte = byte & mask;
    y = y >> 1;
    z = z << 1;
    return newbyte | x | y | z;
}
