#include "salts.h"
#include "bf.h"
#include <stdio.h>
#include <stdlib.h>
#include "speck.h"

struct BloomFilter {
    uint64_t primary[2]; // Primary hash function salt.
    uint64_t secondary[2]; // Secondary hash function salt.
    uint64_t tertiary[2]; // Tertiary hash function salt.
    BitVector *filter;
};

// Constructs a new Bloom Filter
// Returns a BloomFilter pointer to new BF
//
// size: size of the Bloom filter
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    bf->primary[0] = SALT_PRIMARY_LO;
    bf->primary[1] = SALT_PRIMARY_HI;
    bf->secondary[0] = SALT_SECONDARY_LO;
    bf->secondary[1] = SALT_SECONDARY_HI;
    bf->tertiary[0] = SALT_TERTIARY_LO;
    bf->tertiary[1] = SALT_TERTIARY_HI;
    bf->filter = bv_create(size);
    return bf; // return here
}

// Frees all memory related to Bloom Filter
// Return type void
//
// bf: double pointer to BF
void bf_delete(BloomFilter **bf) {
    if (*bf && (*bf)->filter) {
        bv_delete(&(*bf)->filter);
        free(*bf);
        *bf = NULL;
    }
    return;
}

// Returns the size of a bloom filter (32-bit unsigned int)
//
// bf: pointer to a Bloom Filter
uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

// Inserts oldspeak into the bloom filter
// Return type void
//
// bf: pointer to a Bloom Filter
// oldspeak: word to insert
void bf_insert(BloomFilter *bf, char *oldspeak) {
    // mod with size of bf
    uint32_t index1 = hash(bf->primary, oldspeak) % bf_size(bf);
    uint32_t index2 = hash(bf->secondary, oldspeak) % bf_size(bf);
    uint32_t index3 = hash(bf->tertiary, oldspeak) % bf_size(bf);
    bv_set_bit(bf->filter, index1);
    bv_set_bit(bf->filter, index2);
    bv_set_bit(bf->filter, index3);
}

// Check if a word is in the BF
// Returns boolean (if word is in it or not)
//
// bf: pointer to a Bloom Filter
// oldspeak: word to check
bool bf_probe(BloomFilter *bf, char *oldspeak) {
    uint32_t index1 = hash(bf->primary, oldspeak) % bf_size(bf);
    uint32_t index2 = hash(bf->secondary, oldspeak) % bf_size(bf);
    uint32_t index3 = hash(bf->tertiary, oldspeak) % bf_size(bf);
    if (bv_get_bit(bf->filter, index1) == true && bv_get_bit(bf->filter, index2) == true
        && bv_get_bit(bf->filter, index3) == true) { // if bits at all indices are set
        return true;
    }
    return false;
}

// Returns the number of set bits in BF
// Returns a 32-bit unsigned int
//
// bf: pointer to a Bloom Filter
uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < bf_size(bf); i += 1) { // iterate through filter
        if (bv_get_bit(bf->filter, i) == true) { // if bit in filter is set
            count += 1;
        }
    }
    return count;
}

// Prints out the BF (return type void)
//
// bf: pointer to a Bloom Filter
void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
