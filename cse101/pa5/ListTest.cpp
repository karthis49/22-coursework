/********************************************************************************* 
 * * Karthi Sankar, kasankar 
 * * 2022 Spring CSE101 PA5
 * * ListTest.cpp 
 * * Test file for List ADT 
 * *********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main() {
    
    List A, B;
    int i;

    for(i=1; i<=15; i++){
      A.insertAfter(i);
      B.insertAfter(16-i);
    }

    // general tests of inserts, moves, position, equals

    cout << endl;
    cout << "A = " << A << endl;
    cout << "A.position() = " << A.position() << endl;
    cout << "B = " << B << endl;
    cout << "B.position() = " << B.position() << endl;
    cout << endl;

    A.moveBack();
    B.moveFront();
    cout << "A = " << A << endl;
    cout << "A.position() = " << A.position() << endl;
    cout << "B = " << B << endl;
    cout << "B.position() = " << B.position() << endl;

    cout << endl << "B: ";
    for(i=1; i<=7; i++){
       cout << B.moveNext() << " ";
    }
    cout << endl << "B.position() = " << B.position() << endl;

    cout << endl << "A: ";
    for(i=1; i<=7; i++){
       cout << A.movePrev() << " ";
    }
    cout << endl << "A.position() = " << A.position() << endl;

    cout << endl;
    cout << "A==B is " << (A==B?"true":"false") << endl;
    cout << endl;

    List C = A;
    cout << "A==C is " << (A==C?"true":"false") << endl;
    cout << endl;

    // test of length, front, back, sets
    cout << "A.length() = " << A.length() << endl;
    cout << "B.length() = " << B.length() << endl;
    cout << "C.length() = " << C.length() << endl;
    C.clear();
    cout << "C.length() after clearing = " << C.length() << endl;

    // adding values to C
    C.insertBefore(5);
    C.insertBefore(5);
    C.insertBefore(5);
    C.insertBefore(5);
    C.insertBefore(5);
    
    cout << "A.front() = " << A.front() << endl;
    cout << "B.front() = " << B.front() << endl;
    cout << "C.front() = " << C.front() << endl;

    cout << "A.back() = " << A.back() << endl;
    cout << "B.back() = " << B.back() << endl;
    cout << "C.back() = " << A.back() << endl;
    cout << endl;

    A.moveFront();
    A.moveNext();
    A.moveNext();
    A.setAfter(4);
    A.moveNext();
    A.setAfter(2);
    A.setBefore(2);
    B.movePrev();
    B.setAfter(100);
    B.setBefore(200);
    B.movePrev();
    B.movePrev();
    B.setBefore(5000);

    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "C = " << B << endl;
    cout << endl;

    // test of erases and peeks
    List N;
    List M;

    for(i=59; i>=42; i--){
      N.insertAfter(i);
      M.insertBefore(i);
    }

    cout << "N = " << N << endl;
    cout << "M = " << M << endl;
    cout << endl;

    N.moveFront();
    for(i=1; i<=11; i++){
      N.moveNext();
    }
    N.eraseBefore();
    N.eraseBefore();
    N.eraseBefore();
    N.eraseAfter();
    
    M.moveBack();
    for(i=1; i<=9; i++){
      M.movePrev();
    }
    M.eraseBefore();
    M.eraseAfter();
    M.eraseAfter();
    M.eraseAfter();
    M.eraseAfter();
    M.eraseAfter();

    cout << "N = " << N << endl;
    cout << "M = " << M << endl;
    cout << endl;

    N.moveFront();
    for(i=1; i<=7; i++){
      cout << "N: peekNext: " << N.peekNext() << endl;
      cout << N.moveNext() << endl; 
    }

    cout << endl;

    M.moveBack();
    for(i=1; i<=4; i++){
      cout << "M: peekPrev: " << M.peekPrev() << endl;
      cout << M.movePrev() << endl; 
    }

    cout << endl;

    // findPrev()/findNext() tests
    List P;

    for(i=4; i<=10; i++){
      P.insertBefore(i);
    }

    P.moveFront();
    P.insertBefore(4);
    P.moveNext();
    P.moveNext();
    P.moveNext();
    P.moveNext();

    cout << "P = " << P << endl;
    cout << P.findPrev(4) << endl;
    cout << B.findPrev(18) << endl;
    cout << endl;

    List Q = P;
    Q.moveFront();
    cout << "Q = " << Q << endl;
    cout << Q.findNext(7) << endl;
    cout << Q.findNext(20) << endl;
    cout << endl;

    // concat() tests

    List Y;
    List Z;
 
    Y.insertAfter(1);
    Y.insertAfter(2);
    Y.insertAfter(3);
    cout << "Y = " << Y << endl;
    cout << "Y.length() = " << Y.length() << endl;
    cout <<  endl;

    Z.insertAfter(4);
    Z.insertAfter(5);
    Z.insertAfter(6);
    cout << "Z = " << Z << endl;
    cout << "Z.length() = " << Z.length() << endl;
    cout <<  endl;

    cout << "Y==Z is " << (Y==Z?"true":"false") << endl;
    cout << endl;

    List X = Z.concat(Y);
    cout << "X = " << X << endl;
    cout << "X.length() = " << X.length() << endl;
    cout <<  endl;

    List T = Z.concat(Z);
    cout << "T = " << X << endl;
    cout << "T.length() = " << T.length() << endl;
    cout <<  endl;


    // cleanup() tests
    
    List clean;
    clean.insertBefore(3);
    clean.insertBefore(1);
    clean.insertBefore(1);
    clean.insertBefore(3);
    clean.insertBefore(2);
    clean.insertBefore(1);
    clean.insertBefore(1);
    clean.insertBefore(3);
    clean.insertBefore(2);
    clean.insertBefore(1);
    clean.insertBefore(2);
    clean.insertBefore(3);
    clean.insertBefore(3);
    clean.insertBefore(1);
    clean.insertBefore(2);
    clean.insertBefore(1);
    clean.moveFront();
    clean.moveNext();
    clean.moveNext();
    clean.moveNext();
    clean.moveNext();
    cout << "clean = " << clean << endl;
    cout << "clean.position() = " << clean.position() << endl;
    clean.cleanup();
    cout << "clean = " << clean << endl;
    cout << "clean.position() = " << clean.position() << endl;
    cout << endl;

    // another test
    clean.clear();
    clean.insertBefore(6);
    clean.insertBefore(8);
    clean.insertBefore(9);
    clean.insertBefore(10);
    clean.insertBefore(4);
    clean.insertBefore(4);
    clean.insertBefore(4);
    clean.insertBefore(1);
    clean.insertBefore(7);
    clean.insertBefore(2);
    clean.insertBefore(1);
    clean.insertBefore(8);
    clean.insertBefore(9);
    clean.insertBefore(10);
    clean.insertBefore(14);
    clean.insertBefore(3);
    clean.insertBefore(2);
    clean.insertBefore(7);
    clean.insertBefore(0);
    clean.insertBefore(0);
    clean.insertBefore(3);
    clean.insertBefore(0);
    clean.insertBefore(1);
    clean.moveBack();
    clean.movePrev();
    clean.movePrev();
    clean.movePrev();
    cout << "clean = " << clean << endl;
    cout << "clean.position() = " << clean.position() << endl;
    clean.cleanup();
    cout << "clean = " << clean << endl;
    cout << "clean.position() = " << clean.position() << endl;
    cout << endl;

    // TESTING EXCEPTIONS
    cout << "test exceptions: " << endl;
    cout << "A = " << A << endl;
    A.moveFront();
    try{
        A.peekPrev();
    }catch( std::range_error& e ){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.movePrev();
     }catch( std::range_error& e ){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
     }
     try{
        A.setBefore(5);
     }catch( std::range_error& e ){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
     }
     try{
        A.eraseBefore();
     }catch( std::range_error& e ){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    A.moveBack();
    try{
       A.peekNext();
    }catch( std::range_error& e ){
       cout << e.what() << endl;
       cout << "   continuing without interruption" << endl;
    }

    return(0);
}
