Hun Jae Lee (hxl224)
EECS338 Homework 8
Due 161109 Wed

---

## How to run

- `make` to compile all files
- `make q1a` to run OpenMP incrementing/decrementing with `#pragma omp critical`.
- `make q1b` to run OpenMP incrementing/decrementing without `#pragma omp critical`.
- `make q2` to run reader/writer program with shared buffer.
- `make clean` to clean up the output files

## Program Outputs & Discussion

### Problem 1a: with `#pragma omp critical`

```
$ export OMP_NUM_THREADS=4
$ ./q1a.o
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
```

### Problem 1b: *without* `#pragma omp critical`

```
$ export OMP_NUM_THREADS=4
$ ./q1b.o
2 -18 0 0 0 -108 1 20 0 0 
28 -53 -92 0 0 0 0 0 72 0 
0 4 38 0 8 81 0 56 -62 -44 
50 -1 0 0 -93 0 0 -28 14 0 
0 0 -52 0 -20 0 89 -63 0 0 
-54 0 -13 4 11 0 10 -13 30 -7 
-15 -29 50 0 2 0 -28 -6 -27 -8 
-47 14 -1 0 3 17 24 2 0 14 
4 0 27 0 -15 29 0 0 -6 0 
0 0 0 -21 2 0 0 -19 0 0 
```

#### Discussion

As introduced during lecture, I was able to observe the discrepency between the results.

### Problem 2: Reader & Writer

```
$ ./q2.o
1080630080(2): 1st sentence
1078528832(1): 1st sentence
1078528832(1): 2nd sentence
1080630080(2): 2nd sentence
1080630080(2): 3rd sentence
1078528832(1): 3rd sentence
1078528832(1): 4th sentence
1080630080(2): 4th sentence
```

#### Discussion

I have also attached the child number to the thread id so that it is easier to see. The result is as expected.

## Notes

- File naming convention:
   1. `q1a.c`, `q1b.c`, `q2.c`: source code, each number corresponding to the question number in the assignment.
   2. `makefile`: the makefile
   3. `README.md`: what you are reading right now