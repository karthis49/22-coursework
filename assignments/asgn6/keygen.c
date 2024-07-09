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

#define OPTIONS "b:i:n:d:s:vh"

// Main function for key generation
// Return type int: 0
//
// argc: argument counter
// argv: array of strings
int main(int argc, char **argv) {
    bool help = false;
    bool invalid_input = false;
    bool verbose = false;
    uint64_t num_iters = 50;
    uint64_t nbits = 256;
    char *pbfile = "rsa.pub";
    char *pvfile = "rsa.priv";
    FILE *pubfile;
    FILE *privfile;
    uint64_t seed = time(NULL);
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'b':
            nbits = strtoul(optarg, NULL, 10);
            if (errno == EINVAL) {
                nbits = 256; // default nbits
            }
            break;
        case 'i':
            num_iters = strtoul(optarg, NULL, 10);
            if (errno == EINVAL) {
                num_iters = 100; //default iters
            }
            break;
        case 'n': pbfile = optarg; break;
        case 'd': pvfile = optarg; break;
        case 's':
            seed = strtoul(optarg, NULL, 10);
            if (errno == EINVAL) {
                seed = time(NULL); // default seed
            }
            break;
        case 'v': verbose = true; break;
        case 'h': help = true; break;
        default: invalid_input = true; break;
        }
    }

    if (help || invalid_input) {
        fprintf(stderr, "SYNOPSIS\n");
        fprintf(stderr, "   Generates an RSA public/private key pair.\n");
        fprintf(stderr, "\n");
        fprintf(stderr, "USAGE\n");
        fprintf(stderr, "   .keygen [hv] [-b bits] -n pbfile -d pvfile\n");
        fprintf(stderr, "OPTIONS\n");
        fprintf(stderr, "   -h             Display program help and usage.\n");
        fprintf(stderr, "   -v             Display verbose program output.\n");
        fprintf(stderr, "   -b bits        Minimum bits needed for public key n (default: 256).\n");
        fprintf(stderr,
            "   -i confidence  Miller-Rabin iterations for testing primes (default: 50).\n");
        fprintf(stderr, "   -n pbfile      Public key file (default: rsa.pub).\n");
        fprintf(stderr, "   -d pvfile      Private key file (default: rsa.priv).\n");
        fprintf(stderr, "   -s seed        Random seed for testing.\n");
        exit(1);
    }

    pubfile = fopen(pbfile, "w");
    if ((pubfile = fopen(pbfile, "w")) == NULL) {
        fprintf(stderr, "The public key file is not valid\n");
        exit(1);
    }

    privfile = fopen(pvfile, "w");
    if ((privfile = fopen(pvfile, "w")) == NULL) {
        fprintf(stderr, "The private key file is not valid\n");
        exit(1);
    }

    fchmod(fileno(privfile), 0600); // permissions 0600 => rw for user only

    randstate_init(seed);
    //CREATE MPZ_T's to pass in make_pub/priv
    mpz_t p, q, n, e, d;
    mpz_inits(p, q, n, e, d, NULL);

    // MAKE PUBLIC/PRIVATE KEYS
    rsa_make_pub(p, q, n, e, nbits, num_iters);
    // priv called after public to store vals into params
    rsa_make_priv(d, e, p, q);

    // get username
    char *username = getenv("USER");
    if (username == NULL) {
        fprintf(stderr, "The username is not valid\n");
        exit(1);
    }
    mpz_t user, s;
    mpz_inits(user, s, NULL);
    mpz_set_str(user, username, 62); // store username as mpz_t user

    // FIND SIGNATURE OF USERNAME
    rsa_sign(s, user, d, n);

    // WRITE PUB/PRIV KEY TO FILES
    rsa_write_pub(n, e, s, username, pubfile);
    rsa_write_priv(n, d, privfile);

    if (verbose) {
        fprintf(stderr, "user = %s\n", username);
        gmp_fprintf(stderr, "s (%lu bits) = %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_fprintf(stderr, "p (%lu bits) = %Zd\n", mpz_sizeinbase(p, 2), p);
        gmp_fprintf(stderr, "q (%lu bits) = %Zd\n", mpz_sizeinbase(q, 2), q);
        gmp_fprintf(stderr, "n (%lu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_fprintf(stderr, "e (%lu bits) = %Zd\n", mpz_sizeinbase(e, 2), e);
        gmp_fprintf(stderr, "d (%lu bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }

    mpz_clears(p, q, n, e, d, user, s, NULL); //clear username and s
    randstate_clear();
    fclose(pubfile);
    fclose(privfile);
    return 0;
}
