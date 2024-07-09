#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "vui:o:h" // : -> argument after option

// Depth-first search to find the shortest Hamiltonian path of cities
// Return type is void
//
// G: pointer to a Graph g
// v: vertex that will be checked with each call of DFS
// curr: pointer to a Path curr
// shortest: pointer to a Path shortest
// cities: array of city names (vertices) to be navigated
// outfile: file pointer to an output file
// verbose: bool that states whether or not -v option is used
// rec_count: counts the number of recursive calls of DFS
void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile,
    bool verbose, int *rec_count) {
    //if path_vertices is one before the end && edge connects back to origin
    if ((path_vertices(curr) + 1) == graph_vertices(G) && graph_has_edge(G, v, START_VERTEX)) {
        // check if shortest length is 0 or curr length is less than shortest length
        if (path_length(shortest) == 0 || path_length(curr) < path_length(shortest)) {
            path_push_vertex(curr, START_VERTEX, G);
            if (verbose) { // print all Ham. paths
                path_print(curr, outfile, cities);
            }
            path_copy(shortest, curr); //copy current to shortest
        }
    } else { // i = 1 because START_VERTEX is used in first call of DFS
        for (uint32_t i = 1; i < graph_vertices(G); i += 1) { // iterate through full graph
            // if there is edge from v to i && i has not been visited
            if (graph_has_edge(G, v, i) && !(graph_visited(G, i))) {
                path_push_vertex(curr, i, G);
                graph_mark_visited(G, i);
                *rec_count += 1; // add to total recursive calls
                dfs(G, i, curr, shortest, cities, outfile, verbose,
                    rec_count); // call DFS with new v (== i)
            }
        }
        uint32_t x;
        graph_mark_unvisited(G, v);
        path_pop_vertex(curr, &x, G);
    }
}

// Main function that will run the full program
// Returns 0 to indicate program end/success
//
// argc: argument counter
// argv: array of strings
int main(int argc, char **argv) {
    bool undirect = false;
    bool verbose = false;
    bool help = false;

    FILE *infile = stdin; // default is stdin/stdout
    FILE *outfile = stdout;

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': help = true; break;
        case 'v': verbose = true; break;
        case 'u': undirect = true; break;
        case 'i':
            infile = fopen(optarg, "r"); // input file to be used
            if ((infile = fopen(optarg, "r")) == NULL) {
                fprintf(stderr, "The input file given is not valid\n");
                exit(1);
            }
            break;
        case 'o':
            outfile = fopen(optarg, "w"); // output file to be used
            if ((outfile = fopen(optarg, "w")) == NULL) {
                fprintf(stderr, "The output file given is not valid\n");
                exit(1);
            }
            break;
        default: break;
        }
    }

    // Help Message
    if (help) {
        fprintf(outfile, "SYNOPSIS\n");
        fprintf(outfile, "   Traveling Salesman Problem using DFS.\n");
        fprintf(outfile, "USAGE\n");
        fprintf(outfile, "   .tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n");
        fprintf(outfile, "OPTIONS\n");
        fprintf(outfile, "   -u             Use undirected graph.\n");
        fprintf(outfile, "   -v             Enable verbose printing.\n");
        fprintf(outfile, "   -h             Program usage and help.\n");
        fprintf(outfile, "   -i infile      Input containing graph (default: stdin)\n");
        fprintf(outfile, "   -o outfile     Output of computed path (default: stdout)\n");
    }

    // GETTING INPUT/PRINTING OUTPUT

    uint32_t num_vertices;
    fscanf(infile, "%" SCNu32 "\n", &num_vertices); // scan number of vertices from input
    if (num_vertices > VERTICES) {
        fprintf(stderr, "The number of vertices given is not valid\n"); // error if not < VERTICES
        exit(1);
    }

    char buf[1024]; // buffer
    char *cities[num_vertices]; // zeroed out (STATIC) array of VERTICES size

    char *fgets_input;
    for (uint32_t i = 0; i < num_vertices; i += 1) {
        if ((fgets_input = fgets(buf, 1024, infile)) == NULL) {
            fprintf(stderr, "The vertice given is not valid");
            exit(1);
        }
        buf[strlen(buf) - 1] = '\0';
        cities[i] = strdup(buf); // save a copy of string (FREE IT LATER)
    }

    Graph *g = graph_create(num_vertices, undirect); // graph to be used

    uint32_t i = 0; // i vertex in graph
    uint32_t j = 0; // j vertex in graph
    uint32_t k = 0; // k edge in graph
    int suc;
    while ((suc = fscanf(infile, "%" SCNu32 " %" SCNu32 " %" SCNu32 "\n", &i, &j, &k)) != EOF) {
        if (suc != 3) {
            fprintf(stderr, "The edge given is not valid\n");
            exit(1);
        }
        graph_add_edge(g, i, j, k);
    }

    Path *current;
    Path *shortest;
    current = path_create(); // current path in DFS
    shortest = path_create(); // shortest path in DFS

    int recur_count = 0;
    dfs(g, START_VERTEX, current, shortest, cities, outfile, verbose, &recur_count);
    path_print(shortest, outfile, cities); // print the shortest path
    fprintf(outfile, "Total recursive calls: "); // print recursive calls
    fprintf(outfile, "%d\n", recur_count);

    // FREE EVERYTHING
    fclose(infile);
    fclose(outfile);
    graph_delete(&g);
    path_delete(&current);
    path_delete(&shortest);
    // FREE STRINGS IN CITIES ARRAY
    for (uint32_t n = 0; n < num_vertices; n += 1) {
        free(cities[n]);
    }
    return 0; // success/end of program
}
