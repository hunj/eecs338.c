Hun Jae Lee (hxl224)
EECS338 Homework 4
Due 161003 Wed

---

## How to run:

- `make` to compile all files
- `make pipe` to run fork with pipe comms. design
- `make socket` to run both server and client with socket comms. design
- `make threads` to run multithread design
- `make clean` to clean up the output files

## Discussion

### 1. Result/output of each design

All three programs reported `-185.301878` as global minimum with given `-2 ≤ x1, x2 ≤ +2` with step `x += 0.05`.

1. `fork()` with pipe:
   ```
   $ ./pipe.o
   Parent:  -64.679992
   Child:   -185.301878
   MIN:  -185.301878
   ```

2. Server & Client:

   ```
   $ ./server.o & ./client.o
   <CLIENT> shubert result is -185.301878
   <SERVER> shubert result is -64.679992.
   <SERVER> Global minimum is -185.301878.
   ```

3. Multithread:
   ```
   $ ./threads.o
   minimum: -185.301878
   ```

### 2. What use?

I would use **server-client design** for parallel programming application, especially when **we have cloud platforms these days**; however, in my program I have specified the range INSIDE the client program which is not so viable. I would have an advanced structure where there would be more communication between server and client(s) in order to distribute equal amount of work.

## Notes:

- File naming convention:
   1. `fork_pipe.c` fork with pipe comms. design
   2. `server.c` and `client.c` fork with socket comms. design
   3. `multithreading.c` multithread design
   4. `makefile` the makefile
   5. `README.md` what you're looking at
   6. `shubert.c` the Shubert function given with the assignment; modified into dependency