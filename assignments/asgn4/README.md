# Assignment 4: The Perambulations of Denver Long

The function makes use of three ADTS: Graph, Stack, and Path, in order to 
complete a depth-first search. This DFS recursively will find the shortest 
Hamiltonian path through a number of given vertices.
 
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
$ ./tsp -vui:o:h 
```
  
## Command Line Options
 
-u:             Use undirected graph.\
-v:             Enable verbose printing.\
-h:             Program usage and help.\
-i infile:      Input containing graph (default: stdin).\
-o outfile:     Output of computed path (default: stdout).

