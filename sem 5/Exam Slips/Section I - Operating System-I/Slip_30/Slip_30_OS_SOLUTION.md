# Slip 30 — Operating System-I Solution Guide

## Question 1: Round Robin (RR) CPU Scheduling [15 Marks]

### Problem Statement
Write program to simulate Round Robin (RR) CPU-scheduling. Arrival time and burst time input, time quantum. Output Gantt chart, TAT, WT, avg TAT & WT.

### Concept & Algorithm
1. Time-sharing scheduling algorithm with fixed time quantum.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_30_Q1 Slip_30_Q1.c
./Slip_30_Q1
```

### Sample Output
```text
--- Gantt Chart ---
 | P1 | P2 | P3 | P2 | P3 | P3 |
Average Turnaround Time: 11.67
Average Waiting Time: 5.67
```

---

## Question 2: MFU Page Replacement Simulation [15 Marks]

### Problem Statement
Write simulation program for demand paging using MFU page replacement algorithm. String: 2, 5, 2, 8, 5, 4, 1, 2, 3, 2, 6, 1, 2, 5, 9, 8; n frames.

### Concept & Algorithm
1. Replaces the page with the highest frequency count.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_30_Q2 Slip_30_Q2.c
./Slip_30_Q2
```

### Sample Output
```text
Step    Page    Frames          Status
-------------------------------------------------
1       2       [ 2 - - ]       PAGE FAULT
2       5       [ 2 5 - ]       PAGE FAULT
3       2       [ 2 5 - ]       HIT
...
Total Page Faults: 11
Total Hits: 5
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What happens in Round Robin if the time quantum is 1 millisecond?
**Answer:** Context switching overhead dominates CPU execution time, significantly reducing system throughput.

### Q2. Why does MFU replace the page with the largest count?
**Answer:** Based on the heuristic that the page with the highest count has been heavily utilized and is now finished with its burst.

### Q3. What is the optimal page replacement algorithm (OPT/MIN)?
**Answer:** The algorithm that replaces the page that will not be used for the longest period of time in the future (theoretical benchmark).

### Q4. What is starvation in CPU scheduling?
**Answer:** A condition where a ready-to-run process waits indefinitely for the CPU because other processes are continuously chosen ahead of it.

### Q5. How does Round Robin prevent starvation?
**Answer:** Every process in the ready queue is guaranteed a turn of CPU time within a bounded time interval (n-1)*q.
