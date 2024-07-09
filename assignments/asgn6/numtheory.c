#include "numtheory.h"
#include "randstate.h"

// Computes GCD of two numbers
// Return type void
//
// d: output
// a: 1st number
// b: second number
void gcd(mpz_t d, mpz_t a, mpz_t b) {
    mpz_t temp_a, temp_b, t;
    mpz_inits(temp_a, temp_b, t, NULL);
    mpz_set(temp_a, a);
    mpz_set(temp_b, b);
    while (mpz_cmp_ui(temp_b, 0) != 0) { // while b != 0
        mpz_set(t, temp_b);
        mpz_mod(temp_b, temp_a, temp_b); // b = a mod b
        mpz_set(temp_a, t);
    }
    mpz_set(d, temp_a); // return a
    mpz_clears(temp_a, temp_b, t, NULL);
}

// Computes inverse i of a % n
// Return type void
//
// i: inverse result
// a: number to be used
// n: modulus
void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
    mpz_t r, r_prime, t, t_prime, q, temp_r, temp_t, q_times_rp, q_times_tp;
    mpz_inits(r, r_prime, t, t_prime, q, temp_r, temp_t, q_times_rp, q_times_tp, NULL);
    mpz_set(r, n);
    mpz_set(r_prime, a);
    mpz_set_ui(t, 0);
    mpz_set_ui(t_prime, 1);

    while (mpz_cmp_ui(r_prime, 0) != 0) {
        mpz_fdiv_q(q, r, r_prime); // floor divide
        mpz_set(temp_r, r);
        mpz_set(r, r_prime);
        mpz_mul(q_times_rp, q, r_prime); // q_times_rp = q * r_prime
        mpz_sub(r_prime, temp_r,
            q_times_rp); // rp = temp_r - q_times_rp

        mpz_set(temp_t, t);
        mpz_set(t, t_prime);
        mpz_mul(q_times_tp, q, t_prime); // q_times_tp = q * t_prime
        mpz_sub(t_prime, temp_t, q_times_tp); // tp = temp_t - q_times_tp
    }

    if (mpz_cmp_ui(r, 1) > 0) { // if r > 0
        mpz_set_ui(i, 0);
        mpz_clears(r, r_prime, t, t_prime, q, temp_r, temp_t, q_times_rp, q_times_tp, NULL);
        return;
    }
    if (mpz_cmp_ui(t, 0) < 0) { // if t < 0
        mpz_add(t, t, n); // t = t + n
    }
    mpz_set(i, t); // return t
    mpz_clears(r, r_prime, t, t_prime, q, temp_r, temp_t, q_times_rp, q_times_tp, NULL);
}

// Performs modular exponentiation
// Return type void
//
// out: output
// base: the base number
// exponent: the exponent value
// modulus: the modulus value
void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    // a = base, d = exponent, n = modulus
    mpz_t v, p, temp_d;
    mpz_inits(v, p, temp_d, NULL);
    mpz_set_ui(v, 1);
    mpz_set(p, base);
    mpz_set(temp_d, exponent);
    while (mpz_cmp_ui(temp_d, 0) > 0) { // while d > 0
        if (mpz_odd_p(temp_d) != 0) {
            mpz_mul(v, v, p);
            mpz_mod(v, v, modulus); // v = v % n
        }
        mpz_mul(p, p, p);
        mpz_mod(p, p, modulus); // p = p % n
        mpz_fdiv_q_ui(temp_d, temp_d, 2); // d = d/2 (floor)
    }
    mpz_set(out, v); // return v
    mpz_clears(v, p, temp_d, NULL);
}

// Tests if a number is prime using Miller-Rabin
// Returns boolean if number is prime or not
//
// n: number to be tested
// iters: number of iterations to test with
bool is_prime(mpz_t n, uint64_t iters) {
    // CHECK EVEN NUMBERS, 0, 1
    //    n is not odd    and      n is > 2
    if ((mpz_odd_p(n) == 0) && (mpz_cmp_ui(n, 2) > 0)) {
        return false;
    }
    if (mpz_cmp_ui(n, 0) == 0 || mpz_cmp_ui(n, 1) == 0) { // n is 0, 1 -> false
        return false;
    }
    if (mpz_cmp_ui(n, 2) == 0 || mpz_cmp_ui(n, 3) == 0) { // n is 2,3 -> true
        return true;
    }

    mpz_t n_minus_1, two, r, j;
    mpz_inits(n_minus_1, two, r, j, NULL);
    mpz_sub_ui(n_minus_1, n, 1); // set n_minus_1
    mpz_set_ui(two, 2);
    mp_bitcnt_t s = 2;
    while (mpz_divisible_2exp_p(n_minus_1, s)) { // divide (n-1) by 2^s
        s++;
    }
    s--; // last s was correct
    mpz_tdiv_q_2exp(r, n_minus_1, s); // r = (n-1)/2^s

    mpz_t a, bound, y;
    mpz_inits(a, bound, y, NULL);
    for (uint64_t i = 0; i < iters; i += 1) {
        mpz_sub_ui(bound, n, 3);
        mpz_urandomm(a, state, bound);
        mpz_add_ui(a, a, 2);
        pow_mod(y, a, r, n);
        if ((mpz_cmp_ui(y, 1) != 0) && (mpz_cmp(n_minus_1, y) != 0)) {
            mpz_set_ui(j, 1);
            while (!(mpz_cmp_ui(j, (s - 1)) > 0) && (mpz_cmp(y, n_minus_1) != 0)) {
                pow_mod(y, y, two, n);
                if (mpz_cmp_ui(y, 1) == 0) { // if y == 1
                    // clear?
                    return false;
                }
                mpz_add_ui(j, j, 1); // j = j + 1
            }
            if (mpz_cmp(y, n_minus_1) != 0) { // y != n - 1
                mpz_clears(n_minus_1, two, r, j, a, bound, y, NULL);
                return false;
            }
        }
    }
    mpz_clears(n_minus_1, two, r, j, a, bound, y, NULL);
    return true;
}

// Generates a large prime number (checked by M-R)
// Return type void
//
// p: stored generated number
// bits: number of bits p has to be at least
// iters: iterations with which to generate number
void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    do {
        mpz_urandomb(p, state, bits);
    } while (!is_prime(p, iters) || (mpz_sizeinbase(p, 2)) < bits || (mpz_odd_p(p) == 0));
    //         not prime               not >= bits                     // not odd
}
