# Assignment 4: Huffman Coding
 
This program contains both a Huffman encoder and decoder implemented using
the Huffman coding algorithm. It makes uses of ADTs (Node, Priority Queue, Code,
Stack) as well supplementary files IO and Huffman. The program will encode or 
decode input files as well as standard input and print to output files 
or standard output.
 
## Building
 
Build the program with:
```
$ make
```
or
```
$ make all
```
## Running

Run the program with:\
Note: input or output file must be specified after command line option
```
$ ./encode -vi:o:h
``` 
or
```
$ ./decode -vi:o:h
```

## Command Line Options

-v:             Print compression statistics.\
-h:             Program usage and help.\
-i infile:      Input file to (de)compress.\
-o outfile:     Output of (de)compressed data.
