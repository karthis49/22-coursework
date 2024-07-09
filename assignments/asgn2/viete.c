#include "mathlib.h"

static int num_factors = 0; // var to track number of factors in series

// Calculates all factors of the Viete series and mutiplies them together
// Returns product of the Viete series
// No parameters taken
double pi_viete(void) {
    num_factors = 0;
    double factor = 0.0;
    double product = 1.0;
    double numerator = sqrt_newton(2); // numerator of term when k is equal to one
    for (double k = 1.0; (1 - absolute(factor)) > EPSILON; k += 1.0) {
        // continues until difference between one and the  latest term < EPSILON
        if (k > 1) {
            double prev_numer = numerator; // save latest numerator
            numerator = 2; // two must be added with each iteration
            numerator = sqrt_newton(
                prev_numer + numerator); // update by taking square root of added terms
        }
        factor = numerator / 2.0; // each term is number / two
        product *= factor;
        num_factors += 1;
    }
    return 2.0 / product; // two over pi because viete product equals two over pi
}

// Will return variable for number of factors counted
// Returns number of factors in series
// No parameters taken
int pi_viete_factors(void) {
    return num_factors;
}
