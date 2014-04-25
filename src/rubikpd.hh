/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Juliana Leon <julianaleon8@gmail.com>
  *
  * @section Description
  *
  * Rubik's cube pattern database class header
  */

#ifndef RUBIKPD_HH
#define RUBIKPD_HH

#include "rubik.hh"

/*
 * Rubikpd class
 */
class Rubikpd {
    private:
        /*
         * Cost of every Rubik's cube configuration taking only corners cubies
         * There are 8!x3^8 = 264.539.520 possible configurations
         */
        int corners[264539520];   
     
    public:
        Rubikpd();
        int getCCost(int);       //corners cost
    private:
        int unrankCIDs(int);     //Corners ID
        int unrankCO(int);       //Corners Orientations
        int rankAux(int,int*,int*);     
        int rankCIDs(Rubik *);    
        int rankCO(Rubik *);
        int rankC(Rubik *);
       
  
};

#endif
