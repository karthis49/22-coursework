/********************************************************************************* 
 *  * * Karthi Sankar, kasankar 
 *   * * 2022 Spring CSE101 PA2
 *   * * List.c 
 *   * * List ADT 
 *      * *********************************************************************************/



#include<stdio.h>
#include<stdlib.h> 
#include<assert.h>
#include<stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
    int data;
    Node prev;
    Node next;
} NodeObj;

// private ListObj type
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(ListElement data){
    Node N = malloc(sizeof(NodeObj));
    assert( N!=NULL );
    N->data = data;
    N->prev = NULL;
    N->next = NULL;
    return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
       free(*pN);
       // set prev and next to NULL?
       *pN = NULL;
   }
}

// newList()
// Creates and returns a new empty List.
List newList(void) {
    List L;
    L = malloc(sizeof(ListObj));
    assert( L!=NULL );
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
}

// freeList()
// Frees all heap memory associated with *pL, and sets
// *pL to NULL.   
void freeList(List* pL) {
    if(pL!=NULL && *pL!=NULL) { 
      // delete all elements in List     
      while (length(*pL) > 0) {
          deleteFront(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------


// length()
// Returns the number of elements in L.
int length(List L) {
    if( L==NULL ){
        printf("List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
    if( L==NULL ){
        printf("List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {   // if it is defined
        return (L->index);   
    } else {
        return -1;
    }
 }

// front()
// Returns front element of L. Pre: length()>0
int front(List L) {
    if( L==NULL ){
        printf("List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length < 0 || L->length == 0) {  // change to length()?
        printf("List Error: calling front() on List with undefined length\n");
        exit(EXIT_FAILURE); 
    }
    return (L->front->data);
}

// back()
// Returns back element of L. Pre: length()>0
int back(List L) {
    if( L==NULL ){
        printf("List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length < 0 || L->length == 0) {
        printf("List Error: calling back() on List with undefined length\n");
        exit(EXIT_FAILURE); 
    }
    return (L->back->data);
}

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
    if( L==NULL ){
        printf("List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length < 0 || L->length == 0) {
        printf("List Error: calling get() on List with undefined length\n");
        exit(EXIT_FAILURE); 
    }
    if (L->index < 0) {
        printf("List Error: calling get() on List with undefined index\n");
        exit(EXIT_FAILURE);  
    }
    if (L->cursor == NULL) {
        printf("List Error: calling get() on List with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    return (L->cursor->data); 
}

// equals()
// Returns true iff Lists A and B are in same
// state, and returns false otherwise.
bool equals(List A, List B) {  
    if(A==NULL || B==NULL) {
        printf("List Error: calling equals() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    bool eq;
    Node N, M;

    eq = ( A->length == B->length );
    N = A->front;
    M = B->front;
    while( eq && N!=NULL){
        eq = ( N->data==M->data );
        N = N->next;
        M = M->next;
    }
    return eq;
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L) {
    if( L==NULL ) {
        printf("List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    while (length(L) > 0) {
        deleteFront(L);
    }
}

// set()
// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, int x) {
    if( L==NULL ){
        printf("List Error: calling set() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length < 0 || L->length == 0) {
        printf("List Error: calling set() on List with undefined length\n");
        exit(EXIT_FAILURE); 
    }
    if (L->index < 0) {
        printf("List Error: calling set() on List with undefined index\n");
        exit(EXIT_FAILURE);  
    }
    L->cursor->data = x;  // change value of Node* directly
}

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
    if( L==NULL ){
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0) {  
    L->cursor = L->front;  // set to front
    L->index = 0;  //change to 1? MOVE BACK TO 0?
    }
}

// moveBack()
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L) {
    if( L==NULL ){
        printf("List Error: calling moveBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0) {  
    L->cursor = L->back;  // set to back
    L->index = (L->length)-1;  // MOVE BACK TO LEN-1?
    }
}

// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) {
    if( L==NULL ){
        printf("List Error: calling movePrev() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {  //cursor is defined
        if (L->cursor != L->front) {   //cursor is not at front
            L->cursor = L->cursor->prev;
            L->index -= 1;  //move index back 1
        }
        else if (L->cursor == L->front) {   // cursor is at front
            L->cursor = NULL;   // undefined cursor
            L->index = -1;
             
        }   
    }
}

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
    if( L==NULL ){
        printf("List Error: calling moveNext() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {  //cursor is defined
        if (L->cursor != L->back) {   //cursor is not at back
            L->cursor = L->cursor->next;
            L->index += 1;  //move index up 1
            return;
        }
        else if (L->cursor == L->back) {   // cursor is at back
            L->cursor = NULL;   // undefined cursor
            L->index = -1;
            return;
        }   
    }
}

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int x) {
    if( L==NULL ){
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (L->length == 0) {   // if list is empty
        L->front = L->back = N;
        L->length = 1;
        return;
    }
    if (L->length > 0) {
        N->next = L->front;  // setting of pointers?
        N->prev = NULL;
        (L->front)->prev = N;
        L->front = N; 
        L->length += 1;
        if (L->cursor != NULL) {  // if cursor is defined (OR L->CURSOR)
        	L->index += 1;     //increment index (ex: cursor is on Front)
        }
        return;
    }
}

// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int x) {
    if( L==NULL ){
        printf("List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (L->length == 0) {   // if list is empty
        L->front = L->back = N;
        L->length = 1;
        return;
    }
    if (L->length > 0) {  // not empty
        N->next = NULL;   
        L->back->next = N;  // setting of pointers
        N->prev = L->back;
        L->back = N;
        L->length += 1;
        return;
    }
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
    if( L==NULL ){
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length < 0 || L->length == 0) {
        printf("List Error: calling insertBefore() on List with undefined length\n");
        exit(EXIT_FAILURE); 
    }
    if (L->index < 0) {
        printf("List Error: calling insertBefore() on List with undefined index\n");
        exit(EXIT_FAILURE);  
    }
    //Node N = newNode(x);
    if (L->cursor == L->front) {
        prepend(L, x);
        return;
    }
    Node N = newNode(x);
    N->prev = L->cursor->prev;
    L->cursor->prev = N;
    N->next = L->cursor;
    if (N->prev != NULL) {  
        N->prev->next = N;
    }
    L->index +=1;   // cursor moved
    L->length += 1;  // got longer
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
    if( L==NULL ){
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length < 0 || L->length == 0) {
        printf("List Error: calling insertBefore() on List with undefined length\n");
        exit(EXIT_FAILURE); 
    }
    if (L->index < 0) {
        printf("List Error: calling insertBefore() on List with undefined index\n");
        exit(EXIT_FAILURE);  
    }
    if (L->cursor == L->back) {
        append(L, x);
        return;
    }
    Node N = newNode(x);
    N->next = L->cursor->next;
    L->cursor->next = N;
    N->prev = L->cursor;
    if (N->next != NULL) {  
        N->next->prev = N;
    }
    L->length += 1; // increment length, index doesn't change
}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L) {
    if( L==NULL ){
        printf("List Error: deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length < 0 || L->length == 0) {
        printf("List Error: calling deleteFront() on List with undefined length\n");
        exit(EXIT_FAILURE); 
    }
    if (L->length == 1) {
        freeNode(&L->front);
        L->front = L->back = L->cursor = NULL;
        L->index = -1;
        L->length = 0;
        return;
    }
   /* if (L->index == 0) {
        L->cursor = NULL;
        L->index = -1;
        Node temp = L->front->next;
        L->front->prev = NULL;
        L->front->next->prev = NULL;
        L->front->next = NULL;
        freeNode(&L->front);
        L->front = temp;
    }*/
    Node temp = L->front->next;
    L->front->prev = NULL;
    L->front->next->prev = NULL;
    L->front->next = NULL;
    freeNode(&L->front);
    L->front = temp;
    //L->index -= 1;
    // free temp?
    if (L->index == 0) {
        L->cursor = NULL;
        L->index = -1;
    } else { 
        L->index -= 1;
    }
    L->length -= 1;
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L) {
    if( L==NULL ){
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length < 0 || L->length == 0) {
        printf("List Error: calling deleteBack() on List with undefined length\n");
        exit(EXIT_FAILURE); 
    }
    if (L->length == 1) {
        freeNode(&L->back);
        L->front = L->back = L->cursor = NULL;
        L->index = -1;
        L->length = 0;
        return;
    }
    Node temp = L->back->prev;
    L->back->next = NULL;
    L->back->prev->next = NULL;
    L->back->prev = NULL;
    freeNode(&L->back);
    L->back = temp;
    // free temp
    if (L->index == L->length-1) {
        L->cursor = NULL;
        L->index = -1;
    }
    L->length -= 1; 
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
    if( L==NULL ){
        printf("List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length < 0 || L->length == 0) {
        printf("List Error: calling delete() on List with undefined length\n");
        exit(EXIT_FAILURE); 
    }
    if (L->index < 0) {
        printf("List Error: calling delete() on List with undefined index\n");
        exit(EXIT_FAILURE);  
    }
    if (L->cursor == NULL) {
        printf("List Error: calling delete() on List with undefined cursor\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 1) {
        freeNode(&L->cursor);
        L->front = L->back = L->cursor = NULL;
        L->index = -1;
        L->length = 0;
        return;
    }
    if (index(L) == 0) { //change back L->cursor == L->front?
        deleteFront(L);
        return;
    }
    else if (index(L) == length(L)-1) { //change back L->cursor == L->back?
        deleteBack(L);
        return;
    }
    else { 
        if (L->cursor == NULL) {
        printf("List Error: calling delete() on List with undefined cursor\n");
        exit(EXIT_FAILURE);
        } 
        printf("index %d\n", index(L));
        L->cursor->next->prev = L->cursor->prev;  // move pointers arond deleted node
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next = NULL;
        L->cursor->prev = NULL;
        // set cursor to NULL
        freeNode(&L->cursor);
        L->cursor = NULL;
        L->index = -1;
        L->length -= 1;
    }
    //L->length -= 1;
} 

// Other Functions ------------------------------------------------------------

// printList())
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L) {
    Node N = NULL;
    if( L==NULL ){
        printf("List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    for(N = L->front; N != NULL; N = N->next){
        fprintf(out, FORMAT" ", N->data);
    }
}

// copyList()
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L) {
    Node N = NULL;
    List C = newList();
    for(N = L->front; N != NULL; N = N->next) {  // NEW list with same elements?
        append(C, N->data);
    }
    return C;
}
