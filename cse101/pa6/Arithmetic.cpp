/********************************************************************************* 
 *  * * Karthi Sankar, kasankar 
 *  * * 2022 Spring CSE101 PA6
 *  * * Arithmetic.cpp 
 *  * * Main file for PA6 
 *  * *********************************************************************************/

#include<iostream>
#include<string>
#include<fstream>
#include<stdexcept>
#include"BigInteger.h"
using namespace std;

int main(int argc, char * argv[]) {
    
   ifstream in;
   ofstream out;
   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(1);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(1);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(1);
   }

   return 0;

}
