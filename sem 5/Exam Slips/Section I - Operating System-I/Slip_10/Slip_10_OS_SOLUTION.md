# Slip 10 — Operating System-I Solution Guide

## Question 1: Round Robin (RR) CPU Scheduling [15 Marks]

### Problem Statement
Write program to simulate Round Robin (RR) CPU scheduling. Arrival time, burst time, time quantum input. Output Gantt chart, TAT, WT, avg TAT & WT.

### Concept & Algorithm
1. RR allocates a fixed time quantum to each ready process in circular order.
2. Preempts processes that do not complete within the quantum and returns them to the ready queue.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_10_Q1 Slip_10_Q1.c
./Slip_10_Q1
```

### Sample Output
```text
--- Gantt Chart ---
 | P1 | P2 | P3 | P2 | P3 | P3 |
Total Time: 18

PID     AT      1st BT  Next BT CT      TAT     WT
P1      0       3       4       5       5       2
P2      0       6       8       12      12      6
P3      0       9       1       18      18      9

Average Turnaround Time: 11.67
Average Waiting Time: 5.67
```

---

## Question 2: LOOK Disk Scheduling Simulation [15 Marks]

### Problem Statement
Write a simulation program for disk scheduling using LOOK algorithm. Request: 86, 147, 91, 177, 45, 12, 130; Start Head: 60; Direction: Right.

### Concept & Algorithm
1. LOOK algorithm scans in the current direction until reaching the furthest requested cylinder, then reverses immediately without traveling to the physical end of the disk.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_10_Q2 Slip_10_Q2.c
./Slip_10_Q2
```

### Sample Output
```text
Order of Request Service:
60 -> 86 -> 91 -> 130 -> 147 -> 177 -> 45 -> 12

Total Head Movements: 282 cylinders
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. How does time quantum affect Round Robin performance?
**Answer:** If time quantum is very large, RR degenerates to FCFS. If it is very small, excessive context switching overhead degrades system performance.

### Q2. What is context switching?
**Answer:** Context switching is the process of saving the execution state of the currently running process and restoring the state of the next scheduled process.

### Q3. Why is LOOK preferred over SCAN?
**Answer:** LOOK avoids unnecessary head travel to disk boundaries (cylinder 0 or max) when there are no requests pending there.

### Q4. What is response time in CPU scheduling?
**Answer:** Response time is the duration from the submission of a request/process until the first response is produced.

### Q5. Is Round Robin preemptive or non-preemptive?
**Answer:** Round Robin is strictly preemptive because timer interrupts preempt processes when their quantum expires.
