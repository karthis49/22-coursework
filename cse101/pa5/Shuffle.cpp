/********************************************************************************* 
 * * Karthi Sankar, kasankar 
 * * 2022 Spring CSE101 PA5
 * * Shuffle.cpp 
 * * Main file using List ADT
 * *********************************************************************************/

#include<iostream>
#include <string> 
#include<fstream>
#include<string>
#include"List.h"

using namespace std;

void shuffle(List& D) {
    int mid = D.length() / 2;
    List left;
    List right;
    ListElement val;
    int len_D = D.length();  // save val of length before clearing
    D.moveFront();
    // fill "left" and "right lists"
    while (D.position() < D.length()) {
        if (D.position() < mid) {
            val = D.peekNext();
            left.insertBefore(val);
            D.moveNext();
        }
        if (D.position() == mid || D.position() > mid) {
            val = D.peekNext();  
            right.insertBefore(val);
            D.moveNext();
        }
    }
    D.clear();  // changing list D
    left.moveFront();
    right.moveFront();
    for (int x = 0; x < len_D; x++) {
        if (x % 2 == 0) {  // index is even, insert from right list
            int r_val = right.peekNext();
            D.insertBefore(r_val);
            right.moveNext(); 
        }
        if (x % 2 == 1) {  // index is odd, insert from left list
            int l_val = left.peekNext();
            D.insertBefore(l_val);
            left.moveNext(); 
        }   
    }
    // resulting List D should be shuffled
}

int main(int argc, char * argv[]){

    // check command line for correct number of arguments
    if( argc != 2 ) {
       cerr << "Usage: " << argv[0] << " <deck size> " << endl;
       return(EXIT_FAILURE);
    }

    // convert CLO into int variable
    int max_deckSize = stoi(argv[1], nullptr, 10);
    List shuffled;  // list to be shuffled
    List standard;  // "original state" of the list

    int deckSize;
    int shuffle_count = 1;

    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;

    for (deckSize = 1; deckSize <= max_deckSize; deckSize++) {
        shuffled.insertBefore(deckSize - 1);
        standard.insertBefore(deckSize - 1);

        // shuffle once to start
        shuffle(shuffled);
        while (!standard.equals(shuffled)) {  // shuffle until list is "back to normal"
            shuffle(shuffled);
            shuffle_count += 1;
        }
        
        cout << deckSize << "	         " << shuffle_count << endl;

        // reset shuffle count back to 1
        shuffle_count = 1;
    }

    return 0;
}
