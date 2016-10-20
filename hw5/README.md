Hun Jae Lee (hxl224)
EECS338 Homework 5
Due 161019 Wed

---

## How to run:

- `make` to compile all files
- `make q1` to run OpenMP directives with `reduction (min: variable)` clause to find the minimum value of the Shubert function.
- `make q2` to run the above program, but without the `reduction` clause.
- `make q3` to run multithread design for global counting (I know you will be running this multiple times)
- `make q4` to run fork design for global counting (I know you will be running this multiple times)
- `make clean` to clean up the output files

## Discussion

### 1. Program output for multithreaded counting (Problem #3)

The multithreaded program with parent counter and child counter working with global counter resulted as following, with 10^8 iterations:

- First run:

```
$ ./q3.o
child_counter:	-100000000
parent_counter:	100000000
global_counter:	-1882296
```

- Second run:

```
$ ./q3.o
child_counter:	-100000000
parent_counter:	100000000
global_counter:	1560250
```

The positive error and negative error, as demonstrated in the assignment, was observed.

### 2. Program output for forked counting (Problem #4)

The fork-design approach to the above problem resulted in the following output, with 10^8 iterations:

- First run:

```
$ ./q4.o
parent counter:	100000000
child counter:	-100000000
global counter:	-17782049
```

- Second run:

```
$ ./q4.o
child counter:	-100000000
parent counter:	100000000
global counter:	2991875
```

Both positive and negative errors were observed. It must be noted that the order of the output is different because either child or parent could be done counting first (while the multithread design has consistent output order).

### Notes:

- File naming convention:
   1. `q1.c, q2.c, q3.c, q4.c` source code, each number corresponding to the question number in the assignment.
   2. `makefile` the makefile
   3. `README.md` what you're reading right now
   4. `shubert.c` the Shubert function, given with the assignment; modified into dependency