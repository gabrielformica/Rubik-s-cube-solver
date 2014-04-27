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
        int getCCost(int);       //corners cost
    private:
        void initializeCorners();
        void initializeOrientations();

        Rubik goalForCorners();

        //Methods to rank corners permutation
        int rankC(Rubik);      
        int rankCIDs(Rubik);   //Auxiliar function to rankC
        int rankCO(Rubik);     //Auxiliar function to rankC

        //Methods to unrank corners permutation
        Rubik unrankC(int);
        Rubik unrankCIDs(int);     //Corners ID
        Rubik unrankCO(int);       //Corners Orientations
};

#endif
