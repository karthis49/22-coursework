#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

// A stack is a dynamically allocated stack of items
struct Stack {
    uint32_t top; // Index of the next empty slot .
    uint32_t capacity; // Number of items that can be pushed .
    uint32_t *items; // Array of items , each with type uint32_t .
};

// Creates a stack with a specified capacity
// Returns a pointer to a created stack
//
// capacity: the size of the stack
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t)); // dyn. alloc. array of ints
        if (!s->items) {
            free(s);
            s = NULL; // has to be set to NULL after freeing
        }
    }
    return s;
}

// Deletes the specified stack
// Return type is void
//
// s: double pointer to stack s that must be freed
void stack_delete(Stack **s) {
    if (*s && (*s)->items) { // if s and items both exists
        free((*s)->items);
        free(*s); // free both
        *s = NULL;
    }
    return;
}

// Will be the size of the given stack
// Returns a 32-bit int that is the size of the Stack
//
// s: pointer to a Stack s
uint32_t stack_size(Stack *s) {
    return s->top;
}

// Check if a stack is empty or not
// Returns true is the stack is empty
// Returns false if not
//
// s: pointer to a Stack s
bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    } else {
        return false;
    }
}

// Check if a stack is full or not
// Returns true is the stack is full
// Returns false if not
//
// s: pointer to a Stack s
bool stack_full(Stack *s) {
    if (s->top == s->capacity) {
        return true;
    }
    return false;
}

// Pushes a vertex onto the stack
// Returns true if the push onto the stack is successful
// Returns false if not
//
// s: pointer to a Stack s
// x: the value that is pushed onto the stack
bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = x;
    s->top += 1;
    return true;
}

// Pops a vertex off the stack
// Returns true if the pop off the stack is successful
// Returns false if not
//
// s: pointer to a Stack s
// x: pointer to the value that is popped off the stack
bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    // pass popped value back through ptr x
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}

// Peeks at an element at the top of the stack
// Returns true if the peek was successful
// Returns false if not
//
// s: pointer to a Stack s
// x: pointer to the value that is peeked at
bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    // pass value at top to ptr x?
    *x = s->items[s->top - 1];
    return true;
}

// Copies a source stack to a destination stack
// Return type is void
//
// dst: pointer to a destination stack
// src: pointer to a source stack
void stack_copy(Stack *dst, Stack *src) {
    if (dst->capacity == src->capacity) {
        for (uint32_t i = 0; i < src->top; i += 1) {
            dst->items[i] = src->items[i];
        }
    }
    dst->top = src->top;
}

// Prints the given stack
// Return type is void
//
// s: pointer to a Stack s
// outfile: pointer to output file
// cities: pointeter to array that contains items of stack
void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
