Hun Jae Lee (hxl224)
EECS338 Homework 6
Due 161026 Wed

---

## How to run:

- `make` to compile all files
- `make q1` to run Peterson’s solution and multithreading design.
- `make q2` to run Peterson’s solution and fork with shared memory design.
- `make q3` to run semaphore and multithreading design
- `make q4` to run semaphore and multithreading design
- `make clean` to clean up the output files

## Discussion

### 1. Program output for Peterson’s solution and multithreading design (Problem #1)

```
$ ./q1.o
parent counter:	100000000
child counter:	-100000000
global counter:	0
```

When the thread is generated, the signal is given to the child. The child subtracts 10^8 from the `global_counter` which results in -10^8. Then when the signal is given to the parent upon the child thread's termination, 10^8 is added back to `global_counter` which finally results in zero.

### 2. Program output for Peterson’s solution and fork with shared memory design (Problem #2)

```
$ ./q2.o
parent counter:	100000000
child counter:	-100000000
global counter:	0
```

The result was the same. This time the parent counted up first then the child counted down.





### Notes:

- File naming convention:
   1. `q1.c, q2.c, q3.c, q4.c` source code, each number corresponding to the question number in the assignment.
   2. `makefile` the makefile
   3. `README.md` what you're reading right now
   4. `shubert.c` the Shubert function, given with the assignment; modified into dependency