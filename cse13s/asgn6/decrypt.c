#include "numtheory.h"
#include "rsa.h"
#include "randstate.h"
#include "stdio.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <limits.h>

#define OPTIONS "i:o:n:vh"

// Main function for RSA decryption
// Return type int: 0
//
// argc: argument counter
// argv: array of strings
int main(int argc, char **argv) {
    bool help = false;
    bool invalid_input = false;
    bool verbose = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    char *pvfile = "rsa.priv";
    FILE *privfile;

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            infile = fopen(optarg, "r"); // read mode
            if (infile == NULL) {
                perror("Error with use of input file");
                exit(1);
            }
            break;
        case 'o':
            outfile = fopen(optarg, "w"); // write mode
            if (outfile == NULL) {
                perror("Error with use of output file");
                exit(1);
            }
            break;
        case 'n': pvfile = optarg; break;
        case 'v': verbose = true; break;
        case 'h': help = true;
        default: invalid_input = true; break;
        }
    }

    if (help || invalid_input) {
        fprintf(stderr, "SYNOPSIS\n");
        fprintf(stderr, "   Decrypts data using RSA decryption.\n");
        fprintf(stderr, "   Encrypted data is encrypted by the encrypt program.\n");
        fprintf(stderr, "\n");
        fprintf(stderr, "USAGE\n");
        fprintf(stderr, "   ./decrypt [-hv] [-i infile] [-o outfile] -n privkey\n");
        fprintf(stderr, "\n");
        fprintf(stderr, "OPTIONS\n");
        fprintf(stderr, "   -h             Display program help and usage.\n");
        fprintf(stderr, "   -v             Display verbose program output.\n");
        fprintf(stderr, "   -i infile      Input file of data to decrypt (default: stdin).\n");
        fprintf(stderr, "   -o outfile     Output file of data to decrypt (default: stdout).\n");
        fprintf(stderr, "   -n pbfile      Private key file (default: rsa.priv).\n");
        fclose(infile);
        fclose(outfile);
        exit(1);
    }

    // OPEN PRIVATE KEY FILE
    privfile = fopen(pvfile, "r");
    if (privfile == NULL) { // direct check of privfile
        fprintf(stderr, "The private key file is not valid\n");
        exit(1);
    }

    // READ PRIVATE KEY FROM FILE
    mpz_t n, d;
    mpz_inits(n, d, NULL);
    rsa_read_priv(n, d, privfile);

    if (verbose) {
        gmp_fprintf(stderr, "n (%lu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_fprintf(stderr, "d (%lu bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }

    // DECRYPT FILE
    rsa_decrypt_file(infile, outfile, n, d);

    fclose(infile);
    fclose(outfile);
    fclose(privfile);
    mpz_clears(n, d, NULL);
    return 0;
}
