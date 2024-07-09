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

#define OPTIONS "hi:o:v" // :  argument expected after option

// Runs full Huffman encoding
// Returns 0 if full program executed
//
// argc: argument counter
// argv: array of strings
int main(int argc, char **argv) {
    bool verbose = false;
    bool help = false;
    int infile = STDIN_FILENO;
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
        fprintf(stderr, "   A Huffman encoder.\n");
        fprintf(stderr, "   Compresses a file using the Huffman coding algorithm\n");
        fprintf(stderr, "USAGE\n");
        fprintf(stderr, "   .encode [-v] [-h] [-i infile] [-o outfile]\n");
        fprintf(stderr, "OPTIONS\n");
        fprintf(stderr, "   -h             Program usage and help.\n");
        fprintf(stderr, "   -v             Print compression statisitics.\n");
        fprintf(stderr, "   -i infile      Input file to compress\n");
        fprintf(stderr, "   -o outfile     Output of compressed data\n");
        exit(0);
    }

    uint64_t hist[ALPHABET] = { 0 };
    uint8_t h_buffer[BLOCK] = { 0 };
    uint32_t uniq_symbols = 0;

    // for each symbol (256 ASCII chars), increment place in hist when char is found

    hist[0] += 1;
    hist[ALPHABET - 1] += 1;

    while ((bytes_read = read_bytes(infile, h_buffer, BLOCK)) > 0) {
        for (uint64_t i = 0; i < bytes_read; i += 1) {
            if (hist[h_buffer[i]] == 0) {
                uniq_symbols += 1;
            }
            hist[h_buffer[i]] += 1;
        }
    }

    Node *root = build_tree(hist);
    Code table[ALPHABET] = { 0 };
    build_codes(root, table);

    struct stat head_buf;
    fstat(infile, &head_buf);
    fchmod(outfile, head_buf.st_mode);

    Header h = { 0, 0, 0, 0 };
    h.magic = MAGIC;
    h.permissions = head_buf.st_mode;
    h.tree_size = 3 * uniq_symbols - 1;
    h.file_size = head_buf.st_size;
    write_bytes(outfile, (uint8_t *) &h, sizeof(h));

    uint64_t uncompressed = h.file_size; // to use for -v

    dump_tree(outfile, root);

    // new buff for codes
    uint8_t c_buffer[BLOCK] = { 0 };

    lseek(infile, 0, SEEK_SET);
    while ((bytes_read = read_bytes(infile, c_buffer, BLOCK)) > 0) {
        for (uint64_t i = 0; i < bytes_read; i += 1) {
            write_code(outfile, &table[c_buffer[i]]);
        }
    }
    flush_codes(outfile);

    if (verbose) {
        fprintf(stderr, "Uncompressed file size: %lu bytes\n", uncompressed);
        fprintf(stderr, "Compressed file size: %lu bytes\n", bytes_written);
        fprintf(stderr, "Space saving: %lu%% \n", (100 * (1 - bytes_written / uncompressed)));
    }

    delete_tree(&root);
    close(infile);
    close(outfile);

    return 0;
}
