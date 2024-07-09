#include "pq.h"
#include "node.h"
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

struct PriorityQueue {
    uint32_t capacity;
    uint32_t size;
    Node **items;
};

// Contructs a priority queue with capacity, size, items
// Returns a pointer to created PQ
//
// capacity: number of items a PQ can hold
PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->capacity = capacity;
        q->size = 0; // 1-based index
        q->items = (Node **) calloc(capacity + 1, sizeof(Node *));
    }
    return q;
}

// Destructs an existing PQ
// Return type is void
//
// q: double pointer to be freed in function
void pq_delete(PriorityQueue **q) { // need to change?
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

// Checks if PQ is empty
// Returns boolean to say whether or not it is
//
// q: pointer to a PQ
bool pq_empty(PriorityQueue *q) {
    if (q->size == 0) {
        return true;
    }
    return false;
}

// Checks if PQ is full
// Returns boolean to say whether or not it is
//
//  q: pointer to a PQ
bool pq_full(PriorityQueue *q) {
    if (q->size == q->capacity) {
        return true;
    }
    return false;
}

// The size of the queue is returned
// Returns a 32-bit unsigned int
//
//  q: pointer to a PQ
uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

// Inserts a node into min heap (items)
// Return type is void
//
//  q: pointer to a PQ
// n: pointer to node to be inserted
void min_heap_insert(PriorityQueue *q, Node *n) {
    uint32_t i = q->size + 1;
    uint32_t parent = i / 2;
    q->items[i] = n;
    while (i > 1 && q->items[parent]->frequency > q->items[i]->frequency) {
        Node *temp = q->items[parent]; // swap parent and i
        q->items[parent] = q->items[i];
        q->items[i] = temp;
        i = parent;
        parent = i / 2;
    }
}

// Makes a heap follow min heap property
// Return type is void
//
//  q: pointer to a PQ
//  i: integer index to start with
void min_heapify(PriorityQueue *q, uint32_t i) {
    uint32_t left_child = i * 2;
    uint32_t right_child = i * 2 + 1;
    uint32_t smallest = 0;
    if (left_child <= q->size && q->items[left_child]->frequency < q->items[i]->frequency) {
        smallest = left_child;
    } else {
        smallest = i;
    }
    if (right_child <= q->size
        && q->items[right_child]->frequency < q->items[smallest]->frequency) {
        smallest = right_child;
    }
    if (smallest != i) {
        Node *temp = q->items[i]; // swap parent and i
        q->items[i] = q->items[smallest];
        q->items[smallest] = temp;
        min_heapify(q, smallest);
    }
}

// Enqueues a node into a PQ
// Returns a boolean if enq. was done
//
// q: pointer to a PQ
// n: node to enqueue
// CITE: function covered in Eric's tutoring session
bool enqueue(PriorityQueue *q, Node *n) {
    // check if PQ is full
    if (pq_full(q)) {
        return false;
    } else {
        min_heap_insert(q, n);
        q->size += 1;
        return true;
    }
}

// Dequeues a node from a PQ
// Returns a boolean if deq. was done
//
// q: pointer to a PQ
// n: node that was dequeued
// CITE: function covered in Eric's tutoring session
bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    } else {
        *n = q->items[1];
        q->items[1] = q->items[q->size];
        q->size -= 1;
        min_heapify(q, 1);
        return true;
    }
}

void pq_print(PriorityQueue *q) {
    for (uint32_t i = 0; i < q->size; i += 1) {
        printf("%5" PRIu64, q->items[i]->frequency);
    }
}
