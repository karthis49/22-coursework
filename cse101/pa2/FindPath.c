/********************************************************************************* 
 *  * * Karthi Sankar, kasankar 
 *  * * 2022 Spring CSE101 PA2
 *  * * FindPath.c 
 *  * * Main file using List, Graph ADTs 
 *  * *********************************************************************************/


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
    fscanf(in,"%d", &num_vertices);            // scan in first line for ORDER of graph
    Graph G = newGraph(num_vertices);  
    while (vertex != 0 && neighbor != 0) {     // when this ends, print graph 
      fscanf(in,"%d %d", &vertex, &neighbor);
      if (vertex != 0 && neighbor != 0) {      // don't add 0 0 as an edge
          addEdge(G, vertex, neighbor);        // add all edges
      }
    }
    printGraph(out, G);  
    fprintf(out, "\n");
    
    // go to next line?

    int src = -1;
    int dst = -1;
    List L = newList();
    while (src != 0 && dst != 0) {        // scan until second 0 0 is reached
      fscanf(in,"%d %d", &src, &dst);
      if (src != 0 && dst != 0) {         // don't run BFS/getPath on 0 0
          BFS(G, src);
          clear(L);                       // clear list before each getPath()
          int distance = getDist(G, dst);
          if (distance == INF) {          // if dst is not reachable by src
              fprintf(out, "The distance from %d to %d is infinity\n", src, dst);
              fprintf(out, "No %d-%d path exists", src, dst);
          } else {                        // if reachable, print distance and path
	      fprintf(out, "The distance from %d to %d is %d\n", src, dst, distance);
	      fprintf(out, "A shortest %d-%d path is: ", src, dst);
	      getPath(L, G, dst);
              printList(out, L);
	      fprintf(out, "\n");
          }
      }
      fprintf(out, "\n");
    }
    
    // close files and free Graph
    fclose(in);
    fclose(out);
    freeList(&L);
    freeGraph(&G);

    return(0);
}
