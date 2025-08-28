[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/VB6kmSmS)
# Homework 5: QSort

Deadline: 09/29/2025

Late: 10/02/2025

## Goals 

This assignment asks you to write a program reads data from a file, sorts the data using *qsort*, and writes the sorted data to another file.


You will learn to
* Read unsorted data from files
* Write sorted data to another file
* Call the `qsort(...)` function
* Allocate and free memory dynamically
* Check memory errors using `valgrind`

## Background

### 1. Dynamic memory allocation

In this assignment, you will use `malloc(...)` to allocate memory dynamically.

`void* malloc(size_t size)` allocates the requested memory and returns a pointer to it,
**OR** returns NULL if the allocation fails.

You should always deallocate the memory with the `void free(void *ptr)` function when you are done using the memory.

For example, 

```
int* arr = (int*) malloc(10 * sizeof(int)); // allocates memory for 10 integers
free(arr); // releases the allocated memory
```

You will use the `valgrind` tool to debug memory errors, and detect memory leaks.
Check [here](http://cs.ecs.baylor.edu/~donahoo/tools/valgrind/messages.html) for the various types of errors that you may encounter.

For example, to use valgrind to check the program `hw5` for memory errors with input file `filename`, run the following command:

`valgrind --tool=memcheck --leak-check=yes ./hw5 filename`


### 2. QSort

QSort is a built-in function in C for sorting arrays based on quick sort algorithm.
In this assignment, you **do not** need to implement the qsort function.
Instead, you will need to read the [`qsort` function](https://linux.die.net/man/3/qsort)
and understand how to use it. The QSort algorithm is based on recusion.
You will learn the algorithm later when we discuss recursion in class.

To use qsort, you need to provide four arguments:

* the address of the first element
* the number of elements
* the size of each element
* the function for comparing elements


### 3. strcmp function

`strcmp()` function's signature is: `int strcmp(const char* s1, const char* s2)`. It takes two char arrays (i.e., strings) and compares them lexicographically. It returns a negative number if the first string is lexicographically smaller, 0 if the both strings are the equal, and a positive number if the second string is lexicographically smaller.

> Lexicographical ordering in this situation means the order of characters in the ASCII table.


## What do you need to do?

You need to modify only one file - `student.c` - and complete the following functions:
 * `bool StudentRead(char* filename, Student** stu, int* numelem)`
 * `bool StudentWrite(char* filename, Student* stu, int numelem)`
 * `void sortStudents(Student* stu, int numelem, int (*compar)(const void*, const void*))`
 * `int compareID(const void* p1, const void* p2)`
 * `int compareName(const void* p1, const void* p2)`
 * `bool areStudentsSorted(Student* stu, int numelem, int (*compar)(const void*, const void*))`

Read the comments for each of the functions to understand what you need to do.
For the two comparison functions (`compareID` and `compareName`), each of them has three steps:

* cast the type from `void *` to the proper type (it is a pointer). For example in `compareID`, you can use `const Student* st1 = (const Student*) p1;` to cast from pointer p1 (of type `const void*`) to type `const Student*` and assign its value to st1 (of type `const Student*`)
* retrieve the values from the pointer
* compare the values and return negative, zero, or positive numbers

To compare two IDs, you'll use the numeric difference.
To compare two names (strings), you'll use `strcmp()` function.


### Testing for memory leak

Note that in the Makefile provided to you, there is one target line for `testmemory`.
Running the Makefile with the target `testmemory` will check for memory errors using `valgrind` and display the output in the terminal.

```
make testmemory # Will display memory report in the terminal
``` 


### What to submit?

Please submit **ONLY** the `student.c` file to Gradescope.

### Test inputs

Four test cases have been provided. You can test individual testcases using `make test#` or the entire suite using `make testall`.