/********************************************************************************* 
 *  * * Karthi Sankar, kasankar 
 *  * * 2022 Spring CSE101 PA8
 *  * * DictionaryTest.cpp 
 *  * * Test file for Dictionary ADT
 *  * *********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main() {
    
    string s;
    int x;
 
    // WARRIORS
    // new Dictionary A
    Dictionary A;
    A.setValue("Bjelica", 8);
    A.setValue("Chiozza", 2);
    A.setValue("Curry", 30);
    A.setValue("Green", 23);
    A.setValue("Iguodala", 9);
    A.setValue("Kuminga", 00);
    A.setValue("Lee", 1);
    A.setValue("Looney", 5);
    A.setValue("Moody", 4);
    A.setValue("Payton", 0);
    A.setValue("Poole", 3);
    A.setValue("Porter", 32);
    A.setValue("Thompson", 11);
    A.setValue("Toscano", 95);
    A.setValue("Weatherspoon", 15);
    A.setValue("Wiggins", 22);
    A.setValue("Wiseman", 33);

    cout << "Dictionary A: " << endl;
    cout << endl;
    cout << "A.size() = " << A.size() << endl  << A << endl;
    cout << "A_pre: \n" << A.pre_string() << endl;

    Dictionary K = A;
    
    // new Dictionary K
    cout << "Dictionary K: " << endl;
    cout << endl;
    cout << "K.size() = " << K.size() << endl  << K << endl;
    cout << "A == K is " << (A==K ?"true":"false") << endl;

    K.remove("Weatherspoon");
    K.remove("Chiozza");
    K.remove("Wiseman");

    cout << endl;  
    // removed some pairs from K
    cout << "Removed pairs from K:" << endl;
    cout << "K.size() = " << K.size() << endl  << K << endl;

    // contains tests
    cout << "Does the dictionaries contain these keys?" << endl;
    cout << "A contains Curry is " << (A.contains("Curry") ? "true":"false") << endl;
    cout << "K contains Chiozza is " << (K.contains("Chiozza") ? "true":"false") << endl;
    cout << "K contains Poole is " << (K.contains("Poole") ? "true":"false") << endl;
    cout << "K contains Green is " << (K.contains("Green") ? "true":"false") << endl;

    // new Dictionary C
    cout << endl;  
    Dictionary C = A;

    // equals test
    cout << "A == C is " << (A==C ?"true":"false") << endl;

    // add values to C
    cout << endl;  
    C.setValue("Sankar", 15);
    C.setValue("Durant", 35);
    C.setValue("Barbosa", 19);
    C.setValue("Livingston", 34);
    C.setValue("Speights", 5);
    cout << "Dictionary C:" << endl;
    cout << endl;
    cout << "C.size() = " << C.size() << endl  << C << endl;
 
    // getValue tests
    cout << "Values of keys in Dictionary C:" << endl;
    cout << "Thompson: " << C.getValue("Thompson") << endl;
    cout << "Wiggins: " << C.getValue("Wiggins") << endl;
    cout << "Poole: " << C.getValue("Poole") << endl;
    cout << "Looney: " << C.getValue("Looney") << endl;

    // equals test
    cout << endl;  
    cout << "A == C is " << (A==C ?"true":"false") << endl;
 
    // hasCurrent tests    
    cout << endl;  
    cout << "Do the dictionaries have current?" << endl;
    A.begin();
    C.end();
    cout << "A has current is " << (A.hasCurrent() ? "true":"false") << endl;
    cout << "K has current is " << (K.hasCurrent() ? "true":"false") << endl;
    cout << "C has current is " << (C.hasCurrent() ? "true":"false") << endl;

    // currentKey/currentVal + begin/end + next/prev tests
    cout << endl;  
    cout << "Some current keys and values:" << endl;
    cout << "A's current key: " << A.currentKey() << endl;
    cout << "A's current value: " << A.currentVal() << endl;
    cout << endl;  
    A.next();
    A.next();
    cout << "A's current key: " << A.currentKey() << endl;
    cout << "A's current value: " << A.currentVal() << endl;
    cout << endl;  
    A.next();
    cout << "A's current key: " << A.currentKey() << endl;
    cout << "A's current value: " << A.currentVal() << endl;
    cout << endl;  
    cout << "C's current key: " << C.currentKey() << endl;
    cout << "C's current value: " << C.currentVal() << endl;
    cout << endl;
    C.prev();
    C.prev();
    cout << "C's current key: " << C.currentKey() << endl;
    cout << "C's current value: " << C.currentVal() << endl;
    cout << endl;  
    K.begin();
    cout << "K's current key: " << K.currentKey() << endl;
    cout << "K's current value: " << K.currentVal() << endl;
    cout << endl;  
    for (int i = 0; i < 7; i++) {
        K.next();
        C.prev();
    }
    cout << "K's current key: " << K.currentKey() << endl;
    cout << "K's current value: " << K.currentVal() << endl;
    cout << endl;  
    cout << "C's current key: " << C.currentKey() << endl;
    cout << "C's current value: " << C.currentVal() << endl;
    cout << endl;  
    K.end();
    cout << "K's current key: " << K.currentKey() << endl;
    cout << "K's current value: " << K.currentVal() << endl;
    cout << endl;  
    A.end();
    cout << "A's current key: " << A.currentKey() << endl;
    cout << "A's current value: " << A.currentVal() << endl;

    // removed some pairs from C
    cout << endl;  
    cout << "Removed pairs from C:" << endl;
    C.remove("Speights");
    C.remove("Durant");
    C.remove("Payton");
    C.remove("Moody");
    C.remove("Bjelica");
    cout << "C.size() = " << C.size() << endl  << C << endl;
    cout << "C_pre: \n" << K.pre_string() << endl;

    // change some values of K
    cout << "Changed some values of K" << endl;
    K.setValue("Kuminga", 10);
    K.setValue("Green", 50);
    K.setValue("Thompson", 77);
    K.setValue("Curry", 3);
    K.setValue("Poole", 18);
    cout << "K.size() = " << K.size() << endl  << K << endl;
    cout << "K_pre: \n" << K.pre_string() << endl;

    // equals test
    cout << "A == K is " << (A==K ?"true":"false") << endl;

    // do reverse iteration on A
    cout << endl;  
    cout << "Key-value pairs of A: " << endl;
    for(A.end(); A.hasCurrent(); A.prev()){
        s = A.currentKey();
        x = A.currentVal();
        cout << "(" + s + ", " << x << ") ";
    }
    cout << endl << endl;

    // do forward iteration on K
    cout << "Key-value pairs of K: " << endl;
    for(K.begin(); K.hasCurrent(); K.next()){
        s = K.currentKey();
        x = K.currentVal();
        cout << "(" + s + ", " << x << ") ";
    }
    cout << endl << endl;

    // do reverse iteration on C
    cout << "Key-value pairs of C: " << endl;
    for(C.end(); C.hasCurrent(); C.prev()){
        s = C.currentKey();
        x = C.currentVal();
        cout << "(" + s + ", " << x << ") ";
    }
    cout << endl << endl;

    // clear test
    A.clear();
    K.clear();
    C.clear();

    cout << "after clearing: " << endl;
    cout << "A.size() = " << A.size() << endl;
    cout << "K.size() = " << K.size() << endl;
    cout << "C.size() = " << C.size() << endl;
    cout << endl;  

    // check exceptions
    cout << "test pre-condition errors:" << endl; 
    try{
        A.getValue("blah");
    } catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.remove("blah");
    } catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.currentKey();
    } catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.currentVal();
    } catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }  
    try{
        A.next();
    } catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    try{
        A.prev();
    } catch(logic_error& e){
        cout << e.what() << endl;
        cout << "   continuing without interruption" << endl;
    }
    cout << endl;  

    // success!!
    return(0);
}
