#include "mathlib.h"

static int iters = 0; // var to track number of iterations to get root

// FUNCTION PSUEDOCODE COMES FROM PROFESSOR LONG
// Calculates square root using Newton-Raphson method
// Returns the square root of the parameter given
// x: the number whose square root will be taken
double sqrt_newton(double x) {
    iters = 0;
    double z = 0.0; // previous term
    double y = 1.0; // current term
    while (absolute(y - z) > EPSILON) {
        z = y; // store current as previous term
        y = 0.5 * (z + x / z); // will converge to result as iterating occurs
        iters += 1;
    }
    return y;
}

// Will return variable for number of iterations counted
// Returns number of iterations
// No parameters taken
int sqrt_newton_iters(void) {
    return iters;
}
