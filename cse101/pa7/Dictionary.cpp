/********************************************************************************* 
 *  * * Karthi Sankar, kasankar 
 *  * * 2022 Spring CSE101 PA7
 *  * * Dictionary.cpp 
 *  * * Dictionary ADT
 *  * *********************************************************************************/

#include<iostream>
#include<stdexcept>
#include<string>
#include"Dictionary.h"

// Private Constructor --------------------------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v) {
    // Node fields
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right  = nullptr;
}

// Helper Functions -----------------------------------------------------------

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

// transplant()
// used within the remove() function
void Dictionary::transplant(Node* u, Node*v) {
    if (u->parent == nil) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    if (v != nil) {
        v->parent = u->parent;
    }
}

// Class Constructors & Destructors ----------------------------------------

// Dictionary constructor 
// Creates new Dictionary in the empty state. 
Dictionary::Dictionary() {
    // Dictionary fields
    nil = new Node("nil", -1);  // nullptr
    root = nil;
    current = nil;  
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
    // empty state
    nil = new Node("nil", -1);
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
        throw std::logic_error("Dictionary: getValue(): key " + k + " does not exist");
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
    // set parent, left, right to nil
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
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
    if (!contains(k)) {
        throw std::logic_error("Dictionary: remove(): key " + k + " does not exist");
    }
    Node *z = search(root, k);
    if (z == current) {
        current = nil;
    }
    if (z->left == nil) {           // case 1 or case 2.1 (right only)
        transplant(z, z->right);
        delete z;
    }
    else if (z->right == nil) {     //  case 2.2 (left only)
        transplant(z, z->left);
        delete z;
    }
    else {
        Node *y = findMin(z->right);
        if (y->parent != z) {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        delete z;
    }
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
