#include "randstate.h"
#include <gmp.h>

gmp_randstate_t state;

// Initialize random state
// Return type void
//
// seed: random seed
void randstate_init(uint64_t seed) {
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
}

// Free/clear memory used by state
// Return type void
//
// void: no parameters
void randstate_clear(void) {
    gmp_randclear(state);
}
