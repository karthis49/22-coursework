# Assignment 3 - Sorting: Putting your affairs in order

This program is an implementation of four different sorts: insertion, quick, heap, and
shell sort. This program uses a struct to track the moves and compares each sort is 
doing, allowing us to analyze the effectiveness of each of the sorts at the end.

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

Run the program with:

```
$ ./sorting -aeisqr:n:p:h
```

## Command Line Options

-h:             displays program help.\
-a:             enable all sorts.\
-e:             enable Heap Sort.\
-i:             enable Insertion Sort.\
-s:             enable Shell Sort.\
-q:             enable Quick Sort.\
-n length:      specify number of array elements (default: 100).\
-p elements:    specify number of elements to print (default: 100).\
-r seed:        specify random seed (default: 13371453).

