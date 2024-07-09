#include <stdbool.h>
#include <inttypes.h>
#include "defines.h"

typedef struct {
    uint32_t top;
    uint8_t bits[MAX_CODE_SIZE];
} Code;

// Constructs a code with top and array bits
// Returns a created code
//
// No parameters
Code code_init(void) {
    Code c;
    c.top = 0;
    for (int i = 0; i < MAX_CODE_SIZE; i += 1) {
        c.bits[i] = 0;
    }
    return c;
}

// Returns the size of a code
// Returns a 32-bit int
//
// c: pointer to a code
uint32_t code_size(Code *c) {
    return c->top;
}

// Checks if a code is empty
// Returns boolean if this is true or not
//
// c: pointer to a code
bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    }
    return false;
}

// Checks if a code is full
// Returns boolean for if it is
//
// c: pointer to a code
bool code_full(Code *c) {
    if (c->top == ALPHABET) {
        return true;
    }
    return false;
}

// Sets a bit in bits to 1
// Returns a boolean if successful
//
// c: pointer to a code
// i: index to set
bool code_set_bit(Code *c, uint32_t i) {
    if (!(i < MAX_CODE_SIZE)) {
        return false;
    }
    c->bits[i / 8] |= (0x1 << i % 8);
    return true;
}

// Clears a bit in bits
// Returns a boolean if successeful
//
// c: pointer to a code
// i: index to clear
bool code_clr_bit(Code *c, uint32_t i) {
    if (!(i < MAX_CODE_SIZE)) {
        return false;
    }
    c->bits[i / 8] &= ~(0x1 << i % 8);
    return true;
}

// Gets a bit from bits at index
// Returna boolean if successful
//
// c: pointer to a code
// i: index to get
bool code_get_bit(Code *c, uint32_t i) {
    if (!(i < MAX_CODE_SIZE)) {
        return false;
    }
    return (c->bits[i / 8] >> i % 8) & 0x1;
}

// Pushes a bit onto code
// Returns boolean if successful
//
// c: pointer to a code
// bit: what to push
bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) {
        return false;
    }
    if (bit == 1) {
        code_set_bit(c, c->top);
        return true;
    } else {
        code_clr_bit(c, c->top);
        return true;
    }
}

// Pops a bit off code
// Returns boolean if successful
//
// c: pointer to a code
// bit: bit that is popped off
bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) {
        return false;
    }
    c->top -= 1; // decrement before or after pop?
    *bit = code_get_bit(c, c->top);
    return true;
}

void code_print(Code *c);
