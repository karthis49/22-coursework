#include "shell.h"

#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

// Sorts a given array using Shell sort algorithm
// No return value (void)
//
// stats: Stats struct used to track moves and compares
// A: array to be sorted by function
// n: length of array A
void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t *gaps = (uint32_t *) calloc(
        ((log(3.0 + (2.0 * n))) / log(3.0)), sizeof(uint32_t)); // array that will contain all gaps
    uint32_t index = 0; // used to access gaps array

    for (uint32_t exp = ((log(3.0 + (2.0 * n))) / log(3.0)); exp > 0;
         exp -= 1) { // iterating through all exponents
        gaps[index] = floor(((pow(3, exp)) - 1) / 2); // gap is calculated with formula
        index += 1;
    }
    uint32_t len_gaps = index;
    index = 0; // index is reset

    for (index = 0; index < len_gaps; index += 1) { // iterate through gaps array
        for (uint32_t i = gaps[index]; i < n; i += 1) { // iterate from gap value to n
            uint32_t j = i;
            uint32_t temp = move(stats, A[i]);
            while (j >= gaps[index]
                   && cmp(stats, temp, A[j - gaps[index]]) < 0) { // if temp < A[j - gaps[index]]
                A[j] = move(stats, A[j - gaps[index]]);
                j -= gaps[index];
            }
            A[j] = move(stats, temp); // elements are shifted in array, similarly to Insertion sort
        }
    }
    free(gaps);
}
