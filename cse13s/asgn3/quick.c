#include "quick.h"

// Partitions a given array using a pivot
// Returns a uint32_t, which is the index of the pivot
//
// stats: Stats struct used to track moves and compares
// A: array to be partitioned
// lo: uint32_t index of 1
// hi: uint32_t index of last element
uint32_t partition(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    uint32_t i = lo - 1;
    for (uint32_t j = lo; j < hi; j += 1) {
        if (cmp(stats, A[j - 1], A[hi - 1]) < 0) { // if A[j-1] < A[hi -1]
            i += 1;
            swap(stats, &A[i - 1],
                &A[j - 1]); // small values moved to left side, large values moved to right
        }
    }
    swap(stats, &A[i], &A[hi - 1]); //places pivot in the middle of the array
    return i + 1; //index of the pivot element
}

// Partitions and ecursively sorts the given array
// No return value (void)
//
// stats: Stats struct used to track moves and compares
// A: array to be sorted
// lo: uint32_t index of 1
// hi: uint32_t index of last element
void quick_sorter(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    if (lo < hi) {
        uint32_t p = partition(stats, A, lo, hi); // A is first partitioned
        quick_sorter(stats, A, lo, p - 1); // left half is sorted
        quick_sorter(stats, A, p + 1, hi); // right half is sorted
    }
}

// Sorts a given array using Quick sort algorithm
// No return value (void)
//
// stats: Stats struct used to track moves and compares
// A: array to be sorted by function
// n: length of array A
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n); // run quick sorter for given array A
}
