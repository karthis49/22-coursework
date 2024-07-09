/********************************************************************************* 
 *  * * Karthi Sankar, kasankar 
 *  * * 2022 Spring CSE101 PA4
 *  * * MatrixTest.c 
 *  * * Test for Matrix ADT 
 *  * *********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"
#include"Matrix.h"

int main(int argc, char* argv[]){

    int n=100000;
    Matrix A = newMatrix(n);

    printf("%d\n", NNZ(A));
    printf("%d\n", size(A));
    printMatrix(stdout, A);
    printf("\n");
    
    Matrix C, D, E, F, G, H;
 
    H = scalarMult(1.5, A);
    D = sum(A, A);
    F = diff(A, A);
    E = transpose(A);
    G = product(A, A);
    C = copy(A);

    makeZero(A);
    freeMatrix(&A);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    return 0;
}
