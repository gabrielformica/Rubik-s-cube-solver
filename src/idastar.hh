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

#include <list>
#include "rubik.hh" 
#include "rubiknode.hh"
#include "rubikpd.hh"

typedef struct Solution Solution;

struct Solution {
    std::list<char> path;
    int cost;
};

extern Solution *DFScontour(RubikNode *,int,Rubikpd);

extern Solution *IDAstar(Rubik,Rubikpd);

#endif
