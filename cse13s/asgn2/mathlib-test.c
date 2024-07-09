#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "aebmrvnsh"

bool e_test = false;
bool euler_test = false;
bool bbp_test = false;
bool madhava_test = false;
bool viete_test = false;
bool newton_test = false;
bool stats = false;
bool help = false;
bool no_input = true;

// Checks which command line options are typed and sets bools to true for printing results
// No returns
// argc: argument counter
// argv: array of strings
int main(int argc, char **argv) {
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        no_input = false;
        switch (opt) {
        case 'a': // set everything to true, run all tests
            e_test = true;
            bbp_test = true;
            madhava_test = true;
            euler_test = true;
            viete_test = true;
            newton_test = true;
            break;
        case 'e': e_test = true; break;
        case 'b': bbp_test = true; break;
        case 'm': madhava_test = true; break;
        case 'r': euler_test = true; break;
        case 'v': viete_test = true; break;
        case 'n': newton_test = true; break;
        case 's': stats = true; break; // prints all stats for com. line options presented
        case 'h': help = true; break;
        default: break;
        }
    }

    // each bool that is set to true triggers printing of results

    if (e_test) {
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(e() - M_E));
        if (stats) {
            printf("e() terms = %d\n", e_terms());
        }
    }
    if (euler_test) {
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI,
            absolute(pi_euler() - M_PI));
        if (stats) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }
    if (madhava_test) {
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI,
            absolute(pi_madhava() - M_PI));
        if (stats) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }
    if (bbp_test) {
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI,
            absolute(pi_bbp() - M_PI));
        if (stats) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    }
    if (viete_test) {
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI,
            absolute(pi_viete() - M_PI));
        if (stats) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
    }
    if (newton_test) {
        for (double x = 0.0; x < 10.0; x += 0.1) {
            printf("sqrt_newton(%lf) = %16.15lf, sqrt(%lf) = %16.15lf, diff = %16.15lf\n", x,
                sqrt_newton(x), x, sqrt(x), absolute(sqrt_newton(x) - sqrt(x)));
            if (stats) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }

    if (help || no_input) {
        printf("SYNOPSIS\n");
        printf("   A test harness for the small numerical library.\n");
        printf("USAGE\n");
        printf("   ./mathlib-test [-aebmrvnsh]\n");
        printf("OPTIONS\n");
        printf("   -a   Runs all tests.\n");
        printf("   -e   Runs e test.\n");
        printf("   -b   Runs BBP pi test.\n");
        printf("   -m   Runs Madhava pi test.\n");
        printf("   -r   Runs Euler pi test.\n");
        printf("   -v   Runs Viete pi test.\n");
        printf("   -n   Runs Newton square root tests.\n");
        printf("   -s   Print verbose statistics.\n");
        printf("   -h   Display program synopsis and usage.\n");
    }
    return 0;
}
