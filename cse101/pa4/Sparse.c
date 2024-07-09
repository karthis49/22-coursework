/********************************************************************************* 
 *  * * Karthi Sankar, kasankar 
 *  * * 2022 Spring CSE101 PA4
 *  * * Sparse.c 
 *  * * Main file for PA4
 *  * *********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"
#include "Matrix.h"

int main(int argc, char* argv[]){

    FILE *in, *out;

     //check command line for correct number of arguments
     if( argc != 3 ){
         fprintf(stderr, "Usage error: An incorrect number of arguments were given.\n");
         exit(1);
     }
     
     //open files for reading and writing 
     in = fopen(argv[1], "r");
     if( in==NULL ){
         printf("Unable to open file %s for reading\n", argv[1]);
         exit(1);
     }

    out = fopen(argv[2], "w");
    if( out==NULL ){ 
         printf("Unable to open file %s for writing\n", argv[2]);
         exit(1);
    }




    fclose(in);
    fclose(out);
    return 0;
}