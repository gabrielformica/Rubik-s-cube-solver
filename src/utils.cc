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
  * Returns the minimun of 'x' and 'y'
  * @param 'x' : integer
  * @param 'y' : integer
  * @return min(x,y) 
  */

int min(int x, int y) {
    if (x <= y)
        return x;
    return y;
};


/**
  * Returns the maximun of 'x' and 'y'
  * @param 'x' : integer
  * @param 'y' : integer
  * @return max(x,y)
  */

int max(int x, int y) {
    if (x >= y)
        return x;
    return y;
};


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
  * Ranks the sub-set in the permutation from n-k...n-1 
  * pieces of an array (sequence) of integers
  * @param 'k'  :   size of subset
  * @param 'n'  :   size of any of the permutations 
  * @param 'seq'    : sequence to be rakend
  * @param 'inverse': inverse of the identity
  * @return Int of ranked k-permutation
  */ 

int rankAux(int k, int n, int *seq, int *inverse) {

    if (n == k)
        return 0;

    int s = seq [n-1];
    swap(&seq[n-1], &seq[inverse[n-1]]);
    swap(&inverse[s], &inverse[n-1]);

    return s + n*(rankAux(k,n-1, seq, inverse));
};


/**
  * Unranks the subset of size k from n-k...n-1 of 
  * an array (sequence) of integers
  * @param 'k'  :   size of subset
  * @param 'n'         :   size of any of the permutations 
  * @param 'r'         :   ranked value to be unranked
  * @param 'identity'  :   identity permutation
  */

void unrankAux(int k, int n, int r, int *identity) {

    if (n > k) {
        int temp = identity[n-1];
        identity[n-1] = identity[r % n];
        identity[r % n] = temp;
        unrankAux(k,n-1, r / n, identity);
    }
};
