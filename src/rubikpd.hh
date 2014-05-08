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

#include <stdio.h>
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
        unsigned char corners[264539520];   

        /*
         * Cost of every Rubik's cube configuration taking only edges cubies
         * placed in the left face, and the first two cubies of the middle face
         * (middle[0], middle[1])
         * There are (12!/6!)x(2^6) = 42.577.920 possible configurations
         */
        unsigned char edges1[42577920];

        /*
         * Cost of every Rubik's cube configuration taking only edges cubies
         * placed in the right face, and the last two cubies of the middle face
         * (middle[2], middle[3])
         * There are (12!/6!)x(2^6) = 42.577.920 possible configurations
         */
        unsigned char edges2[42577920];
     
    public:
        int heuristic(Rubik);
        void initializeAll();
        void initializeAllWithFiles();
    private:
        void initializeCorners();
        void initializeEdges(int);
        void initializeCornersWithFile();
        void initializeEdgesWithFile(int);

        //Methods to rank permutation of corners cubies
        int rankC(Rubik);      
        int rankCornersP(Rubik);   //Auxiliary method to rankC
        int rankCornersO(Rubik);     //Auxiliary method to rankC

        //Methods to unrank permutation of corners cubies
        Rubik unrankC(int);
        Rubik unrankCornersP(int);     //Corner Positions 
        Rubik unrankCornersO(int);     //Corner Orientations

        //Methods to rank permutation of edges cubies in edges1
        int rankE(int,Rubik);
        int rankEdgesP(int,Rubik);
        void auxiliaryRankEdgesP(int *,int *,int *);
        int rankEdgesO(int,Rubik);

        //Methods to unrank permutation of edges cubies in edges1
        Rubik unrankE(int,int);
        Rubik unrankEdgesP(int,int);        //Edge Positions 
        Rubik unrankEdgesO(int,int,Rubik);  //Edge Orientations
};

#endif
