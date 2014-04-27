/**
  * @file
  * @author Gabriel Formica <gabrielformica93@gmail.com>
  * @author Juliana Leon <julianaleon8@gmail.com>
  *
  * @section Description
  *
  * Useful functions
  */

#include "utils.hh"


/**
  * Swap two integer elements (pointers to integers)
  * @param 'x'   :   pointer to integer
  * @param 'y'   :   pointer to integer
  */

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
};


/**
  * Returns base raise to the power exponent
  * @param 'b'  :   base
  * @param 'e'  :   exponent
  * @return b^e
  */

int pow(int b, int e) {
    int i;

    int pow = 1;
    for (i = 1; i <= e; i++) {
        pow = pow*b;
    }
    
    return pow;
};


/**
  * Ranks an array (sequence) of int
  * @param 'n'  :   size of any of the permutations 
  * @param 'seq'    : sequence to be rakend
  * @param 'inverse': inverse of the identity
  * @return Ranked permutation int
  */ 

int rankAux(int n, int *seq, int *inverse) {

    if (n == 1)
        return 0;

    int s = seq [n-1];
    swap(&seq[n-1], &seq[inverse[n-1]]);
    swap(&inverse[s], &inverse[n-1]);

    return s + n*(rankAux(n-1, seq, inverse));
};


/**
  * Unranks an array (sequence) of int
  * @param 'n'         :   size of any of the permutations 
  * @param 'r'         :   ranked value to be unranked
  * @param 'identity'  :   identity permutation
  */

void unrankAux(int n, int r, int *identity) {

    if (n > 0) {
        int temp = identity[n-1];
        identity[n-1] = identity[r % n];
        identity[r % n] = temp;
        unrankAux(n-1, r / n, identity);
    }
};
