#include "node.h"
#include "ht.h"
#include "bst.h"
#include "salts.h"
#include "speck.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// number of lookups to HT (extern)
uint64_t lookups = 0; // set to 0

struct HashTable {
    uint64_t salt[2]; // salts needed
    uint32_t size; // size
    Node **trees; // array of BSTs
};

// Constructs a new HashTable
// Returns a pointer to a HashTable
//
// size: size of the HT
HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = SALT_HASHTABLE_LO;
        ht->salt[1] = SALT_HASHTABLE_HI;
        ht->size = size;
        ht->trees = (Node **) calloc(size, sizeof(Node *));
        for (uint32_t i = 0; i < size; i += 1) {
            // each index is an empty BST
            ht->trees[i] = bst_create();
        }
    }
    return ht;
}

// Frees all memory of a HT
// Return type void
//
// ht: double pointer to a Hashtable
void ht_delete(HashTable **ht) {
    for (uint32_t i = 0; i < (*ht)->size; i += 1) {
        // delete each tree
        bst_delete(&(*ht)->trees[i]);
    }
    free((*ht)->trees);
    free(*ht);
    *ht = NULL;
    return;
}

// Returns the size of a HT (32-bit unsigned int)
//
// ht: pointer to a HashTable
uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

// Check if node is in HT
// Returns pointer to (found) node
//
// ht: pointer to a HashTable
// CITE: Eugene (TA) explained this function in his 11/30 tutoring session
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    lookups += 1; //update lookups
    // index to look up
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    return bst_find(ht->trees[index], oldspeak);
}

// Inserts a node into the HT
// Return type void
//
// ht: pointer to a HashTable
// oldspeak: of the node to be inserted
// newspeak: of the node to be inserted
// CITE: Eugene (TA) explained this function in his 11/30 tutoring session
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    lookups += 1; //update lookups
    // index to look up
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    ht->trees[index] = bst_insert(ht->trees[index], oldspeak, newspeak);
}

// Returns the number of non-NULL BSTs in HT
// Returns a 32-bit unsigned int
//
// ht: pointer to a HashTable
uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht_size(ht); i += 1) {
        if (ht->trees[i] != NULL) {
            count += 1; // add up num. of non-NULL bsts
        }
    }
    return count;
}

// Calculates the avg BST size in the HT
// Returns a double
//
// ht: pointer to a HashTable
double ht_avg_bst_size(HashTable *ht) {
    uint32_t sum = 0;
    for (uint32_t i = 0; i < ht_size(ht); i += 1) {
        sum += bst_size(ht->trees[i]);
    }
    return (double) sum / ht_count(ht); // sum of sizes / count
}

// Calculates the avg BST height in a HT
// Returns a double
//
// ht: pointer to a HashTable
double ht_avg_bst_height(HashTable *ht) {
    uint32_t sum = 0;
    for (uint32_t i = 0; i < ht_size(ht); i += 1) {
        sum += bst_height(ht->trees[i]);
    }
    return (double) sum / ht_count(ht); // sum of heights / count
}

// Prints out the HT
// Return type void
//
// ht: pointer to a HashTable
void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i += 1) {
        node_print(ht->trees[i]);
    }
}
