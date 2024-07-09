#include "bv.h"
#include <stdlib.h>
#include <stdio.h>

struct BitVector {
    uint32_t length; // length of bv
    uint8_t *vector; // array of u8_t's (bits)
};

// Constructs a new BitVector
// Returns BV pointer
//
// length: length of BitV
BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    if (bv) {
        bv->vector = (uint8_t *) calloc(length, sizeof(uint8_t));
        bv->length = length;
        return bv;
    } else {
        return NULL;
    }
}

// Frees all BV memory
// Return type void
//
// bv: double pointer to BitVector
void bv_delete(BitVector **bv) {
    if (*bv && (*bv)->vector) {
        free((*bv)->vector);
        free(*bv);
        *bv = NULL;
    }
    return;
}

// Returns the length of bit vector (32-bit unsigned int)
//
// bv: BitVector pointer
uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

// Sets bit in vector array
// Returns boolean (if successful)
//
// bv: BitVector pointer
// i: index to set
// CITE: Inspiration for function comes from Prof. Long's file bv8.c in Code Comments repo
bool bv_set_bit(BitVector *bv, uint32_t i) {
    if (!(i < bv->length)) {
        return false;
    }
    bv->vector[i / 8] |= (0x1 << i % 8);
    return true;
}

// Clears bit in vector array at index i
// Returns boolean (if successful)
//
// bv: BitVector pointer
// i: index to clear
// CITE: Inspiration for function comes from Prof. Long's file bv8.c in Code Comments repo
bool bv_clr_bit(BitVector *bv, uint32_t i) {
    if (!(i < bv->length)) {
        return false;
    }
    bv->vector[i / 8] &= ~(0x1 << i % 8);
    return true;
}

// Get value of bit (0 or 1) at index i
// Returns booleean (value of bit)
//
// bv: BitVector pointer
// i: index to get bit from
// CITE: Inspiration for function comes from Prof. Long's file bv8.c in Code Comments repo
bool bv_get_bit(BitVector *bv, uint32_t i) {
    if (!(i < bv->length)) {
        return false;
    }
    return (bv->vector[i / 8] >> i % 8) & 0x1;
}

// Prints out bit vector
// Return type void
//
// bv: BitVector pointer
void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv->length; i += 1) {
        if (bv_get_bit(bv, i) == true) {
            printf("%d", 1);
        } else {
            printf("%d", 0);
        }
    }
}
