# Assignment 7: The Great Firewall of Santa Cruz: Bloom Filters, Linked Lists, Binary Trees and Hash Tables

This program is used to parse input from a user and determining whether what they say is a violation of
law or not and how they should be punished. In this program, I make use of bit vectors, bloom filters,
binary search trees, hash tables, and also matching words with the use of a regex expression. The program
runs depending on a combination of command line options, and output depends on what words the user
inputs or "says" after running the program.

## Building

Build the program with 
```
$ make
```
or 
```
$ make all
```
or 
```
$ make banhammer
```
## Running

Run the program with:
```
$ ./banhammer [-hs] [-t size] [-f size]
```

## Command Line Options

Banhammer Options:\
  -h           Program usage and help.\
  -s           Print program statistics.\
  -t size      Specify hash table size (default: 2^16).\
  -f size      Specify Bloom filter size (default: 2^20).\

## Errors

No errors resulting from running scan-build.\

