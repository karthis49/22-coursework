#include "node.h"
#include "pq.h"
#include "huffman.h"
#include "stack.h"
#include "io.h"
#include "header.h"
#include "defines.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <inttypes.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>

#define OPTIONS "hi:o:v" // : -> argument after option

// Runs full Huffman decoding
// Returns 0 if full program executed
//
// argc: argument counter
// argv: array of strings
int main(int argc, char **argv) {
    bool verbose = false;
    bool help = false;
    int infile = STDIN_FILENO; // file pointers
    int outfile = STDOUT_FILENO;

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': help = true; break;
        case 'i':
            infile = open(optarg, O_RDONLY); // input file to be used
            if (infile < 0) {
                perror("Error with use of input file"); // PRINT ERROR
                exit(0);
            }
            // can check outfile
            break;
        case 'o':
            outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC); // output file to be used
            if (outfile < 0) {
                perror("Error with use of output file"); // PRINT ERROR
                exit(0);
            }
            break;
        case 'v': verbose = true; break;
        default: break;
        }
    }

    if (help) {
        fprintf(stderr, "SYNOPSIS\n");
        fprintf(stderr, "   A Huffman decoder.\n");
        fprintf(stderr, "   Decompresses a file using the Huffman coding algorithm\n");
        fprintf(stderr, "USAGE\n");
        fprintf(stderr, "   .decode [-v] [-h] [-i infile] [-o outfile]\n");
        fprintf(stderr, "OPTIONS\n");
        fprintf(stderr, "   -h             Program usage and help.\n");
        fprintf(stderr, "   -v             Print compression statisitics.\n");
        fprintf(stderr, "   -i infile      Input file to decompress.\n");
        fprintf(stderr, "   -o outfile     Output of decompressed data.\n");
        exit(0);
    }

    Header h = { 0, 0, 0, 0 };
    read_bytes(infile, (uint8_t *) &h, sizeof(h));
    if (h.magic != MAGIC) {
        perror("Incorrect magic number");
        close(infile);
        close(outfile);
        exit(0);
    }
    fchmod(outfile, h.permissions);

    uint8_t tree_dump[h.tree_size];
    read_bytes(infile, tree_dump, h.tree_size); //read tree dump into array

    Node *root = rebuild_tree(h.tree_size, tree_dump);

    uint64_t decoded_syms = 0;
    uint8_t *bit = NULL;

    Node *curr = root;
    while (decoded_syms != h.file_size) {
        read_bit(infile, bit);
        if (*bit == 0) {
            curr = curr->left;
        }
        if (*bit == 1) {
            curr = curr->right;
        }
        if (curr->left == NULL && curr->right == NULL) { //leaf node
            write_bytes(outfile, &curr->symbol, 1);
            decoded_syms += 1;
            curr = root;
        }
    }

    if (verbose) {
        fprintf(stderr, "Compressed file size: %lu bytes\n", h.file_size);
        fprintf(stderr, "Decompressed file size: %lu bytes\n", bytes_written);
        fprintf(
            stderr, "Space saving: %lu%% \n", (100 * (1 - h.file_size / bytes_written))); //CHANGE
    }

    node_delete(&root);
    close(infile);
    close(outfile);
    return 0;
}
