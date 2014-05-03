/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Juliana Leon <julianaleon8@gmail.com>
  *
  * @section Description
  *
  * IDA* algorithm
  */

#ifndef IDASTAR_HH
#define IDASTAR_HH

#include <climits>
#include "rubik.hh" 
#include "rubik.hh"
#include "rubiknode.hh"
#include "rubikpd.hh"
#include <stdio.h>
#include <stdlib.h>
#include <list>

typedef struct Solution Solution;

struct Solution {
    std::list<char> path;
    int cost;
};

extern Solution *DFScontour(RubikNode *,int,Rubikpd);

extern Solution *IDAstar(Rubik,Rubikpd);

#endif
