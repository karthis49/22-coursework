#include "rsa.h"
#include <math.h>
#include "randstate.h"
#include "numtheory.h"
#include <stdlib.h>

// Makes parts of RSA public key
// Return type void
//
// p: 1st prime
// q: 2nd prime
// n: public modulus
// e: public exponent
// nbits: bit size of n
// iters: number of iters to generate prime with
void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    mpz_t p_minus_1, q_minus_1, totient, gcd_en;
    mpz_inits(p_minus_1, q_minus_1, totient, gcd_en, NULL);
    uint64_t p_bits = (random() % (nbits / 2)) + (nbits / 4) + 1; // +1 for extra bit
    uint64_t q_bits = nbits - p_bits + 1; // + 1
    make_prime(p, p_bits, iters);
    make_prime(q, q_bits, iters);
    mpz_mul(n, p, q); // n = p*q
    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);
    mpz_mul(totient, p_minus_1, q_minus_1);
    do {
        mpz_urandomb(e, state, nbits);
        gcd(gcd_en, e, totient);
    } while (mpz_cmp_ui(gcd_en, 1) != 0); // while gcd(e, n) != 1
    mpz_clears(p_minus_1, q_minus_1, totient, gcd_en, NULL);
}

// Writes public key to output file
// Return type void
//
// n: public modulus
// e: public exponent
// s: signature
// username: array containing the username
// pbfile: output file
void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n%Zx\n%Zx\n%s\n", n, e, s, username);
}

// Read parts of public key from input file
//
//
// n: public modulus
// e: public exponent
// s: signature
// username: array storing username
// pbfile: input file
void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n%Zx\n%Zx\n%s\n", n, e, s, username);
}

// Make RSA private key
// Return type void
//
// d: private key
// e: number to use for mod_inverse
// p: prime number
// q: prime number
void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t p_minus_1, q_minus_1, totient;
    mpz_inits(p_minus_1, q_minus_1, totient, NULL);
    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);
    mpz_mul(totient, p_minus_1, q_minus_1);
    mod_inverse(d, e, totient);
    mpz_clears(p_minus_1, q_minus_1, totient, NULL);
}

// Write private key to output file
// Return type void
//
// n: public modulus
// d: private key
// pvfile: output file
void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n%Zx\n", n, d);
}

// Read parts of private key from input file
// Return type void
//
// n: public modulus
// d: private key
// pvfile: input file
void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n%Zx\n", n, d);
}

// Performs RSA encryption
// Return types void
//
// c: ciphertext
// m: message
// e: exponent
// n: modulus
void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
}

// Encrypts a file using RSA
// Return type void
//
// infile: input file
// outfile: output file
// n: modulus
// e: exponent
void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    mpz_t c, m; // ciphertext and message params passed to encrypt
    mpz_inits(c, m, NULL);

    // BLOCK SIZE WITH INT
    size_t k = ((mpz_sizeinbase(n, 2)) - 1) / 8;

    uint8_t *block = (uint8_t *) calloc(k, sizeof(uint8_t));
    block[0] = 255;
    size_t j = 0;

    while (feof(infile) == 0) {
        j = fread(block + 1, sizeof(uint8_t), k - 1, infile);
        if (j > 0) {
            mpz_import(m, j + 1, 1, sizeof(uint8_t), 1, 0, block);
            rsa_encrypt(c, m, e, n);
            gmp_fprintf(outfile, "%Zx\n", c);
        }
    }

    free(block); // free array
    mpz_clears(c, m, NULL);
}

// Performs RSA decryption
// Return type void
//
// m: message
// c: ciphertext
// d: private key
// n: modulus
void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
}

// Decrypts a file using RSA
// Return type void
//
// infile: input file
// outfile: output file
// n: modulus
// d: private key
void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    mpz_t c, m; // ciphertext and message params passed to rsa_decrypt
    mpz_inits(c, m, NULL);

    // BLOCK SIZE WITH INT
    size_t k = ((mpz_sizeinbase(n, 2)) - 1) / 8;

    uint8_t *block = (uint8_t *) calloc(k, sizeof(uint8_t));
    size_t j = 0;

    while (feof(infile) == 0) { // not at end of file
        int bytes_scanned = gmp_fscanf(infile, "%Zx\n", c);
        if (bytes_scanned > 0) {
            rsa_decrypt(m, c, d, n);
            mpz_export(block, &j, 1, sizeof(uint8_t), 1, 0, m);
            fwrite(block + 1, sizeof(uint8_t), j - 1, outfile);
        }
    }

    free(block);
    mpz_clears(c, m, NULL);
}

// Performs RSA signing
// Return type void
//
// s: signature
// m: message
// d: private key
// n: modulus
void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
}

// Perform RSA verification
// Returns bool if verified or not
//
// m: message
// s: signature
// e: exponent
// n: modulus
bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_init(t);
    pow_mod(t, s, e, n);
    if (mpz_cmp(t, m) == 0) {
        mpz_clear(t);
        return true;
    }
    mpz_clear(t);
    return false;
}
