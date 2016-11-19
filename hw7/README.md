Hun Jae Lee (hxl224)
EECS338 Homework 7
Due 161102 Wed

---

## How to run:

- `make` to compile all files
- `make q1` to run circular buffer without synchronization.
- `make q2` to run circular buffer with synchronization.
- `make clean` to clean up the output files

## Program Output & Discussion

Buffer size is 4 and input values were {10, 20, 30, ..., 100}, produced one by one. The consumer marks the element in buffer as zero upon reading (consuming).

### 1. Program output for circular buffer without synchronization

```
$ ./q1.o
90
100
70
80
0
0
0
0
0
0
```



### 2. Program output for circular buffer with synchronization

```
$ ./q2.o
10
20
30
40
50
60
70
80
90
100
```

The result was as expected: synchronized behavior.

## Notes

- File naming convention:
   1. `q1.c, q2.c` source code, each number corresponding to the question number in the assignment.
   2. `makefile` the makefile
   3. `README.md` what you're reading right now