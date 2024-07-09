#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

// A Path is a dynamically allocated Path with a number of vertices and length
struct Path {
    Stack *vertices; // The vertices comprising the path.
    uint32_t length; // The total length of the path.
};

// Creates a path with a set number of vertices available and length
// Returns a pointer to the path created
//
// No parameters given
Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p) {
        p->vertices = stack_create(VERTICES); // capacity is max num. of verts
        p->length = 0;
    }
    return p;
}

// Deletes the given path by freeing memory
// Return type is void
//
// p: double pointer to path p that must be freed
void path_delete(Path **p) {
    if (*p && (*p)->vertices) { // if p and p->vertices exists
        stack_delete(&(*p)->vertices); // using stack function on a stack
        free(*p);
        *p = NULL;
    }
    return;
}

// Pushes a vertex v onto the given path
// Returns true if the vertex was successfully pushed to path
// Returns false if not
//
// p: pointer to a Path p
// v: vertex to be pushed to the path
// G: graph used to increase path length
bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    if (!stack_full(p->vertices) && !(stack_empty(p->vertices))) { //if not empty or full
        uint32_t val;
        // pass peeked value into val
        stack_peek(p->vertices, &val);
        p->length += graph_edge_weight(G, val, v); // increase by edge between val and v
    }
    return stack_push(p->vertices, v); // boolean return
}

// Pops a vertex v off the given path
// Returns true if the vertex was successfully popped off path
// Returns false if not
//
// p: pointer to a Path p
// v: vertex to be popped off the path
// G: graph used to decrease path length
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_empty(p->vertices)) { // stack vertices is empty
        return false;
    }
    stack_pop(p->vertices, v);
    if (stack_empty(p->vertices)) { // if stack empty, nothing subtracted from length
        return true;
    }
    uint32_t val;
    // pass peeked value to val
    stack_peek(p->vertices, &val);
    p->length -= graph_edge_weight(G, val, *v); // decrease by edge between val and v
    return true;
}

// Return the number of vertices a Path has
// Returns a 32-bit int
//
// p: pointer to a path p
uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

// Returns the length of a path
// Returns a 32-bit int
//
// p: pointer to a Path p
uint32_t path_length(Path *p) {
    return p->length;
}

// Copies a source path to destination path
// Return type is void
//
// dst: destination path
// src: source path
void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
}

// Prints out the path length and the path itself
// Return type is void
//
// p: pointer to a Path p
// outfile: file pointer to output file
// cities: array whose "cities" will be printed as the vertices of path
void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: ");
    fprintf(outfile, "%" PRIu32 "\n", p->length);
    fprintf(outfile, "Path: ");
    fprintf(outfile, "%s ", cities[0]);
    fprintf(outfile, "-> ");
    // prints path length and first element of cities ->
    stack_print(p->vertices, outfile, cities);
}
