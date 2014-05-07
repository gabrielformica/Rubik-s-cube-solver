/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Juliana Leon <julianaleon8@gmail.com>
  *
  * @section Description
  *
  * IDA* implementation
  */

#ifndef IDASTAR_HH 
#define IDASTAR_HH

#include "rubiknode.hh"
#include "rubik.hh"
#include "rubikpd.hh"
#include <list>


/*
 * IDA* class
 */
typedef struct Solution Solution;

struct Solution {
    std::list<char> path;
    int cost;
};


extern Solution IDdfs(RubikNode,int,Rubikpd);

extern Solution IDAstar(Rubik,Rubikpd);

extern void print_solution(Solution);

#endif
