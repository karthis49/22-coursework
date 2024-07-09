/********************************************************************************* 
 * * Karthi Sankar, kasankar 
 * * 2022 Spring CSE101 PA2
 * * GraphTest.c 
 * * Test client for Graph ADT 
 * *********************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){

   // Build graph A 
    Graph A = newGraph(70);
    addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);
    BFS(A, 42);
    printGraph(stdout, A);
    if (getParent(A, 42) != NIL)
      printf("1\n");
    if (getParent(A, 2) != 42)
      printf("2\n");
    if (getParent(A, 8) != NIL)
      printf("3\n");   
    freeGraph(&A);

   Graph C = newGraph(100);
   addEdge(C, 89, 1);
   addEdge(C, 39, 1); 
   addEdge(C, 99, 1); 
   addEdge(C, 95, 2); 
   addEdge(C, 9, 7);
   addEdge(C, 90, 9); 
   addEdge(C, 88, 4); 
   addArc(C, 50, 3);
   addArc(C, 30, 1); 
   BFS(C, 99);
   getDist(C, 50);
   getParent(C, 88);
   getSource(C);
   List K = newList();
   getPath(K, C, 50);
   printList(stdout, K);
   printf("\n");
   printGraph(stdout, C);
   makeNull(C);
   freeList(&K);
   freeGraph(&C);

  
   return(0);
}
