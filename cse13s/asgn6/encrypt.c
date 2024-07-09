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

// Main function for RSA encryption
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
    char *pbfile = "rsa.pub";
    FILE *pubfile;

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
        case 'n': pbfile = optarg; break;
        case 'v': verbose = true; break;
        case 'h': help = true;
        default: invalid_input = true; break;
        }
    }

    // Help
    if (help || invalid_input) {
        fprintf(stderr, "SYNOPSIS\n");
        fprintf(stderr, "   Encrypts data using RSA encryption.\n");
        fprintf(stderr, "   Encrypted data is decrypted by the decrypt program..\n");
        fprintf(stderr, "\n");
        fprintf(stderr, "USAGE\n");
        fprintf(stderr, "   ./encrypt [-hv] [-i infile] [-o outfile] -n pubkey\n");
        fprintf(stderr, "OPTIONS\n");
        fprintf(stderr, "   -h             Display program help and usage.\n");
        fprintf(stderr, "   -v             Display verbose program output.\n");
        fprintf(stderr, "   -i infile      Input file of data to encrypt (default: stdin).\n");
        fprintf(stderr, "   -o outfile     Output file of data to encrypt (default: stdout).\n");
        fprintf(stderr, "   -n pbfile      Public key file (default: rsa.pub).\n");
        fclose(infile);
        fclose(outfile);
        exit(1);
    }

    // OPEN PUBLIC KEY FILE
    pubfile = fopen(pbfile, "r");
    if (pubfile == NULL) {
        fprintf(stderr, "The public key file is not valid\n");
        exit(1);
    }

    // READ PUBLIC KEY FROM FILE
    mpz_t n, e, s;
    mpz_inits(n, e, s, NULL);
    char username[_POSIX_LOGIN_NAME_MAX]; // 9
    rsa_read_pub(n, e, s, username, pubfile);

    if (verbose) {
        fprintf(stderr, "user = %s\n", username);
        gmp_fprintf(stderr, "s (%lu bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_fprintf(stderr, "n (%lu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_fprintf(stderr, "e (%lu bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
    }

    // CONVERT USERNAME TO MPZ_T AND VERIFY IT
    mpz_t user, m;
    mpz_inits(user, m, NULL);
    mpz_set_str(user, username, 62);
    rsa_verify(m, user, e, n);

    // ENCRYPT FILE
    rsa_encrypt_file(infile, outfile, n, e);

    // ADDED CLOSE OF IN/OUTFILE
    fclose(infile);
    fclose(outfile);
    fclose(pubfile);
    mpz_clears(n, e, s, user, m, NULL);
    return 0;
}
