#include "pq.h"
#include "node.h"
#include "huffman.h"
#include "stack.h"
#include <inttypes.h>
#include <stdlib.h>
#include "io.h"
#include <unistd.h>

// Constructs a Huffman tree given a histogram
// Returns a pointer to a node (root)
//
// hist: histogram to construct tree with
Node *build_tree(uint64_t hist[static ALPHABET]) {
    PriorityQueue *q = pq_create(ALPHABET);
    for (uint64_t i = 0; i < ALPHABET; i += 1) {
        if (hist[i] > 0) {
            Node *n = node_create(i, hist[i]);
            enqueue(q, n);
        }
    }
    while (pq_size(q) > 1) {
        Node *left, *right;
        dequeue(q, &left);
        dequeue(q, &right);
        Node *parent = node_join(left, right);
        enqueue(q, parent);
    }
    Node *root;
    dequeue(q, &root);
    pq_delete(&q);
    return root;
}

// Builds codes for a tree of nodes
// Return types is void
//
// root: pointer to root node of tree
// table: code table to be built
void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = { 0, { 0 } }; // local to function
    if (root != NULL) {
        if (root->left == NULL && root->right == NULL) {
            table[root->symbol] = c;
        } else {
            if (root->left != NULL) {
                uint8_t popped_bit;
                code_push_bit(&c, 0);
                build_codes(root->left, table);
                code_pop_bit(&c, &popped_bit);
            }
            if (root->right != NULL) {
                uint8_t popped_bit2;
                code_push_bit(&c, 0);
                build_codes(root->left, table);
                code_pop_bit(&c, &popped_bit2);
            }
        }
    }
}

// Creates a dump that represents a Huffman tree
// Return type is void
//
// outfile: file descriptor for output file
// root: pointer to root node of tree
void dump_tree(int outfile, Node *root) {
    if (root != NULL) {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);

        uint8_t leaf = 'L';
        uint8_t interior = 'I';

        if (root->left == NULL && root->right == NULL) { // no child
            write_bytes(outfile, &leaf, 1);
            write_bytes(outfile, &root->symbol, 1);
        } else {
            write_bytes(outfile, &interior, 1);
        }
    }
}

// Rebuilds a Huffman tree given a tree dump
// Returns a node pointer (to root of tree)
//
// nbytes: size of stack to be used
// tree: tree dump to be used to make tree
Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    Stack *s = stack_create(nbytes);
    for (uint16_t i = 0; i < nbytes; i += 1) {
        if (tree[i] == 'L') {
            Node *n = node_create(tree[i + 1], 0);
            stack_push(s, n);
        }
        if (tree[i] == 'I') {
            Node *right, *left;
            stack_pop(s, &right);
            stack_pop(s, &left);
            Node *parent = node_join(left, right);
            stack_push(s, parent);
        }
    }
    Node *root;
    stack_pop(s, &root);
    stack_delete(&s);
    return root;
}

// Deletes a Huffman tree, freeing memory
// Return type is void
//
// root: double pointer to root node that must be freed
void delete_tree(Node **root) {
    if (*root != NULL) {
        delete_tree(&(*root)->left);
        delete_tree(&(*root)->right);
        node_delete(root);
    }
}
