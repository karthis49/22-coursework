/********************************************************************************* 
 *  * * Karthi Sankar, kasankar 
 *  * * 2022 Spring CSE101 PA8
 *  * * Dictionary.cpp 
 *  * * Dictionary ADT
 *  * *********************************************************************************/

#include<iostream>
#include<stdexcept>
#include<string>
#include"Dictionary.h"

#define RED   1
#define BLACK 0

// Private Constructor --------------------------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v) {
    // Node fields
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right  = nullptr;
    color = RED;  // initial color of nodes to be inserted
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key;
        s += " : ";
        s += std::to_string(R->val);
        s += "\n";
        inOrderString(s, R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s += R->key;
        s += "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) { 
    if (R == N) {
        return;
    }
    setValue(R->key, R->val);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) {
    if (R == nil) {
        return;
    }
    postOrderDelete(R->left); 
    postOrderDelete(R->right); 
    // check if R->parent->left/right == R and set it to nil before deleting
    if (R->parent->left == R) {
        R->parent->left = nil;
    }
    if (R->parent->right == R) {
        R->parent->right = nil;
    }
    delete R;
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    int comp = 0;
    if (R != nil) {
        comp = k.compare(R->key);
    }
    if (R == nil || k == R->key) {
        return R;
    }
    else if (comp < 0) {  //k < R->key
        return search(R->left, k);
    }
    else {  //k > R->key 
        return search(R->right, k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
    if (R == nil) {
        return nil;
    }
    Node* x = R;
    while (x->left != nil) {
        x = x->left;
    }
    return x;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
     if (R == nil) {
        return nil;
    }
    Node* x = R;
    while (x->right != nil) {
        x = x->right;
    }
    return x;
}

// findNext() -> SUCCESSOR
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N == nil) {
        return nil;
    }
    // N = x, M = y in pseudo
    if (N->right != nil) {
        return findMin(N->right);
    }
    Node *C = N;
    Node *M = N->parent;
    while (M != nil && C == M->right) {
        C = M;
        M = M->parent;
    }
    return M;
}

// findPrev() -> PREDECCESSOR 
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N == nil) {
        return nil;
    }
    // N = x, M = y in pseudo
    if (N->left != nil) {
        return findMax(N->left); 
    }
    Node *C = N;
    Node *M = N->parent;
    while (M != nil && C == M->left) {
        C = M;
        M = M->parent;
    }
    return M;
}

// RBT Helper Functions (Optional) -----------------------------------------
   
// LeftRotate()
void Dictionary::LeftRotate(Node* N) {
    // set y, x = N
    Node* y = N->right;

    // turn y's left subtree into x's right subtree
    N->right = y->left;
    if (y->left != nil) { 
        y->left->parent = N;  // conditional not needed
    }
 
    // link y's parent to x
    y->parent = N->parent;
    if (N->parent == nil) {
        root = y;
    }
    else if (N == N->parent->left) {
        N->parent->left = y;
    }
    else {
        N->parent->right = y;
    }

    // put x on y's left
    y->left = N; 
    N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N) {
    // set y, x = N
    Node* y = N->left;

    // turn y's right subtree into x's left subtree
    N->left = y->right;
    if (y->right != nil) {
        y->right->parent = N;  // conditional not needed
    }

    // link y's parent to x
    y->parent = N->parent;
    if (N->parent == nil) {
        root = y;
    }
    else if (N == N->parent->right) {
        N->parent->right = y;
    }
    else {
        N->parent->left = y;
    }

    // put x on y's right
    y->right = N; 
    N->parent = y;
}

