Hun Jae Lee (hxl224)
EECS338 Homework 3
Due 160921 Wed

---

## How to run:

- `make` to compile
- `make q1` to run question 1 (then `make q2`, `make q3` for questions 2 and 3)
- `make clean` to clean up the output files

## Discussion

For question 2, I was able to observe the following (running on my computer, not `eecslinab3` server)

```
How many processes? 1
Process 1 (43004) started.
Process 1 (43004) total time was 3.398492 seconds. x = 1000000000.

How many processes? 2
Process 1 (43026) started.
Process 2 (43027) started.
Process 2 (43027) total time was 1.700001 seconds. x = 500000000.
Process 1 (43026) total time was 1.700816 seconds. x = 500000000.

How many processes? 3
Process 1 (43043) started.
Process 2 (43044) started.
Process 3 (43045) started.
Process 2 (43044) total time was 1.171473 seconds. x = 333333333.
Process 3 (43045) total time was 1.171794 seconds. x = 333333333.
Process 1 (43043) total time was 1.172506 seconds. x = 333333333.

How many processes? 4
Process 1 (43063) started.
Process 2 (43064) started.
Process 3 (43065) started.
Process 4 (43066) started.
Process 2 (43064) total time was 0.904792 seconds. x = 250000000.
Process 4 (43066) total time was 0.906261 seconds. x = 250000000.
Process 3 (43065) total time was 0.912646 seconds. x = 250000000.
Process 1 (43063) total time was 0.921757 seconds. x = 250000000.
```

I was able to find a significant increase in speed (= less time elapsed) as I increased the number of processes to compute (3.39s, 1.70s, 1.17s, 0.90s).

For 3 and 4 processes, I was able to observe that the processes were created in order; however, the processes did not report their elapsed time in a certain order (either created order or the reverse of it). I suspect that this is because each process prints out the result right after the computation is complete.

I have also tried 255 processes to stress test my computer; it took about 0.065s to compute, which is a very significant increase in speed as well.

### Notes:

- File naming convention:
  1. `q1.c`: Question #1
  2. `q2.c`: Question #2
  3. `q3.c`: Question #3


- Question 1:
  - Forking issue? Invalid command still forks a child (Noted by Chris in class)
  - When no command is entered and the return key pressed, it exits.
- Question 2:
  - Processes do not report their elapsed times in a certain order.
- Question 3:
  - Prints the process ID and some TA-friendly information.