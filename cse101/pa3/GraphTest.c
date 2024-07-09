/********************************************************************************* 
 *  * * Karthi Sankar, kasankar 
 *  * * 2022 Spring CSE101 PA3
 *  * * GraphTest.c 
 *  * * Test client for Graph ADT 
 *  * *********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]) {
   // 2 separate tests of all the functions in Graph.c
   // TEST 1
   int i;
   Graph one = newGraph(6);
   List oneL = newList();
   addEdge(one, 1, 2);
   addEdge(one, 1, 3);
   addEdge(one, 2, 4);
   addEdge(one, 2, 5);
   addEdge(one, 2, 6);
   addEdge(one, 3, 4);
   addEdge(one, 4, 5);
   addEdge(one, 5, 6);
   printGraph(stdout, one);
   fprintf(stdout, "\n"); 
   fprintf(stdout, "order: %d, size: %d\n", getOrder(one), getSize(one));
   fprintf(stdout, "\n");
   for(i=1; i<=6; i++) append(oneL, i);
   fprintf(stdout, "List for DFS:\n");
   printList(stdout, oneL);
   fprintf(stdout, "\n");
   fprintf(stdout, "\n"); 
   Graph oneT = transpose(one);
   Graph oneC = copyGraph(one);
   fprintf(stdout, "Transpose of Graph:\n");
   printGraph(stdout, oneT);
   fprintf(stdout, "\n");
   fprintf(stdout, "Copy of Graph:\n");
   printGraph(stdout, oneC);
   fprintf(stdout, "\n");
   DFS(one, oneL);
   fprintf(stdout, "First Run of DFS\n");
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=6; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(one, i), getFinish(one, i), getParent(one, i));
   }
   fprintf(stdout, "\n");
   DFS(oneT, oneL);
   fprintf(stdout, "Second Run of DFS\n");
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=6; i++){
       fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(oneT, i), getFinish(oneT, i), getParent(oneT, i));
   }
   fprintf(stdout, "\n");

   freeList(&oneL);
   freeGraph(&one);
   freeGraph(&oneT);
   freeGraph(&oneC);

   // TEST 2
   Graph two = newGraph(8);
   List twoL = newList();
   addArc(two, 1, 2);
   addArc(two, 2, 3);
   addArc(two, 3, 4);
   addArc(two, 4, 3);
   addArc(two, 5, 1);
   addArc(two, 2, 5);
   addArc(two, 5, 6);
   addArc(two, 2, 6);
   addArc(two, 6, 7);
   addArc(two, 7, 6);
   addArc(two, 3, 7);
   addArc(two, 7, 8);
   addArc(two, 8, 8);
   printGraph(stdout, two);
   fprintf(stdout, "\n");
   fprintf(stdout, "order: %d, size: %d\n", getOrder(two), getSize(two));
   fprintf(stdout, "\n");
   for(i=1; i<=8; i++) append(twoL, i);
   fprintf(stdout, "List before DFS:\n");
   printList(stdout, twoL);
   fprintf(stdout, "\n");
   fprintf(stdout, "\n");
   Graph twoT = transpose(two);
   Graph twoC = copyGraph(two);
   fprintf(stdout, "Transpose of Graph:\n");
   printGraph(stdout, twoT);
   fprintf(stdout, "\n");
   fprintf(stdout, "Copy of Graph:\n");
   printGraph(stdout, twoC);
   fprintf(stdout, "\n");
   fprintf(stdout, "First Run of DFS\n");
   fprintf(stdout, "\n");
   DFS(two, twoL);
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=8; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(two, i), getFinish(two, i), getParent(two, i));
   }
   fprintf(stdout, "\n");
   fprintf(stdout, "List after 1st DFS:\n");
   printList(stdout, twoL);
   fprintf(stdout, "\n");
   fprintf(stdout, "\n");
   DFS(twoT, twoL);
   fprintf(stdout, "Second Run of DFS\n");
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=8; i++){
       fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(twoT, i), getFinish(twoT, i), getParent(twoT, i));
   } 
   fprintf(stdout, "\n");
   fprintf(stdout, "List after 2nd DFS:\n");
   printList(stdout, twoL);
   fprintf(stdout, "\n");
   fprintf(stdout, "\n");
    
   freeList(&twoL);
   freeGraph(&two);
   freeGraph(&twoC);
   freeGraph(&twoT);

   return(0);
}
