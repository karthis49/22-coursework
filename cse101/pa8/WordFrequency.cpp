/********************************************************************************* 
 *  * * Karthi Sankar, kasankar 
 *  * * 2022 Spring CSE101 PA8
 *  * * WordFrequency.cpp 
 *  * * Main: counts the number of occurences of each word in an input file
 *  * ****************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include "Dictionary.h"

using namespace std;

int main (int argc, char * argv[]) {

    size_t begin, end, len;
    ifstream in;
    ofstream out;
    string line;
    string token;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

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

    // create new, empty Dictionary
    Dictionary A;

    while (getline(in, line)) {
        len = line.length();       
 
        // get first token
        begin = min(line.find_first_not_of(delim, 0), len);
        end   = min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end-begin);
      
        while (token != "") {  // we have a token
        
            for (auto& c : token) {
                c = tolower(c);
            }

            if (A.contains(token) == true) {
                A.getValue(token) += 1;
            }
            else {
                A.setValue(token, 1);
            }

            // get next token
            begin = min(line.find_first_not_of(delim, end+1), len);
            end   = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end-begin);
        }
    }
 
    out << A.to_string() << endl;

    // close files 
    in.close();
    out.close();

    return(0);
}

