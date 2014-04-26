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
