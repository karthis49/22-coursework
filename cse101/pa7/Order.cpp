/********************************************************************************* 
 *  * * Karthi Sankar, kasankar 
 *  * * 2022 Spring CSE101 PA7
 *  * * Order.cpp 
 *  * * Main file, uses Dictionary ADT
 *  * *********************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

using namespace std;

int main(int argc, char * argv[]){

    int line_count;
    ifstream in;
    ofstream out;
    string line;

    // check command line for correct number of arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // open files for reading and writing 
    in.open(argv[1]);
    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    Dictionary D;

    // read each line of input file, then add to dictionary
    line_count = 1;
    while (getline(in, line)) {
        D.setValue(line, line_count);
        line_count++;        
    }
    
    // print Dictionary + new line + pre_string
    out << D << endl;
    out << endl;
    out << D.pre_string() << endl;

    // close files 
    in.close();
    out.close();

    // success!
    return(0);
}
