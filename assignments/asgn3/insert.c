#include "insert.h"

#include "stats.h"

#include <stdint.h>

// Sorts a given array using Insertion sort algorithm
// No return value (void)
//
// stats: Stats struct used to track moves and compares
// A: array to be sorted by function
// n: length of array A
void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t i = 1; i < n; i += 1) { //go through length of array
        uint32_t j = i;
        uint32_t temp = move(stats, A[i]); // A[j] stored in temp variable
        while (j > 0 && cmp(stats, temp, A[j - 1]) < 0) { // if element < previous element
            A[j] = move(stats, A[j - 1]); // A[i] is set to previous element
            j -= 1;
        }
        A[j] = move(
            stats, temp); // A[j] is set to temp, elements are 'swapped' throughout whole array
    }
}
