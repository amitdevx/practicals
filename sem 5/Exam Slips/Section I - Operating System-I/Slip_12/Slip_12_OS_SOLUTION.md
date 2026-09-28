# Slip 12 — Operating System-I Solution Guide

## Question 1: FCFS CPU Scheduling Simulation [15 Marks]

### Problem Statement
Write program to simulate FCFS CPU scheduling. Input arrival time and first CPU-burst. Generate next burst randomly. Output Gantt chart, TAT, WT, avg TAT & WT.

### Concept & Algorithm
1. First-Come First-Served schedules processes strictly in arrival order.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_12_Q1 Slip_12_Q1.c
./Slip_12_Q1
```

### Sample Output
```text
--- Gantt Chart ---
 |  P1  |  P2  |  P3  |
Average Turnaround Time: 7.00
Average Waiting Time: 3.33
```

---

## Question 2: Fork System Call with Bubble Sort and Insertion Sort [15 Marks]

### Problem Statement
Implement C program to accept n integers. Main forks child. Parent sorts using bubble sort and waits; Child sorts using insertion sort.

### Concept & Algorithm
1. fork() creates concurrent processes.
2. Child process executes insertion sort on array.
3. Parent calls wait() and then executes bubble sort.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_12_Q2 Slip_12_Q2.c
./Slip_12_Q2
```

### Sample Output
```text
[Child PID: 12345] Sorting using Insertion Sort...
[Child] Sorted Array: 3 6 9 12 15 

[Parent PID: 12344] Child finished. Sorting using Bubble Sort...
[Parent] Sorted Array: 3 6 9 12 15
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What does fork() return in parent and child?
**Answer:** It returns 0 to the child process and the child's PID (>0) to the parent process; returns -1 on error.

### Q2. What is the Convoy Effect in FCFS?
**Answer:** The Convoy Effect occurs when several short CPU-bound processes are delayed behind one long CPU-bound process, resulting in poor CPU and device utilization.

### Q3. Why is wait() system call important after fork()?
**Answer:** wait() suspends the parent process until one of its children terminates, collecting the exit status and preventing the creation of a zombie process.

### Q4. What is the time complexity of Bubble Sort and Insertion Sort?
**Answer:** Both have worst-case and average-case time complexity of O(n^2), with best-case O(n) for already sorted arrays.

### Q5. Are memory spaces shared between parent and child after fork()?
**Answer:** No, fork creates a separate copy of the address space using copy-on-write (COW).
