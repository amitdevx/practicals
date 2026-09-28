# Slip 22 — Operating System-I Solution Guide

## Question 1: Linked File Allocation Simulation [15 Marks]

### Problem Statement
Write a program to simulate Linked file allocation method. Assume disk with n blocks. Randomly mark allocated, maintain free list, menu: Show Bit Vector, Create New File, Show Directory, Exit.

### Concept & Algorithm
1. Simulates linked list disk blocks allocation.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_22_Q1 Slip_22_Q1.c
./Slip_22_Q1
```

### Sample Output
```text
[+] File 'project.c' created successfully using Linked Allocation.
```

---

## Question 2: Non-preemptive Priority CPU Scheduling [15 Marks]

### Problem Statement
Write program to simulate Non-preemptive Priority scheduling. Input arrival time, burst time, priority. Output Gantt chart, TAT, WT, avg TAT & WT.

### Concept & Algorithm
1. Dispatches the highest priority ready process non-preemptively.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_22_Q2 Slip_22_Q2.c
./Slip_22_Q2
```

### Sample Output
```text
--- Gantt Chart ---
 |  P1  |  P3  |  P2  |
Average Turnaround Time: 8.00
Average Waiting Time: 4.00
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. Why does linked allocation not have external fragmentation?
**Answer:** Because any free block anywhere on disk can satisfy a request for the next block of the file.

### Q2. What is the primary drawback of Non-preemptive Priority scheduling?
**Answer:** Starvation of low-priority processes if high-priority processes keep arriving.

### Q3. How does aging solve starvation?
**Answer:** Aging gradually increases the priority of processes that wait in the system for a long time.

### Q4. What is FAT (File Allocation Table)?
**Answer:** FAT is an implementation of linked allocation where all block pointers are cached together in an array at the beginning of the volume.

### Q5. What is the difference between preemptive and non-preemptive priority?
**Answer:** Preemptive interrupts the running process when a higher-priority process arrives; non-preemptive lets the running process complete its burst.
