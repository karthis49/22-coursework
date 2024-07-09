#include "mathlib.h"

static int num_terms = 0; // var to track number of terms in series

// Calculates all terms of the Taylor series to calculate e and adds them together
// Returns summation of the Taylor series
// No parameters taken
double e(void) {
    num_terms = 0;
    double term = 1.0;
    double sum = term;
    for (double k = 1.0; absolute(term) > EPSILON;
         k += 1.0) { // continues until latest term < EPSILON
        if (k == 1 || k == 2) { //term does not need to be updated yet
            term = 1 / k;
            sum += term;
            num_terms += 1;
        }
        if (k > 2) {
            double prev_term = term; // save latest term
            term = 1 / k; // new term to mutiply by
            term = prev_term * term; // update term
            sum += term;
            num_terms += 1;
        }
    }
    return sum;
}

// Will return variable for number of terms counted
// Returns number of terms in series
// No parameters taken
int e_terms(void) {
    return num_terms;
}
