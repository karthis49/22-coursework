#include "heap.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

// Find index of parent node's max child
// Returns the index of the max child
//
// stats: Stats struct used to track moves and compares
// A: array to be sorted by function
// first: uint32_t which is the first index in array
// last: uint32_t which is the last index in array
uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first; // index of left child
    uint32_t right = left + 1; // index of right child
    if (right <= last && cmp(stats, A[right - 1], A[left - 1]) > 0) { //if A[right-1] > A[left-1}
        return right;
    }
    return left;
}

// Makes heap (array) follow properties of a max heap
// No return value (void)
//
// stats: Stats struct used to track moves and compares
// A: array to be sorted by function
// first: uint32_t which is the first index in array
// last: uint32_t which is the last index in array
void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t mother = first;
    uint32_t great = max_child(stats, A, mother, last); // index of max child of array A

    while (mother <= floor(last / 2) && !(found)) {
        if (cmp(stats, A[mother - 1], A[great - 1]) < 0) { // if A[mother-1] < A[great-1]
            swap(stats, &A[mother - 1], &A[great - 1]); // swap because child is greater than parent
            mother = great; // reset mother
            great = max_child(stats, A, mother, last); // reset great
        } else {
            found = true; // array is 'fixed'
        }
    }
}

// Builds the heap (array) by calling fix_heap()
// No return value (void)
//
// stats: Stats struct used to track moves and compares
// A: array to be sorted by function
// first: uint32_t which is the first index in array
// last: uint32_t which is the last index in array
void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t father = floor(last / 2); father > (first - 1);
         father -= 1) { //start from the middle of array
        fix_heap(stats, A, father, last); //fix by swapping parent and child if necessary
    }
}

// Sorts a given array using Heap sort algorithm
// No return value (void)
//
// stats: Stats struct used to track moves and compares
// A: array to be sorted by function
// n: length of array A
void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(stats, A, first, last); // build heap for given array, 1-based indexing
    for (uint32_t leaf = last; leaf > first; leaf -= 1) { //iterate from last element to first
        swap(stats, &A[first - 1],
            &A[leaf - 1]); // 'shrink' array by swapping first and last element
        fix_heap(stats, A, first, leaf - 1); // fix the remaining heap until everything is fixed
    }
}
