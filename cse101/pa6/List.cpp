/********************************************************************************* 
 *  * * Karthi Sankar, kasankar 
 *  * * 2022 Spring CSE101 PA6
 *  * * List.cpp 
 *  * * List ADT 
 *  * *********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------
   
// Creates new List in the empty state.
List::List() {
    frontDummy = new Node(-100);  // contain values that wouldn't be used
    backDummy = new Node(-200);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// Copy constructor.
List::List(const List& L) {
    // create empty state   
    frontDummy = new Node(-100);
    backDummy = new Node(-200);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    pos_cursor = 0;
    num_elements = 0;

    // load elements into this
    Node* N = L.frontDummy->next;
    while (N->next != nullptr) {
        this->insertBefore(N->data);
        N = N->next;
    }  
}

// Destructor
List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}


// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
    return (num_elements);
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
    if( num_elements==0 || num_elements < 0){
        throw std::length_error("List: front(): empty list");
    }
    return(frontDummy->next->data);
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
    if( num_elements==0 || num_elements < 0){
        throw std::length_error("List: back(): empty list");
    }
    return(backDummy->prev->data);
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
    if(pos_cursor < 0 || pos_cursor > num_elements){
        throw std::range_error("List: position(): cursor out of range");
    }
    return (pos_cursor);
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
    if(pos_cursor > num_elements || pos_cursor == num_elements){
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
    if(pos_cursor < 0 || pos_cursor == 0){
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return beforeCursor->data;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    moveFront();
    while (num_elements > 0) {
        eraseAfter();
    }
}
        

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    pos_cursor = length();
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
    if(pos_cursor > num_elements || pos_cursor == num_elements){
        throw std::range_error("List: moveNext(): cursor at back");
    }
    pos_cursor += 1;
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
    if(pos_cursor < 0 || pos_cursor == 0){
        throw std::range_error("List: movePrev(): cursor at front");
    }
    pos_cursor -= 1;
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
    Node* N = new Node(x);
    beforeCursor->next = N;
    N->prev = beforeCursor;
    afterCursor->prev = N;
    N->next = afterCursor;
    afterCursor = N;
    num_elements += 1;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
    Node* N = new Node(x);
    beforeCursor->next = N;
    N->prev = beforeCursor;
    afterCursor->prev = N;
    N->next = afterCursor;
    beforeCursor = N;
    pos_cursor += 1;
    num_elements += 1;    
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
    if(pos_cursor > num_elements || pos_cursor == num_elements){
        throw std::range_error("List: setAfter(): cursor at back");
    }
    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
    if(pos_cursor < 0 || pos_cursor == 0){
        throw std::range_error("List: setAfter(): cursor at front");
    }
    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
    if(pos_cursor > num_elements || pos_cursor == num_elements){
        throw std::range_error("List: eraseAfter(): cursor at back");
    }
    // temp node to delete
    Node* temp = afterCursor;
    // adjust before/after ptrs
    afterCursor = afterCursor->next;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    // delete node
    delete temp;
    num_elements -= 1;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
    if(pos_cursor < 0 || pos_cursor == 0){
        throw std::range_error("List: eraseBefore(): cursor at front");
    }
    // temp node to delete
    Node* temp = beforeCursor;
    // adjust before/after ptrs
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    // delete node
    delete temp;
    pos_cursor -= 1;
    num_elements -= 1;
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {
    while(pos_cursor < num_elements) {
        if (afterCursor->data == x) {
            moveNext();
            return pos_cursor;
        }
        moveNext();
    }
    pos_cursor = length();
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
    while(pos_cursor > 0) {
        if (beforeCursor->data == x) {
            movePrev();
            return pos_cursor;
        }
        movePrev();
    }
    pos_cursor = 0;
    return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    List uniq_vals;
    Node* curr = frontDummy->next;
    while (curr != backDummy) {
        if (uniq_vals.findNext(curr->data) != -1) {  // element found in uniq_vals
            // store node to be deleted
            Node *N = curr;
            // move pointers around deleted node
            curr->next->prev = curr->prev;
            curr->prev->next = curr->next;
            // adjust BC and AC depending on eB or eA 
            // if cursor is next to curr. element
            if (curr == beforeCursor) {
                beforeCursor = curr->prev;
                afterCursor = beforeCursor->next;
                if (num_elements > pos_cursor) {
                    pos_cursor -= 1;
                }
            }
            if (curr == afterCursor) {
                afterCursor = curr->next;
                beforeCursor = afterCursor->prev;
                if (num_elements > pos_cursor) {
                    pos_cursor -= 1;
                }
            }
            curr = curr->next;
            // delete node
            delete N;
            num_elements -= 1;
            if (num_elements < pos_cursor || num_elements == pos_cursor) {
                pos_cursor -= 1;    
            }
            uniq_vals.moveFront();  // for find_next()
            continue;
        } 
        // add element to uniq_vals
        uniq_vals.insertBefore(curr->data);
        curr = curr->next;
        uniq_vals.moveFront();  // for find_next()
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
    List K;
    Node *f = this->frontDummy->next;
    Node *s = L.frontDummy->next;
    while (f != this->backDummy) {
        K.insertBefore(f->data);
        f = f->next;
    }
    while (s != L.backDummy) {
        K.insertBefore(s->data);
        s = s->next;
    }
    K.moveFront();
    return K;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    Node* N = nullptr;
    std::string s = "";
    for (N = frontDummy->next; N != backDummy; N=N->next){
      if (N == frontDummy->next) {
          s += "(";
      }
      s += std::to_string(N->data);
      if (N != backDummy->prev) { 
          s += ", ";
      }
      if (N == backDummy->prev) {
          s += ")";
      }
    }
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
    bool eq = false;
    Node *N = frontDummy;
    Node *M = frontDummy;

    eq = (this->num_elements == R.num_elements);
    N = this->frontDummy->next;
    M = R.frontDummy->next;
    while (eq && N != nullptr) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
    if (this != &L) {
        List temp = L;
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(num_elements, temp.num_elements);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
    }
    return *this;
}

