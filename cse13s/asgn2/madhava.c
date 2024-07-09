#include "mathlib.h"

static int num_terms = 0; // var to track number of terms in series

// Calculates all terms of the Madhava series and adds them together
// Returns summation of the Madhava series
// No parameters taken
double pi_madhava(void) {
    num_terms = 0;
    double term = 1.0;
    double sum = 1.0;
    double numerator = 0.0;
    double denominator = 0.0;
    for (double k = 1.0; absolute(term) > EPSILON;
         k += 1.0) { // continues until latest term < EPSILON
        if (k == 1.0) {
            numerator = (1 / -3.0); // each term's numer. will be neg. exp. of negative three
        }
        if (k > 1.0) {
            double prev_numer = numerator; // save last numer.
            numerator = (1.0 / (-3.0)); // new term to multiply by
            numerator = prev_numer * numerator; // update the numerator
        }
        denominator = (2 * k) + 1; // denominator always stays the same
        term = numerator / denominator; // each term will be the exp. over denominator
        sum += term;
        num_terms += 1;
    }
    sum *= sqrt_newton(12.0); // multiply by square root of twelve to get pi
    return sum;
}

// Will return variable for number of terms counted
// Returns number of terms in series
// No parameters taken
int pi_madhava_terms(void) {
    return num_terms;
}
