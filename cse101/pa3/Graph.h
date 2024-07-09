/********************************************************************************* 
 *  *  * * Karthi Sankar, kasankar 
 *  *  * * 2022 Spring CSE101 PA3
 *  *  * * Graph.h 
 *  *  * * Header file for Graph ADT 
 *  *  * *********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"

#define UNDEF -4
#define NIL -3

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/

// newGraph()
// returns a Graph pointing to a newly created GraphObj representing a graph having
// n vertices and no edges
Graph newGraph(int n);

// freeGraph()
// frees all heap memory associated with the Graph *pG,
// then sets the handle *pG to NULL
void freeGraph(Graph* pG);

/*** Access functions ***/

// getOrder()
// returns order of G
int getOrder(Graph G);

// getSize()
// returns size of G
int getSize(Graph G);

//getParent()
// pre: 1 ≤ u ≤ getOrder(G)
// will return the parent of vertex u in the DFS tree
// created by DFS()
int getParent(Graph G, int u);

// getDiscover()
// Pre: 1<=u<=n=getOrder(G) 
// will return the discover time of vertex u in DFS()
int getDiscover(Graph G, int u);

// getFinish()
// Pre: 1<=u<=n=getOrder(G) 
// will return the finish time of vertex u in DFS()
int getFinish(Graph G, int u); 

/*** Manipulation procedures ***/

// addEdge()
// pre: u and v MUST BE in the range (1, getOrder(G))
// inserts a new edge joining u to v, 
// i.e. u is added to the adjacency List of v
// and v to the adjacency List of u. 
void addEdge(Graph G, int u, int v);

// addArc()
// pre: u and v MUST BE in the range (1, getOrder(G))
// inserts a new directed edge from u to v,
// i.e. v is added to the adjacency List of u
void addArc(Graph G, int u, int v);

// DFS()
// runs full DFS algorithm using function visit()
// Pre: length(S)==getOrder(G) 
void DFS(Graph G, List S); 

/*** Other operations ***/

// transpose()
// creates new Graph, which is the transpose of G
Graph transpose(Graph G);

// copyGraph()
// returns a new reference (copy) to a graph
Graph copyGraph(Graph G);

// printGraph()
// prints Graph G
void printGraph(FILE* out, Graph G);
