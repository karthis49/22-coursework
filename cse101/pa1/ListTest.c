/****************************************************************************************
*  TEMPORARY!!!!!
*  ListTest.c
*  Test client for List ADT
*  *****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   
 //  List A = newList();
 //  List B = newList();
 //  List C = NULL;
 //  int i;

 //  for(i=1; i<=20; i++){
 //     append(A,i);
 //     prepend(B,i);
 //  }

 //  printList(stdout,A); 
 //  printf("\n");
 //  printList(stdout,B); 
 //  printf("\n");

 //  for(moveFront(A); index(A)>=0; moveNext(A)){
 //     printf("%d ", get(A));
 //  }
 //  printf("\n");
 //  for(moveBack(B); index(B)>=0; movePrev(B)){
 //     printf("%d ", get(B));
 //  }
 //  printf("\n");

 //  C = copyList(A);
 //  printf("%s\n", equals(A,B)?"true":"false");
 //  printf("%s\n", equals(B,C)?"true":"false");
 //  printf("%s\n", equals(C,A)?"true":"false");


 //  moveFront(A);
 //  for(i=0; i<5; i++) moveNext(A); // at index 5
 //  insertBefore(A, -1);            // at index 6
 //  for(i=0; i<9; i++) moveNext(A); // at index 15
 //  insertAfter(A, -2);
 //  for(i=0; i<5; i++) movePrev(A); // at index 10
 //  delete(A);
 //  printList(stdout,A);
 //  printf("\n");
 //  printf("%d\n", length(A));
 //  clear(A);
 //  printf("%d\n", length(A));

   //freeList(&A);
   //freeList(&B);
   //freeList(&C);

//   List D = newList();
//   append(D, 1);
//   append(D, 2);
//   append(D, 3);
//   append(D, 5);
//   printf("length: %d\n", length(D));
//   moveFront(D);
//   printf("front: %d\n", get(D)); // 1
//   moveBack(D);
//   printf("back: %d\n", get(D)); // 5
//   movePrev(D);
//   printf("prev of back: %d\n", get(D));  // 3
//   movePrev(D);
//   moveNext(D);
//   printf("next: %d\n", get(D));  // 3
//   prepend(D, 4);
//   printList(stdout, D);
//   printf("length: %d\n", length(D));
//   printf("\n");
//   moveFront(D);
//   printf("front: %d\n", get(D)); 
//   insertBefore(D, 7);
//   printList(stdout, D);  // SOMETHING WRONG
//   printf("\n");
//   moveBack(D);
//   insertBefore(D, 3);
//   printList(stdout, D);
//   printf("\n");
//   moveFront(D);
//   moveNext(D);
//   moveNext(D);
//   insertAfter(D, 9); 
//   printList(stdout, D);
//   printf("\n");
//   moveBack(D);
//   insertAfter(D, 0); // check!
//   printf("index: %d\n", index(D));
//   printList(stdout, D);
//   printf("\n");
//   deleteFront(D);
//   printf("index: %d\n", index(D));
//   deleteBack(D);
//   printList(stdout, D);
//   printf("\n");
//   printf("length: %d\n", length(D));
//   moveFront(D);
//   printf("index: %d\n", index(D));
//   printf("front (val): %d\n", get(D));
//   printf("length: %d\n", length(D));
//   //printf("%d", get(A));
   //printf("%d ", index(A));   
   //delete(D); 
//   printList(stdout, D);
  // printf("\n");
   //freeList(&D);
    
   List A = newList();
   prepend(A, 5);
   printf("1\n");
    append(A, 7);
   printf("2\n");
    prepend(A, 2);
   printf("3\n");
    moveFront(A);
    insertAfter(A, 12);
    return 0;
   printf("index: %d\n", index(A));
  printf("4\n");
    insertBefore(A, 43);
printf("index before DF: %d\n", index(A));
  printList(stdout, A);
   printf("\n");
  printf("5\n");
    deleteFront(A);
   printList(stdout, A);
printf("index after DF: %d\n", index(A));
   printf("\n");
  printf("6\n");
    printList(stdout, A);
    printf("\n");
  printf("7\n");
    delete(A);
  printf("8\n");
   printf("front (val): %d\n", get(A));
     
    
    //if (front(A) != 5)
    //  return 1;
    //return 0;   
   return 0;
}

/*
 * Output of this program:
 * 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
 * 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
 * 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
 * 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
 * false
 * false
 * true
 * 1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
 * 21
 * 0
 * */
