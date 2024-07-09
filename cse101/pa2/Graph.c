/********************************************************************************* 
 *  * * Karthi Sankar, kasankar 
 *  * * 2022 Spring CSE101 PA2
 *  * * Graph.c 
 *  * * Graph ADT 
 *      * *********************************************************************************/


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
    int* distance;
    int order;  // number of vertices
    int size;   // number of edges
    int source; // source for BFS
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
    for (int i = 0; i < (n+1); i++) {
        G->adj[i] = newList();
    }
    G->color = (int*)calloc(n+1, sizeof(int));
    G->parent = (int*)calloc(n+1, sizeof(int));
    G->distance = (int*)calloc(n+1, sizeof(int));
    G->order = n;  // n vertices
    G->size = 0;
    G->source = NIL;  
    return G;
}

// freeGraph()
// frees all heap memory associated with the Graph *pG,
// then sets the handle *pG to NULL
void freeGraph(Graph* pG){
    if (pG != NULL && *pG != NULL)  {
        //for (int i = 1; i <= getOrder(*pG); i++) {
        //    free(&(*pG)->color[i]);
       //     free(&(*pG)->parent[i]); 
       //     free(&(*pG)->distance[i]);
        //} 
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);       
        for (int i = 0; i < getOrder(*pG)+ 1; i++) {  
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
// returns order

// CHECK PRE
int getOrder(Graph G) {
    if(G == NULL ){
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

// getSize()
// returns size
int getSize(Graph G) {
    if(G == NULL ){
        printf("Graph Error: calling getSource() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

// getSource()
// returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called
int getSource(Graph G) {
    if(G == NULL ){
        printf("Graph Error: calling getSource() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (G->source == NIL) {  // BFS has not been called
        return NIL;
    }
    return G->source;
}

//getParent()
// pre: 1 ≤ u ≤ getOrder(G)
// will return the parent of vertex u in the BFS tree
//created by BFS(), or NIL if BFS() has not yet been called.
int getParent(Graph G, int u) {
    if(G == NULL ){
        printf("Graph Error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getParent() for out-of-range vertex");
        exit(EXIT_FAILURE);
    }
    if (G->source == NIL) {  // BFS has not been called
        return NIL;
    }
    return G->parent[u];
}

//getDist()
// pre: 1 ≤ u ≤ getOrder(G)
// returns the distance from the most recent BFS source to vertex u,
// or INF if BFS() has not yet been called
int getDist(Graph G, int u) {
    if(G == NULL ){
        printf("Graph Error: calling getDist() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    } 
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getDist() for out-of-range vertex");
        exit(EXIT_FAILURE);
    }
    if (G->source == NIL) {  // BFS has not been called
        return INF;
    }
    return G->distance[u];
}

//getPath()
// pre: 1 ≤ u ≤ getOrder(G)
// pre: BFS has been called
// pre: getSource(G)!=NIL
// appends to the List L the vertices of a shortest path in G from source to u,
// ,or appends to L the value NIL if no such path exists
void getPath(List L, Graph G, int u){ 
    if(L==NULL){
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(G == NULL ){
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        printf("Graph Error: calling getPath() for out-of-range vertex");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) == NIL) {
        printf("Graph Error: calling getPath() on Graph with undefined source\n");
        exit(EXIT_FAILURE);
    }
    if (u == G->source) {
        append(L, G->source);
    } else if (G->parent[u] == NIL) {
        append(L, NIL);
    } else {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
    return;
}


/*** Manipulation procedures ***/
//makeNull()
// deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G) {
    if(G == NULL ){
        printf("Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }                       //  n + 1
    for (int i = 0; i < getOrder(G)+ 1; i++) {
        clear(G->adj[i]); 
    }
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    return;
}

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
        printf("Graph Error: calling addEdge() for out-of-range vertex");
        exit(EXIT_FAILURE);
    }
    if (v < 1 || v > getOrder(G)) {
        printf("Graph Error: calling addEdge() for out-of-range vertex");
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
        printf("Graph Error: calling getArc() for out-of-range vertex");
        exit(EXIT_FAILURE);
    }
    if (v < 1 || v > getOrder(G)) {
        printf("Graph Error: calling getArc() for out-of-range vertex");
        exit(EXIT_FAILURE);
    }
    // new reference
    List ref = G->adj[u];

    if (length(ref) == 0) {
        append(ref,v);
        G->size += 1;
        return;
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
    ++G->size;
}

// BFS()
// runs BFS algorithm
// setting the color, distance, parent, and source fields of G 
void BFS(Graph G, int s) {
    if(G == NULL ){
        printf("Graph Error: calling BFS() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    // check source
    G->source = s;  // SETTING SOURCE
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->color[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Q = newList();
    append(Q, s);
    while (length(Q) > 0){
        int x = front(Q); //DQ - CHECK
        deleteFront(Q);               // + 1
        //for(int y = 1; y <= length(G->adj[x]); y++) {
        for(moveFront(G->adj[x]); index(G->adj[x]) >= 0; moveNext(G->adj[x])) {
            int y = get(G->adj[x]);
            if(G->color[y] == WHITE) {
                G->color[y] = GRAY;
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(Q, y);  // ENQUEUE
            }
        }
        G->color[x] = BLACK;
    }
    freeList(&Q);
}

/*** Other operations ***/
// printGraph
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
