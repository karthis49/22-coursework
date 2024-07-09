#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "aeisqr:n:p:h" // : -> argument after option

typedef enum { INSERTION, SHELL, HEAP, QUICK } Sorts;

// Main function, which will test the sorts
// Return value is 0, returns an integer
//
// No parameters
int main(int argc, char **argv) {
    Set s = empty_set();
    uint32_t seed = 13371453;
    uint32_t elements = 100;
    uint32_t print_elements = 100;
    bool no_print = true;
    bool help = false;
    bool no_input = true;
    bool bad_input = false;

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        no_input = false;
        switch (opt) {
        case 'a':
            s = insert_set(HEAP, s); // all sorts are inserted into set
            s = insert_set(SHELL, s);
            s = insert_set(INSERTION, s);
            s = insert_set(QUICK, s);
            break;
        case 'i': s = insert_set(INSERTION, s); break;
        case 'q': s = insert_set(QUICK, s); break;
        case 'e': s = insert_set(HEAP, s); break;
        case 's': s = insert_set(SHELL, s); break;
        case 'r':
            seed = strtoul(optarg, NULL, 10); //convert optarg to unsigned long
            if (errno == EINVAL) {
                seed = 13371453; // default seed
            }
            break;
        case 'n':
            elements = strtoul(optarg, NULL, 10); //convert optarg to unsigned long
            if (errno == EINVAL) {
                elements = 100; //default elements
            }
            break;
        case 'p':
            no_print = false;
            print_elements = strtoul(optarg, NULL, 10); //convert optarg to unsigned long
            if (errno == EINVAL) {
                print_elements = 100; // default print_elements
            }
            break;
        case 'h': help = true; break;
        default:
            bad_input = true; // will print help menu later
            break;
        }
    }

    Stats *stats = malloc(sizeof(Stats)); // allocate Stats struct, with moves/compares = 0
    stats->moves = 0;
    stats->compares = 0;

    srandom(seed); // generate psuedorandom numbers using seed
    uint32_t *A = (uint32_t *) calloc(elements, sizeof(uint32_t)); //dynamic array of size elements
    for (uint32_t i = 0; i < elements; i += 1) {
        A[i] = random() & 0x3FFFFFFF; // bit-mask elements to 30 bits
    }

    bool print_0 = false; //boolean to check if 0 is entered after -p

    if (member_set(HEAP, s)) { // if -h is inputted
        heap_sort(stats, A, elements);
        printf("Heap Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n",
            elements, stats->moves, stats->compares);
        if (print_elements == 0) { // if print_0 is true, nothing else should print
            print_0 = true;
        }
        if (print_0 != true) {
            if (print_elements > elements) { // cases in which to print all elements of A
                for (uint32_t i = 0; i < elements; i += 1) {
                    printf("%13" PRIu32, A[i]); //print each element with width of 13
                    if (i > 1
                        && (i + 1) % 5
                               == 0) { // print 5 cols, newline if next element divisible by 5
                        printf("\n");
                    }
                }
                if (elements % 5 != 0) { // new line needed when printing numbers not divisible by 5
                    printf("\n");
                }
            } else if (no_print) {
                for (uint32_t i = 0; i < 100; i += 1) {
                    printf("%13" PRIu32, A[i]); //print each element with width of 13
                    if (i > 1
                        && (i + 1) % 5
                               == 0) { // print 5 cols, newline if next element divisible by 5
                        printf("\n");
                    }
                }
                if (elements % 5 != 0) { // new line needed when printing numbers not divisible by 5
                    printf("\n");
                }
            } else {
                for (uint32_t i = 0; i < print_elements;
                     i += 1) { // any other case mean print number of elements after -p
                    printf("%13" PRIu32, A[i]);
                    if (i > 1
                        && (i + 1) % 5
                               == 0) { // print 5 cols, newline if next element divisible by 5
                        printf("\n");
                    }
                }
                if (print_elements % 5
                    != 0) { // new line needed when printing numbers not divisible by 5
                    printf("\n");
                }
            }
        }
    }
    reset(stats); // must reset stats before running another sort
    srandom(seed); // re-randomize array after each sort
    for (uint32_t i = 0; i < elements; i += 1) {
        A[i] = random() & 0x3FFFFFFF;
    }

    if (member_set(SHELL, s)) { // if -s is inputted
        shell_sort(stats, A, elements);
        printf("Shell Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n",
            elements, stats->moves, stats->compares);
        if (print_elements == 0) { // if print_0 is true, nothing else should print
            print_0 = true;
        }
        if (print_0 != true) {
            if (print_elements > elements) { // cases in which to print all elements of A
                for (uint32_t i = 0; i < elements; i += 1) {
                    printf("%13" PRIu32, A[i]); //print each element with width of 13
                    if (i > 1
                        && (i + 1) % 5
                               == 0) { // print 5 cols, newline if next element divisible by 5
                        printf("\n");
                    }
                }
                if (elements % 5 != 0) { // new line needed when printing numbers not divisible by 5
                    printf("\n");
                }
            } else if (no_print) {
                for (uint32_t i = 0; i < 100; i += 1) {
                    printf("%13" PRIu32, A[i]); //print each element with width of 13
                    if (i > 1
                        && (i + 1) % 5
                               == 0) { // print 5 cols, newline if next element divisible by 5
                        printf("\n");
                    }
                }
                if (elements % 5 != 0) { // new line needed when printing numbers not divisible by 5
                    printf("\n");
                }
            } else {
                for (uint32_t i = 0; i < print_elements;
                     i += 1) { // any other case mean print number of elements after -p
                    printf("%13" PRIu32, A[i]);
                    if (i > 1
                        && (i + 1) % 5
                               == 0) { // print 5 cols, newline if next element divisible by 5
                        printf("\n");
                    }
                }
                if (print_elements % 5
                    != 0) { // new line needed when printing numbers not divisible by 5
                    printf("\n");
                }
            }
        }
    }
    reset(stats); // must reset stats before running another sort
    srandom(seed); // re-randomize array after each sort
    for (uint32_t i = 0; i < elements; i += 1) {
        A[i] = random() & 0x3FFFFFFF;
    }

    if (member_set(INSERTION, s)) { // if -i is inputted
        insertion_sort(stats, A, elements);
        printf("Insertion Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n",
            elements, stats->moves, stats->compares);
        if (print_elements == 0) { // if print_0 is true, nothing else should print
            print_0 = true;
        }
        if (print_0 != true) {
            if (print_elements > elements) { // cases in which to print all elements of A
                for (uint32_t i = 0; i < elements; i += 1) {
                    printf("%13" PRIu32, A[i]); //print each element with width of 13
                    if (i > 1
                        && (i + 1) % 5
                               == 0) { // print 5 cols, newline if next element divisible by 5
                        printf("\n");
                    }
                }
                if (elements % 5 != 0) { // new line needed when printing numbers not divisible by 5
                    printf("\n");
                }
            } else if (no_print) {
                for (uint32_t i = 0; i < 100; i += 1) {
                    printf("%13" PRIu32, A[i]); //print each element with width of 13
                    if (i > 1
                        && (i + 1) % 5
                               == 0) { // print 5 cols, newline if next element divisible by 5
                        printf("\n");
                    }
                }
                if (elements % 5 != 0) { // new line needed when printing numbers not divisible by 5
                    printf("\n");
                }
            } else {
                for (uint32_t i = 0; i < print_elements;
                     i += 1) { // any other case mean print number of elements after -p
                    printf("%13" PRIu32, A[i]);
                    if (i > 1
                        && (i + 1) % 5
                               == 0) { // print 5 cols, newline if next element divisible by 5
                        printf("\n");
                    }
                }
                if (print_elements % 5
                    != 0) { // new line needed when printing numbers not divisible by 5
                    printf("\n");
                }
            }
        }
    }
    reset(stats); // must reset stats before running another sort
    srandom(seed); // re-randomize array after each sort
    for (uint32_t i = 0; i < elements; i += 1) {
        A[i] = random() & 0x3FFFFFFF;
    }

    if (member_set(QUICK, s)) { // if -q is inputted
        quick_sort(stats, A, elements);
        printf("Quick Sort, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n",
            elements, stats->moves, stats->compares);
        if (print_elements == 0) { // if print_0 is true, nothing else should print
            print_0 = true;
        }
        if (print_0 != true) {
            if (print_elements > elements) { // cases in which to print all elements of A
                for (uint32_t i = 0; i < elements; i += 1) {
                    printf("%13" PRIu32, A[i]); //print each element with width of 13
                    if (i > 1
                        && (i + 1) % 5
                               == 0) { // print 5 cols, newline if next element divisible by 5
                        printf("\n");
                    }
                }
                if (elements % 5 != 0) { // new line needed when printing numbers not divisible by 5
                    printf("\n");
                }
            } else if (no_print) {
                for (uint32_t i = 0; i < 100; i += 1) {
                    printf("%13" PRIu32, A[i]); //print each element with width of 13
                    if (i > 1
                        && (i + 1) % 5
                               == 0) { // print 5 cols, newline if next element divisible by 5
                        printf("\n");
                    }
                }
                if (elements % 5 != 0) { // new line needed when printing numbers not divisible by 5
                    printf("\n");
                }
            } else {
                for (uint32_t i = 0; i < print_elements;
                     i += 1) { // any other case mean print number of elements after -p
                    printf("%13" PRIu32, A[i]);
                    if (i > 1
                        && (i + 1) % 5
                               == 0) { // print 5 cols, newline if next element divisible by 5
                        printf("\n");
                    }
                }
                if (print_elements % 5
                    != 0) { // new line needed when printing numbers not divisible by 5
                    printf("\n");
                }
            }
        }
    }
    reset(stats); // must reset stats before running another sort

    if (help || no_input
        || bad_input) { // print help menu if '-h', no input to ./sorting, or invalid input
        printf("SYNOPSIS\n");
        printf("   A collection of comparison-based sorting algorithms.\n");
        printf("USAGE\n");
        printf("   ./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n");
        printf("OPTIONS\n");
        printf("   -h              display program help and usage.\n");
        printf("   -a              enable all sorts.\n");
        printf("   -e              enable Heap Sort.\n");
        printf("   -i              enable Insertion Sort.\n");
        printf("   -s              enable Shell Sort.\n");
        printf("   -q              enable Quick Sort.\n");
        printf("   -n length       specify number of array elements (default: 100).\n");
        printf("   -p elements     specify number of elements to print (default: 100).\n");
        printf("   -r seed         specify random seed (default: 13371453).\n");
    }

    free(A); // de-allocate dynamically allocated array
    return 0; // end of program
}
