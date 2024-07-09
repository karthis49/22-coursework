#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <regex.h>
#include "node.h"
#include "bst.h"
#include "bf.h"
#include "bv.h"
#include "speck.h"
#include "ht.h"
#include "parser.h"
#include "salts.h"
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "messages.h"

#define OPTIONS "ht:f:s"

// regex expression
#define WORD "[A-Za-z0-9_]+(('|-)[A-Za-z0-9_]+)*"

// main function
// Returns 0
// argc: argument counter
// argv: array of strings
int main(int argc, char **argv) {
    bool help = false;
    bool invalid = false;
    bool stats = false;
    uint32_t ht_size = 65536; // default : 2^16
    uint32_t bf_size = 1048576; // default : 2^20

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': help = true; break;
        case 't':
            ht_size = strtoul(optarg, NULL, 10);
            // error check
            if (errno == EINVAL) { //-> set default value
                ht_size = 65536;
            }
            break;
        case 'f':
            bf_size = strtoul(optarg, NULL, 10);
            // error check
            if (errno == EINVAL) { //-> set default value
                bf_size = 1048576;
            }
            break;
        case 's': stats = true; break;
        default: invalid = true; break;
        }
    }

    // help message
    if (help || invalid) {
        fprintf(stderr, "SYNOPSIS\n");
        fprintf(stderr, "  A word filtering program for the GPRSC.\n");
        fprintf(stderr, "  Filters out and reports bad words parsed from stdin.\n");
        fprintf(stderr, "\n");
        fprintf(stderr, "USAGE\n");
        fprintf(stderr, "  ./banhammer [-hs] [-t size] [-f size]\n");
        fprintf(stderr, "\n");
        fprintf(stderr, "OPTIONS\n");
        fprintf(stderr, "  -h           Program usage and help.\n");
        fprintf(stderr, "  -s           Print program statistics.\n");
        fprintf(stderr, "  -t size      Specify hash table size (default: 2^16).\n");
        fprintf(stderr, "  -f size      Specify Bloom filter size (default: 2^20).\n");
        exit(0);
    }

    // Check BF and HT size (if valid)
    if (ht_size < 0 || ht_size == 0) {
        fprintf(stderr, "The hash table size is invalid");
        exit(1);
    }

    if (bf_size < 0 || bf_size == 0) {
        fprintf(stderr, "The bloom filter size is invalid");
        exit(1);
    }

    BloomFilter *bf = bf_create(bf_size);
    HashTable *ht = ht_create(ht_size);

    FILE *badsp;
    FILE *newsp;
    badsp = fopen("badspeak.txt", "r"); // open BS.txt
    newsp = fopen("newspeak.txt", "r"); // open NS.txt
    char bad_buf[1024];
    char old_buf[1024];
    char new_buf[1024];

    // scan each word and insert into BF and HT
    while (fscanf(badsp, "%s\n", bad_buf) != EOF) {
        bf_insert(bf, bad_buf);
        ht_insert(ht, bad_buf, NULL);
    }
    fclose(badsp);

    // scan each word pair and insert into BF and HT
    while (fscanf(newsp, "%s %s\n", old_buf, new_buf) != EOF) {
        bf_insert(bf, old_buf);
        ht_insert(ht, old_buf, new_buf);
    }
    fclose(newsp);

    // CITE: lines 102-106, 108, 111 come from parsing module in section 8 of asgn pdf

    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }

    char *word = NULL;
    Node *bad_bst = bst_create();
    Node *mixed_bst = bst_create();
    while ((word = next_word(stdin, &re)) != NULL) {
        // turn the word to lowercase
        for (size_t i = 0; i < strlen(word); i += 1) {
            word[i] = tolower(word[i]);
        }
        // word is in bloom filter
        if (bf_probe(bf, word) == true) {
            Node *check = ht_lookup(ht, word);
            // word is in ht but has newspeak -> mixed
            if (check != NULL && check->newspeak != NULL) {
                mixed_bst = bst_insert(mixed_bst, check->oldspeak, check->newspeak);
                // word is in ht but has no newspeak -> bad
            } else if (check != NULL && check->newspeak == NULL) {
                bad_bst = bst_insert(bad_bst, check->oldspeak, NULL);
            }
        }
    }
    clear_words();
    regfree(&re);

    if (stats) {
        fprintf(stderr, "Average BST size: %0.6f\n", ht_avg_bst_size(ht));
        fprintf(stderr, "Average BST height: %0.6f\n", ht_avg_bst_height(ht));
        fprintf(stderr, "Average branches traversed: %0.6f\n", (double) branches / lookups);
        double ht_load = (double) ht_count(ht) / ht_size;
        fprintf(stderr, "Hash table load: %0.6f%%\n", 100 * ht_load);
        double bf_load = (double) bf_count(bf) / bf_size;
        fprintf(stderr, "Bloom filter load: %0.6f%%\n", 100 * bf_load);
        exit(0);
    } else {
        // words with old->new and bad words => mixed
        if (bst_size(mixed_bst) > 0 && bst_size(bad_bst) > 0) {
            printf("%s", mixspeak_message);
            bst_print(bad_bst);
            bst_print(mixed_bst);
            // only bad words -> JOYCAMP
        } else if (bst_size(mixed_bst) == 0 && bst_size(bad_bst) > 0) {
            printf("%s", badspeak_message);
            bst_print(bad_bst);
            // only words with old->new => good
        } else if (bst_size(mixed_bst) > 0 && bst_size(bad_bst) == 0) {
            printf("%s", goodspeak_message);
            bst_print(mixed_bst);
        }
    }

    // delete everything
    bst_delete(&mixed_bst);
    bst_delete(&bad_bst);
    ht_delete(&ht);
    bf_delete(&bf);
    return 0;
}
