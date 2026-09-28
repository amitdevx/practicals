# Slip 29 — Operating System-I Solution Guide

## Question 1: Process Sorting and Binary Search with Fork [15 Marks]

### Problem Statement
Implement C program that accepts an integer array. Parent sorts array; child performs binary search.

### Concept & Algorithm
1. Multiprocess coordination with sorting in parent and binary search in child.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_29_Q1 Slip_29_Q1.c
./Slip_29_Q1
```

### Sample Output
```text
[Parent] Sorted Array: 7 12 23 45 89 
[Child] Element 23 found at index 2!
```

---

## Question 2: FCFS CPU Scheduling Simulation [15 Marks]

### Problem Statement
Write program to simulate FCFS CPU-scheduling. Arrival time and burst time input. Output Gantt chart, TAT, WT, avg TAT & WT.

### Concept & Algorithm
1. Non-preemptive FCFS CPU scheduling.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_29_Q2 Slip_29_Q2.c
./Slip_29_Q2
```

### Sample Output
```text
--- Gantt Chart ---
 |  P1  |  P2  |  P3  |
Average Turnaround Time: 7.00
Average Waiting Time: 3.33
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is Gantt chart?
**Answer:** A Gantt chart is a horizontal bar chart illustrating the scheduling timeline of processes executed on the CPU.

### Q2. What is the formula for Turnaround Time?
**Answer:** TAT = Completion Time - Arrival Time.

### Q3. What is the formula for Waiting Time?
**Answer:** WT = Turnaround Time - Burst Time.

### Q4. What is binary search time complexity in worst and best cases?
**Answer:** Best case: O(1) (found at mid). Worst/Average case: O(log n).

### Q5. What happens to child process when parent terminates without wait()?
**Answer:** The child becomes an orphan process and is adopted by init/systemd (PID 1).
