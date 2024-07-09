/********************************************************************************* 
 *  * * Karthi Sankar, kasankar 
 *  * * 2022 Spring CSE101 PA3
 *  * * Graph.c 
 *  * * Graph ADT 
 *  * *********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include"List.h"
#include"Graph.h"

#define WHITE -1
#define GRAY 0
#define BLACK 1

typedef struct GraphObj{
    List* adj;
    int* color;
    int* parent;
    int* discover;
    int* finish;
    int order;  // number of vertices
    int size;   // number of edges
} GraphObj;


/*** Constructors-Destructors ***/
// newGraph()
// returns a Graph pointing to a newly created GraphObj representing a graph having
// n vertices and no edges
Graph newGraph(int n) {
    Graph G;
    G = malloc(sizeof(GraphObj));
    assert(G!=NULL);
    G->adj = (List*)malloc((n+1)*sizeof(List));
    // fill each vertex with empty adj. List
    for (int i = 1; i < (n+1); i++) {
        G->adj[i] = newList();
    }
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->discover = calloc(n+1, sizeof(int));
    G->finish = calloc(n+1, sizeof(int));
    for (int i = 1; i <= n; i++) {
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }   
    G->order = n;  // n vertices
    G->size = 0;
    return G;
}

// freeGraph()
// frees all heap memory associated with the Graph *pG,
// then sets the handle *pG to NULL
void freeGraph(Graph* pG){
    if (pG != NULL && *pG != NULL)  {
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->discover); 
        free((*pG)->finish); 
        for (int i = 1; i < getOrder(*pG)+ 1; i++) {  
           freeList(&(*pG)->adj[i]);
        }
        free((*pG)->adj);     
        free(*pG);
        *pG = NULL;
    }
    return;
}

/*** Access functions ***/
// getOrder()
// returns order of G
int getOrder(Graph G) {
    if(G == NULL ){
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

// getSize()
// returns size of G
int getSize(Graph G) {
    if(G == NULL ){
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

//getParent()
// pre: 1 ≤ u ≤ getOrder(G)
// will return the parent of vertex u in the DFS tree
// created by DFS()
int getParent(Graph G, int u) {
    if(G == NULL ){
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getParent() for out-of-range vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}

// getDiscover()
// Pre: 1<=u<=n=getOrder(G) 
// will return the discover time of vertex u in DFS()
int getDiscover(Graph G, int u) {
    if(G == NULL ){
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getParent() for out-of-range vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->discover[u];
}

// getFinish()
// Pre: 1<=u<=n=getOrder(G) 
// will return the finish time of vertex u in DFS()
int getFinish(Graph G, int u) {
    if(G == NULL ){
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getParent() for out-of-range vertex\n");
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
} 

/*** Manipulation procedures ***/

// addEdge()
// pre: u and v MUST BE in the range (1, getOrder(G))
// inserts a new edge joining u to v, 
// i.e. u is added to the adjacency List of v
// and v to the adjacency List of u. 
void addEdge(Graph G, int u, int v) {
    if(G == NULL ){
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: addEdge() -> u is out of range\n");
        exit(EXIT_FAILURE);
    }
    if (v < 1 || v > getOrder(G)) {
        printf("Graph Error: addEdge() -> v is out of range\n");
        exit(EXIT_FAILURE);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    --G->size;
}

// addArc()
// pre: u and v MUST BE in the range (1, getOrder(G))
// inserts a new directed edge from u to v,
// i.e. v is added to the adjacency List of u
void addArc(Graph G, int u, int v) {
    if(G == NULL ){
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: addArc() -> u is out of range\n");
        exit(EXIT_FAILURE);
    }
    if (v < 1 || v > getOrder(G)) {
        printf("Graph Error: addArc() -> u is out of range\n");
        exit(EXIT_FAILURE);
    }
   
    // new reference
    List ref = G->adj[u];

    // if duplicate, return (do nothing)
    for (moveFront(ref); index(ref) >= 0; moveNext(ref)) {
        int x = get(ref);
        if (x == v)  {  // u-v edge already exists!
            return;
        }  
    }

    // iter through list
    moveFront(ref);
    while(index(ref) > -1 && v > get(ref)) {
        moveNext(ref);
    }
    // come to end
    if(index(ref) < 0) {
        append(ref,v);
    }
    else {
        insertBefore(ref,v);
    }
    
    ++G->size;  // increment in this case
}

// visit()
// private recursive helper function for DFS
// called in DFS() main loop
void visit(Graph G, List V, int x, int* time) {
    G->discover[x] = (++*time);
    G->color[x] = GRAY;
    // increasing vertex label order
    for(moveFront(G->adj[x]); index(G->adj[x]) >= 0; moveNext(G->adj[x])) {
        int y = get(G->adj[x]);
        if (G->color[y] == WHITE) {
            G->parent[y] = x;
            visit(G, V, y, &(*time));
        }
    }
    G->color[x] = BLACK;
    G->finish[x] = (++*time);
    
    // push onto stack and delete back
    prepend(V, x);
}

// DFS()
// runs full DFS algorithm using function visit()
// Pre: length(S)==getOrder(G) 
void DFS(Graph G, List S) {
    if(G == NULL) {
        printf("Graph Error: calling BFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(S) != getOrder(G)) {
        printf("Graph Error: DFS() -> length of List S != number of vertices\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }
    int final_time = 0;
    List V = copyList(S); 
    clear(S);
    for(moveFront(V); index(V) >= 0; moveNext(V)) {
        int i = get(V);
        if (G->color[i] == WHITE) {
            visit(G, S, i, &final_time);
        }
    } 
    // then clear C (copy) and S would contain vertices
    freeList(&V); 
}

/*** Other operations ***/
// printGraph()
// prints Graph G
void printGraph(FILE* out, Graph G) {
    if(G == NULL ){
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < getOrder(G)+1; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}

// transpose()
// creates new Graph, which is the transpose of G
Graph transpose(Graph G) {
    Graph T = newGraph(getOrder(G));
    for (int u = 1; u < getOrder(G)+ 1; u++) {
        for(moveFront(G->adj[u]); index(G->adj[u]) >= 0; moveNext(G->adj[u])) {
            int v = get(G->adj[u]);
            addArc(T, v, u); 
        }
    }
    return T;
}

// copyGraph()
// returns a new reference (copy) to a graph
Graph copyGraph(Graph G) {
    Graph C = newGraph(getOrder(G));   
    for (int i = 1; i <(getOrder(G)+1); i++) {
        for (moveFront(G->adj[i]); index(G->adj[i]) >= 0; moveNext(G->adj[i])) { 
            addArc(C, i, get(G->adj[i]));
        }
    }
    for (int i = 1; i <= getOrder(G); i++) {
        C->color[i] = G->color[i];
        C->parent[i] = getParent(G, i);
        C->discover[i] = getDiscover(G, i);
        C->finish[i] = getFinish(G, i);
    } 
    //copy color, parent, discover, finish

    return C;
}
