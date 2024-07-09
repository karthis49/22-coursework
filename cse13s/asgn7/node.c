#include "node.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Constructs a new Node
// Returns a pointer to a new Node
//
// oldspeak: oldspeak of the new node
// newspeak: newspeak of the new node
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    // check oldspeak
    if (oldspeak == NULL) {
        n->oldspeak = NULL; // null node
    } else {
        n->oldspeak = strdup(oldspeak);
    }

    // check newspeak
    if (newspeak == NULL) { // only has oldspeak
        n->newspeak = NULL;
    } else { // has old and new
        n->newspeak = strdup(newspeak);
    }

    n->left = n->right = NULL;
    return n;
}

// Frees all memory associated with a node
// Return type void
//
// n: double pointer to a node
void node_delete(Node **n) {
    if (*n) {
        free((*n)->oldspeak);
        free((*n)->newspeak);
        free(*n);
        *n = NULL;
    }
    return;
}

// Prints out the contents of a node
// Return type void
//
// n: pointer to a node
void node_print(Node *n) {
    // oldspeak is null, print nothing
    // oldspeak + newspeak
    if (n->oldspeak != NULL) {
        if (n->newspeak != NULL) {
            printf("%s -> %s\n", n->oldspeak, n->newspeak);
        }
        // only oldspeak
        else {
            printf("%s\n", n->oldspeak);
        }
    }
    return;
}
