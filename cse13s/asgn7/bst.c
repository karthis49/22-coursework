#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

// Gets the max between 2 numbers
// Returns a 32-bit unsigned int
//
// x: first number to check
// y: second number to check
// CITE: Function comes from Prof. Long's Lecture 18 slide 55
static uint32_t max(uint32_t x, uint32_t y) {
    return x > y ? x : y;
}

// initial set of branches
uint64_t branches = 0;

// Constructs an empty BST
// Returns a node pointer (root of empty tree)
//
// No parameters
Node *bst_create(void) {
    return NULL;
}

// Calculates the height of a BST
// Returns a 32-bit unsigned int
//
// root: the node pointer to root of BST
// CITE: Function comes from Prof. Long's Lecture 18 slide 55
uint32_t bst_height(Node *root) {
    if (root) {
        return 1 + max(bst_height(root->left), bst_height(root->right));
    }
    return 0;
}

// Calculates the size of a BST
// Returns a 32-bit unsigned int
//
// root: the node pointer to root of BST
// CITE: Function inspired by bst_height() -> from Prof. Long's Lecture 18 slide 55
uint32_t bst_size(Node *root) {
    if (root == NULL) {
        return 0;
    } else { // root is not null
        return 1 + bst_size(root->left) + bst_size(root->right);
    }
}

// Finds a node in a BST
// Returns node pointer to found node or NULL
//
// root: the node pointer to root of BST
// CITE: Function comes/directly inspired from Prof. Long's Lecture 18 slide 57
Node *bst_find(Node *root, char *oldspeak) {
    if (root == NULL) {
        return NULL;
    }
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) > 0) { // root->old > old
            branches += 1;
            return bst_find(root->left, oldspeak);
        } else if (strcmp(root->oldspeak, oldspeak) < 0) { // root->old < old
            branches += 1;
            return bst_find(root->right, oldspeak);
        }
    }
    return root; // if root = node to be found, return root
}

// Inserts a node into a BST
// Returns the root of tree into which the node was inserted
//
// root: the node pointer to root of BST
// CITE: Function comes/directly inspired from Prof. Long's Lecture 18 slide 62
Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    if (root && oldspeak != NULL) {
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            branches += 1;
            root->left = bst_insert(root->left, oldspeak, newspeak);
        } else {
            branches += 1;
            root->right = bst_insert(root->right, oldspeak, newspeak);
        }
        return root;
    }
    return node_create(oldspeak, newspeak);
}

// Prints out a BST with inorder traversal
// Return type void
//
// root: the node pointer to root of BST
// CITE: Function comes/directly inspired from Prof. Long's Lecture 18 explanation and slides 22-34
void bst_print(Node *root) {
    if (root) {
        bst_print(root->left);
        node_print(root);
        bst_print(root->right);
    }
}

// Deletes a BST's memory with a postorder traversal
// Return type void
//
// root: the node pointer to root of BST
// CITE: Function comes/directly inspired from Prof. Long's Lecture 18 explanation and slides 79-85
void bst_delete(Node **root) {
    if (*root) {
        bst_delete(&(*root)->left);
        bst_delete(&(*root)->right);
        node_delete(&(*root));
    }
}
