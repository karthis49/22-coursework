/********************************************************************************* 
 *  *  * * Karthi Sankar, kasankar 
 *  *  * * 2022 Spring CSE101 PA3
 *  *  * * FindComponents.c 
 *  *  * * Main file using List, Graph ADTs 
 *  *  * *********************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char * argv[]){

    FILE *in, *out;

     //check command line for correct number of arguments
     if( argc != 3 ){
         fprintf(stderr, "Usage error: An incorrect number of arguments were given.\n");
         exit(1);
     }
     
     //open files for reading and writing 
     in = fopen(argv[1], "r");
     if( in==NULL ){
         printf("Unable to open file %s for reading\n", argv[1]);
         exit(1);
     }

    out = fopen(argv[2], "w");
    if( out==NULL ){ 
         printf("Unable to open file %s for writing\n", argv[2]);
         exit(1);
    }  


    int num_vertices; 
    int vertex = -1;
    int neighbor = -1;
    fscanf(in,"%d", &num_vertices);       // scan in first line for ORDER of graph
    Graph G = newGraph(num_vertices);  
    while (vertex != 0 && neighbor != 0) {     // when this ends, print graph 
      fscanf(in,"%d %d", &vertex, &neighbor);
      if (vertex != 0 && neighbor != 0) {      // don't add 0 0 as an edge
          addArc(G, vertex, neighbor);        // add all edges
      }
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);  
    fprintf(out, "\n");

    // fill list S with vertices
    List S = newList();
    for(int i = 1; i <= getOrder(G); i++) {
        append(S, i);
    }
    
    // 2 calls to DFS
    DFS(G, S);
    Graph T = transpose(G);
    DFS(T, S);

    // strongly-connected count
    int scc_count = 0;
    for (moveFront(S); index(S) >= 0; moveNext(S)) {
        int i = get(S);
        if (getParent(T, i) == NIL) {  // if parent of vertex i in S
            scc_count += 1;            // add to SCC
        } 
    }    
    fprintf(out, "G contains %d strongly connected components:\n", scc_count); 
    
    List scc = newList();  // list of SCC
    moveBack(S);           // go to back
    int comp_count = 1;    // component count
    while (length(S) > 0) {
        while (getParent(T, get(S)) != NIL) {  // continue to add until parent == NIL
            prepend(scc, get(S));
            movePrev(S);                       
            deleteBack(S);
        }
        prepend(scc, get(S));  // prepend vertex whose parent is NIL
        if (length(S) != 1) {
            movePrev(S);
            deleteBack(S);
        } else {               // delete last item in stack
            deleteFront(S);
        }
        fprintf(out, "Component %d: ", comp_count); // print SCC comp list
        printList(out, scc);
        fprintf(out, "\n");
        comp_count += 1;
        clear(scc);   // clear scc list before next run
    }
       
    // free everything 
    freeList(&scc);
    fclose(in);
    fclose(out); 
    freeGraph(&G);
    freeGraph(&T);
    freeList(&S);
    return 0;
} 
