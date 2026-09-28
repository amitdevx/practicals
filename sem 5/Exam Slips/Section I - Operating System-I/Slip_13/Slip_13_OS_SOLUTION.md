# Slip 13 — Operating System-I Solution Guide

## Question 1: Non-preemptive SJF CPU Scheduling [15 Marks]

### Problem Statement
Write program to simulate Non-preemptive Shortest Job First (SJF) scheduling. Input arrival time and first burst. Output Gantt chart, TAT, WT, avg TAT & WT.

### Concept & Algorithm
1. Schedules process with smallest burst time among all currently arrived processes non-preemptively.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_13_Q1 Slip_13_Q1.c
./Slip_13_Q1
```

### Sample Output
```text
Average Turnaround Time: 6.33
Average Waiting Time: 2.33
```

---

## Question 2: LOOK Disk Scheduling Simulation [15 Marks]

### Problem Statement
Write a simulation program for disk scheduling using LOOK algorithm. Request: 86, 147, 91, 177, 45, 12, 130; Start Head: 60; Direction: Right.

### Concept & Algorithm
1. Scans towards higher cylinder numbers servicing requests until the highest, then reverses to service remaining requests.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_13_Q2 Slip_13_Q2.c
./Slip_13_Q2
```

### Sample Output
```text
Order of Request Service:
60 -> 86 -> 91 -> 130 -> 147 -> 177 -> 45 -> 12
Total Head Movements: 282 cylinders
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. Why does Non-preemptive SJF not switch running jobs?
**Answer:** Because in non-preemptive scheduling, once the CPU has been allocated to a process, the process keeps the CPU until it releases it either by terminating or by switching to waiting.

### Q2. What is the difference between LOOK and C-LOOK?
**Answer:** LOOK reverses direction and services requests on the way back; C-LOOK jumps straight to the lowest request without servicing on the return trip.

### Q3. What is throughput in CPU scheduling?
**Answer:** Throughput is the number of processes completed per unit time.

### Q4. How does disk scheduling improve hard drive lifespan?
**Answer:** By minimizing redundant mechanical arm movements, which reduces wear and tear on drive actuators.

### Q5. What is preemptive scheduling vs non-preemptive scheduling?
**Answer:** In preemptive scheduling, the OS can interrupt a running process to give the CPU to another higher-priority process. In non-preemptive scheduling, the process voluntarily yields the CPU.
