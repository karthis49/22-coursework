/********************************************************************************* 
 *  * * Karthi Sankar, kasankar 
 *  * * 2022 Spring CSE101 PA4
 *  * * ListTest.c 
 *  * * Test for List ADT 
 *  * *********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
    List A = newList();
    List B = newList();

    int X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int i;
    for(i=1; i<=20; i++){
      append(A, &X[i]);
      prepend(B, &X[i]);
    }

    for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
    }
    printf("\n");
   
    for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", *(int*)get(B));
    }
    printf("\n");

    bool equal = (length(A)==length(B));
    moveFront(A);
    moveFront(B);
    while( index(A)>=0 && equal){
       equal = ( get(A)==get(B) );
       moveNext(A);
       moveNext(B);
    }
    
    int a = 1, b = 2, c = 3, d = 4, e = 5;

    moveFront(A);
    set(A, &a);
    prepend(A, &b);
    append(A, &c);
    moveNext(A);
    moveNext(A);
    insertBefore(A, &d);
    insertAfter(A, &e);
    deleteFront(A);
    deleteBack(A);
    moveBack(A);
    delete(A);

    printf("%d ", *(int*)front(B));
    printf("%d ", *(int*)back(B));
    printf("\n");

    for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
    }
    printf("\n");

    clear(A);
    clear(B);

    freeList(&A);
    freeList(&B);

    return 0;
}
