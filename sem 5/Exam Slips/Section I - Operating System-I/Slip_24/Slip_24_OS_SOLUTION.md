# Slip 24 — Operating System-I Solution Guide

## Question 1: Round Robin (RR) CPU Scheduling [15 Marks]

### Problem Statement
Write program to simulate Round Robin (RR) scheduling. Input arrival time, burst time, time quantum. Output Gantt chart, TAT, WT, avg TAT & WT.

### Concept & Algorithm
1. Preemptive scheduling based on fixed time quantum slice.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_24_Q1 Slip_24_Q1.c
./Slip_24_Q1
```

### Sample Output
```text
Average Turnaround Time: 11.67
Average Waiting Time: 5.67
```

---

## Question 2: Process Sorting and Binary Search with Fork [15 Marks]

### Problem Statement
Implement C program that accepts an integer array. Parent sorts array; child performs binary search.

### Concept & Algorithm
1. Parent sorts array and coordinates with child searching for target element.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_24_Q2 Slip_24_Q2.c
./Slip_24_Q2
```

### Sample Output
```text
[Parent] Sorted Array: 7 12 23 45 89 
[Child] Element 23 found at index 2!
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the time complexity of Round Robin scheduling?
**Answer:** O(1) per scheduling decision if implemented with a FIFO queue.

### Q2. What happens if time quantum in RR is too large?
**Answer:** Round Robin degrades into FCFS (First-Come, First-Served).

### Q3. What is binary search prerequisite?
**Answer:** The array must be strictly sorted in ascending or descending order.

### Q4. What is IPC?
**Answer:** Inter-Process Communication mechanisms (pipes, message queues, shared memory, sockets) that allow processes to exchange data.

### Q5. What is the state of a child process after fork before parent calls wait?
**Answer:** If the child finishes first, it enters the ZOMBIE state until the parent calls wait() or terminates.
