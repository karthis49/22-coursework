/********************************************************************************* 
 *  * * Karthi Sankar, kasankar 
 *  * * 2022 Spring CSE101 PA4
 *  * * Matrix.c 
 *  * * Matrix ADT 
 *  * *********************************************************************************/


#include<stdio.h>
#include<stdlib.h> 
#include<assert.h>
#include<stdbool.h>
#include "List.h"
#include "Matrix.h"

// private Entry type
typedef struct EntryObj* Entry;

// private NodeObj type
typedef struct EntryObj{
    double col;
    double val;
} EntryObj;

// private ListObj type
typedef struct MatrixObj{
    List* adj;
    int size;
    int NNZ;
} MatrixObj;

// Constructors-Destructors ---------------------------------------------------

// newEntry()
// Returns reference to new Node object. Initializes next and data fields.
Entry newEntry(double col, double val){
    Entry E = malloc(sizeof(EntryObj));
    assert( E!=NULL );
    E->col = col;
    E->val = val;
    return(E);
}

// freeEntry()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeEntry(Entry* pN){
   if( pN!=NULL && *pN!=NULL ){
       free(*pN);
       *pN = NULL;
   }
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
    Matrix M;
    M = malloc(sizeof(MatrixObj));
    assert(M!=NULL);
    M->adj = (List*)malloc((n+1)*sizeof(List));
    for (int i = 1; i < (n+1); i++) {
        M->adj[i] = newList();
    }
    M->size = n;
    M->NNZ = 0;
    return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL)  {
        for (int i = 1; i < size(*pM)+ 1; i++) {  
           freeList(&(*pM)->adj[i]);
        }
        free((*pM)->adj);  
        free(*pM);
        *pM = NULL;
    }
}

// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M) {
    return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
    return M->NNZ;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
    if (A->size != B->size) {
        return false;
    }
    if (A->NNZ != B->NNZ) {
        return false;
    }
    return true;
}


// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
    for (int i = 1; i < (M->size+1); i++) {
        clear(M->adj[i]);
    }
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
    double countI = 1.0;
    int countJ = 1;
    if (i > 0 && j > 0) {
        for (int y = 1; i < M->size + 1; i++) {
            if (countI == i) {
                for(moveFront(M->adj[y]); index(M->adj[y])>=0; moveNext(M->adj[y])){
                    if (countJ == j) {
                        insertBefore(M->adj[y], &x);
                        M->NNZ += 1;
                    }
                    countJ++;
                }
            
            }
            countI++; 
        }
    }
}

// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
    Matrix N = newMatrix(A->size);
    N->NNZ = A->NNZ;
    return N;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
    Matrix N = newMatrix(A->size);
    N->NNZ = A->NNZ;
    return N;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
    Matrix N = newMatrix(A->size);
    N->NNZ = (int) x;
    return N;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
    if (size(A)!=size(B)) {
        exit(1);   
    }
    Matrix N = newMatrix(A->size);
    N->NNZ = B->NNZ;
    return N;
}


// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
    if (size(A)!=size(B)) {
        exit(1);
    }
    Matrix N = newMatrix(A->size);
    N->NNZ = B->NNZ;
    return N;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
    if (size(A)!=size(B)) {
        exit(1);
    }
    Matrix N = newMatrix(A->size);
    N->NNZ = B->NNZ;
    return N;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
    for (int y = 1; y < M->size + 1; y++) {
        if (length(M->adj[y]) != 0) {
            fprintf(out, "%d: ", y);
            for(moveFront(M->adj[y]); index(M->adj[y])>=0; moveNext(M->adj[y])){
                fprintf(out, "(%d, %d)", M->size, M->NNZ);
            }
        }
    }
}
