#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// A Graph is an dynamically allocated graph of vertices
struct Graph {
    uint32_t vertices; // Number of vertices.
    bool undirected; // Undirected graph?
    bool visited[VERTICES]; // Where have we gone?
    uint32_t matrix[VERTICES][VERTICES]; // Adjacency matrix.
};

// Creates a graph with a specified number of vertices and may be directed or undirected
// Returns a Graph pointer
//
// vertices: the number of vertices in a graph
// undirected: states if the graph is undirected or not
Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) calloc(1, sizeof(Graph)); // dynamically allocated
    G->vertices = vertices;
    G->undirected = undirected;
    return G;
}

// Deletes the graph by freeing memory
// Return type is void
//
// **G: double pointer that must be freed in function
void graph_delete(Graph **G) {
    free(*G);
    *G = NULL; // has to be set to NULL
    return;
}

// Returns the number of vertices a graph has
// Returns a 32-bit integer
//
// G: pointer to a Graph G
uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

// Adds an edge to graph G
// Returns true if adding of edge was successful
// Returns false if otherwise
//
// G: pointer to graph G
// i: vertex in G->matrix
// j: vertex in G->matrix
// k: value of edge to added to graph
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (i < G->vertices && j < G->vertices) {
        G->matrix[i][j] = k;
        if (G->undirected) {
            G->matrix[j][i] = k;
        }
        return true;
    }
    return false;
}

// Check if graph has an edge between two vertices
// Return true if the edge exists
// Returns false if otherwise
//
// G: pointer to graph G
// i: vertex in G->matrix
// j: vertex in G->matrix
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (i < G->vertices && j < G->vertices && G->matrix[i][j] > 0) {
        return true;
    }
    return false;
}

// Returns the value of the edge between two vertices
// Returns a 32-bit integer
// Returns 0 if there is no edge or given vertices are not valid
//
// G: pointer to graph G
// i: vertex in G->matrix
// j: vertex in G->matrix
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (i < G->vertices && j < G->vertices && G->matrix[i][j] > 0) { // if in bounds and edge exists
        return G->matrix[i][j];
    } else {
        return 0;
    }
}

// Checks if the vertex in Graph G has been visited
// Returns true/false depending on if vertex v has been visited
//
// G: pointer to graph G
// v: vertex that is checked
bool graph_visited(Graph *G, uint32_t v) {
    return G->visited[v];
}

// Marks a vertex as visited in graph
// Return type is void
//
// G: pointer to graph G
// v: vertex that is marked visited
void graph_mark_visited(Graph *G, uint32_t v) {
    if (v < G->vertices) { // check bounds
        G->visited[v] = true;
    }
}

// Marks a vertex as unvisited in graph
// Return type is void
//
// G: pointer to graph G
// v: vertex that is marked unvisited
void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = false;
    }
}

void graph_print(Graph *G) {
    for (uint32_t i = 0; i < G->vertices; i += 1) { //print matrix
        for (uint32_t j = 0; j < G->vertices; j += 1) {
            printf("%5" PRIu32, G->matrix[i][j]);
        }
        printf("\n");
    }
    for (uint32_t m = 0; m < G->vertices; m += 1) {
        printf("%d\t", G->visited[m]);
    }
    printf("\n");
}
