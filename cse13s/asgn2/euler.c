#include "mathlib.h"

static int num_terms = 0; // var to track number of terms in series

// Calculates all terms of Euler's solution series and adds them together
// Returns summation of the Euler series
// No parameters taken
double pi_euler(void) {
    num_terms = 0;
    double term = 1.0;
    double sum = 0.0;
    for (double k = 1.0; absolute(term) > EPSILON;
         k += 1.0) { // continues until latest term < EPSILON
        term = 1 / (k * k); // each term is (one/k squared)
        sum += term;
        num_terms += 1;
    }
    sum *= 6;
    sum = sqrt_newton(sum); //multiply by six and square root to get pi
    return sum;
}

// Will return variable for number of terms counted
// Returns number of terms in series
// No parameters taken
int pi_euler_terms(void) {
    return num_terms;
}
