//-----------------------------------------------------------------------------
// Lex.c
//
// 
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){

    int line_count;
    FILE *in, *out;
    char c; // to be used for counting the # of lines
    char line[MAX_LEN];

    // check command line for correct number of arguments
    if( argc != 3 ){
        fprintf(stderr, "Usage error: An incorrect number of arguments were given.\n");
        exit(1);
    }

    // open files for reading and writing 
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
    
    // get # of lines for allocating string array
    line_count = 0;
    while((c = fgetc(in))!=EOF) {
        if(c =='\n') {
            line_count++;
        }
    }
    
    // array of strings
    char **lines = malloc(MAX_LEN); 
    
    // read each line of input file into file_lines
    line_count = 0;
    while(fgets(line, MAX_LEN, in) != NULL)  {
        lines[line_count] = malloc(MAX_LEN);
        strcpy(lines[line_count], line);
        line_count++;
    }

    free(lines);
    // close files 
    fclose(in);
    fclose(out);

    return(0);
}
