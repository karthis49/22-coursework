#include "names.h"

#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };

int main(void) {

    int num_players = 0; //input for number of players
    printf("How many players? ");
    scanf("%d", &num_players);
    if ((num_players < 2) || (num_players > 10)) {
        fprintf(stderr, "Invalid number of players. Using 2 instead.\n");
        num_players = 2;
    }

    int SEED = 0; //input for random seed
    printf("Random seed: ");
    scanf("%d", &SEED);
    // if ((SEED < 0) || (SEED > UINT_MAX)){  //NOT IMPLEMENTED
    //     fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
    //     SEED = 2021;
    // }
    srandom(SEED);

    int points[10]; //init points array and set all to 0
    for (int i = 0; i < 10; i = i + 1) {
        points[i] = 0;
    }

    //rolling and going through players
    int player = 0;
    while (1) { //while true
        printf("%s rolls the pig... ", names[player]);

        while (pig[random() % 7] != SIDE) { //going through each possible (non-SIDE roll)
            if (pig[random() % 7] == RAZORBACK) {
                printf("pig lands on back ");
                points[player] += 10;
            }
            if (pig[random() % 7] == TROTTER) {
                printf("pig lands upright ");
                points[player] += 10;
            }
            if (pig[random() % 7] == SNOUTER) {
                printf("pig lands on snout ");
                points[player] += 15;
            }

            if (pig[random() % 7] == JOWLER) {
                printf("pig lands on ear ");
                points[player] += 5;
            }
        }

        if (player < num_players) { //reset player when side is rolled
            printf("pig lands on side\n");
            if ((points[player] == 100) || (points[player] > 100)) {
                break;
            }
            player += 1;
        } else {
            printf("pig lands on side\n");
            if ((points[player] == 100) || (points[player] > 100)) {
                break;
            }
            player = 0;
        }
    }
    printf("%s wins with %d points\n", names[player], points[player]); //winning message
    return 0;
}
