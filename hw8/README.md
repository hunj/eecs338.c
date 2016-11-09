Hun Jae Lee (hxl224)
EECS338 Homework 8
Due 161109 Wed

---

## How to run:

- `make` to compile all files
- `make q1` to run circular buffer without synchronization.
- `make q2` to run circular buffer with synchronization.
- `make clean` to clean up the output files

## Program Output & Discussion

### Problem 1a: with `#pragma omp critical`

#### First Run

```
$ ./q1a.o

```

#### Second Run

```
$ ./q1a.o

```

#### Third Run

```
$ ./q1a.o

```

As introduced during lecture, I was able to observe the discrepency between the results. The second run did yield what we are seeking for; however, we cannot assure that the program is consistent because the result kept varying.

### Problem 1b: without `#pragma omp critical`

#### First Run

```
$ ./q1a.o
```

#### Second Run

```
$ ./q1a.o
```

#### Third Run

```
$ ./q1a.o
```

### Problem 2: Reader & Writer

## Notes

- File naming convention:
   1. `q1.c`, `q2.c`: source code, each number corresponding to the question number in the assignment.
   2. `makefile`: the makefile
   3. `README.md`: what you're reading right now