// RB_InsertFixUp()
void Dictionary::RB_InsertFixUp(Node* N) {
    Node* z = N;
    Node* y;
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color == RED) {                 
                z->parent->color = BLACK;          // case 1
                y->color = BLACK;                  // case 1
                z->parent->parent->color = RED;    // case 1
                z = z->parent->parent;             // case 1
            }
            else {
                if (z == z->parent->right) {       
                    z = z->parent;                 // case 2
                    LeftRotate(z);                 // case 2
                }
                z->parent->color = BLACK;          // case 3
                z->parent->parent->color = RED;    // case 3
                RightRotate(z->parent->parent);    // case 3
            }
        }
        else {
            y = z->parent->parent->left;
            if (y->color == RED) {                 
                z->parent->color = BLACK;          // case 4
                y->color = BLACK;                  // case 4
                z->parent->parent->color = RED;    // case 4
                z = z->parent->parent;             // case 4
            }
            else {
                if (z == z->parent->left) {       
                    z = z->parent;                 // case 5 
                    RightRotate(z);                // case 5
                } 
                z->parent->color = BLACK;          // case 6
                z->parent->parent->color = RED;    // case 6
                LeftRotate(z->parent->parent);     // case 6s
            }
        }
    }
    root->color = BLACK;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N) {
    Node* w;
    while (N != root && N->color == BLACK) {
        if (N == N->parent->left) {
            w = N->parent->right;
            if (w->color == RED) {
                w->color = BLACK;              // case 1
                N->parent->color = RED;        // case 1
                LeftRotate(N->parent);         // case 1
                w = N->parent->right;          // case 1
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;                // case 2
                N = N->parent;                 // case 2
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;    // case 3
                    w->color = RED;            // case 3
                    RightRotate(w);            // case 3
                    w = N->parent->right;      // case 3
                }
                w->color = N->parent->color;   // case 4
                N->parent->color = BLACK;      // case 4
                w->right->color = BLACK;       // case 4
                LeftRotate(N->parent);         // case 4
                N = root;                      // case 4
            }
        }
        else {
            w = N->parent->left;
            if (w->color == RED) {
                w->color = BLACK;              // case 5
                N->parent->color = RED;        // case 5
                RightRotate(N->parent);        // case 5
                w = N->parent->left;           // case 5
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;                // case 6
                N = N->parent;                 // case 6
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;   // case 7
                    w->color = RED;            // case 7
                    LeftRotate(w);             // case 7
                    w = N->parent->left;       // case 7
                }
                w->color = N->parent->color;   // case 8
                N->parent->color = BLACK;      // case 8
                w->left->color = BLACK;        // case 8
                RightRotate(N->parent);        // case 8
                N = root;                      // case 8
            }
        }
    }
    N->color = BLACK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N) {
    Node* y = N;
    int y_original_color = y->color;  // save y's original color
    Node* x;
    // z = N
    if (N->left == nil) {
        x = N->right;
        RB_Transplant(N, N->right);
    }
    else if (N->right == nil) {
        x = N->left;
        RB_Transplant(N, N->left);
    }
    else {
        y = findMin(N->right);
        y_original_color = y->color;  
        x = y->right;
        if (y->parent == N) {
            x->parent = y;
        }
        else {
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    if (y_original_color == BLACK) {  
        RB_DeleteFixUp(x);
    }
}

// Class Constructors & Destructors ----------------------------------------

// Dictionary constructor 
// Creates new Dictionary in the empty state. 
Dictionary::Dictionary() {
    // Dictionary fields
    nil = new Node("nil", -1);  // nullptr
    nil->color = BLACK;
    root = nil;
    current = nil;  
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
    // empty state
    nil = new Node("nil", -1);
    nil->color = BLACK;
    root = nil;
    current = nil; 
    num_pairs = 0;

    // make a copy of Dictionary
    preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
    clear();
    delete nil;
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
    if (num_pairs == 0) {  // empty
        return false;
    }
    if (search(root, k) != nil) {
        return true;
    }
    return false;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
    if (!contains(k)) {
        throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
    }
    Node* x = search(root, k);    
    return x->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
    if (current != nil) {  
        return true;
    }
    return false;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
    if (size() == 0) {
        return;         // if dict empty, do nothing
    }
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
    // pair does not exist
    if (root->key == k) {
        root->val = v;
        return;
    }
    Node* z = new Node(k, v);
    // set left, right to nil
    z->left = nil;
    z->right = nil;

    Node* y = nil;
    Node* x = root;
    int comp_zx, comp_zy; 
    while (x != nil) {
        comp_zx = z->key.compare(x->key);
        y = x;
        if (comp_zx < 0) {  // z->key < x->key
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y != nil) {   // used to compare z->key and y->key
        comp_zy = z->key.compare(y->key);
    }
    if (y == nil) {
        //z->parent = nil;
        root = z;     // tree was empty
    }
    // pair with key==k exists
    else if (y->key == k) {
        y->val = v;
        delete z;
        return;
    }
    else if (comp_zy < 0) {  // z->key < y->key
        y->left = z;
    }
    else {
        y->right = z;
    }
    num_pairs += 1;
    z->left = nil;
    z->right = nil;
    z->color = RED;
    RB_InsertFixUp(z);
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
    if (!contains(k)) {
        throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
    }
    Node *z = search(root, k);
    if (z == current) {
        current = nil;
    }

    RB_Delete(z);
    delete z;
    num_pairs -= 1;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {
    if (root != nil) { 
        current = findMin(root);
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {
    if (root != nil) {
        current = findMax(root);
    }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: next(): current undefined");
    }
    current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
    if (!hasCurrent()) {
        throw std::logic_error("Dictionary: prev(): current undefined");
    }
    current = findPrev(current);
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
    std::string s = "";
    inOrderString(s, root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
    std::string s = "";
    preOrderString(s, root);
    return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
    bool to_eq = (to_string() == D.to_string());
    return to_eq;
}


// Overloaded Operators ----------------------------------------------------
   
// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
    if (this != &D) {
        Dictionary temp = D;
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;
}
