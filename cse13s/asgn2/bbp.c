#include "mathlib.h"

static int num_terms = 0; // var to track number of terms in series

// Calculates all terms of the BBP series and adds them together
// Returns summation of the BBP series
// No parameters taken
double pi_bbp(void) {
    num_terms = 0;
    double term = 1.0;
    double sixteen_exp = 0.0;
    double sum = 0.0;
    for (double k = 0.0; absolute(term) > EPSILON;
         k += 1.0) { // continues until latest term < EPSILON
        double numerator
            = (k * ((120.0 * k) + 151.0) + 47.0); // the num./denom. separate from sixteen_exp
        double denominator = (k * (k * (k * ((512.0 * k) + 1024) + 712) + 194) + 15);
        if (k == 0.0) {
            sixteen_exp = 1.0;
        }
        if (k == 1.0) {
            sixteen_exp = (1.0 / (16.0));
        }
        if (k > 1) {
            double prev_sixteen_exp = sixteen_exp; // save latest term
            sixteen_exp = (1.0 / 16.0); // term to multiply by to get next sixteen_exp
            sixteen_exp = prev_sixteen_exp * sixteen_exp; //updated sixteen_exp
        }
        term = sixteen_exp * (numerator / denominator); // full term
        sum += term;
        num_terms += 1;
    }
    return sum;
}

// Will return variable for number of terms counted
// Returns number of terms in series
// No parameters taken
int pi_bbp_terms(void) {
    return num_terms;
}
