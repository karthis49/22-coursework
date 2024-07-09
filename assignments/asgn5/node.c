#include "node.h"
#include <stdlib.h>

// Constructs a node with a symbol and frequency
// Returns a pointer to a created node
//
// symbol: the symbol of a node
// frequency: how often a symbol appears in a file
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->symbol = symbol;
        n->frequency = frequency;
    }
    return n;
}

// Destructs a node, freeing memory
// Return type is void
//
// n: double pointer to free in function
void node_delete(Node **n) {
    if (*n) {
        free((*n)->left);
        free((*n)->right);
        free(*n);
        *n = NULL;
    }
    return;
}

// Joins two nodes to form a parent node
// Returns a newly constructed parent node
//
// left: left child of node
// right: right child of parent node
Node *node_join(Node *left, Node *right) {
    Node *parent;
    uint64_t sum = left->frequency + right->frequency;
    parent = node_create('$', sum);
    parent->left = left;
    parent->right = right;
    return parent;
}

void node_print(Node *n);
