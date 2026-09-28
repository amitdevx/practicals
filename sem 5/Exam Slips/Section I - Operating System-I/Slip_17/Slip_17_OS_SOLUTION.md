# Slip 17 — Operating System-I Solution Guide

## Question 1: Non-preemptive SJF CPU Scheduling [15 Marks]

### Problem Statement
Write program to simulate Non-preemptive Shortest Job First (SJF) scheduling. Arrival time and burst time input. Output Gantt chart, TAT, WT, avg TAT & WT.

### Concept & Algorithm
1. Non-preemptive SJF selects the available job with shortest burst time.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_17_Q1 Slip_17_Q1.c
./Slip_17_Q1
```

### Sample Output
```text
Average Turnaround Time: 6.33
Average Waiting Time: 2.33
```

---

## Question 2: Sequential File Allocation Simulation [15 Marks]

### Problem Statement
Write program to simulate Sequential (Contiguous) file allocation. Assume disk with n blocks. Randomly mark allocated, maintain free list, menu: Show Bit Vector, Create New File, Show Directory, Exit.

### Concept & Algorithm
1. Finds contiguous free blocks for file allocation.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_17_Q2 Slip_17_Q2.c
./Slip_17_Q2
```

### Sample Output
```text
[+] File 'test.txt' allocated sequentially from block 4 to 7.
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the primary advantage of sequential file allocation?
**Answer:** It provides the best sequential read/write performance because blocks are stored contiguously on disk.

### Q2. What is the difference between turnaround time and response time?
**Answer:** Turnaround time is the time from arrival to termination. Response time is the time from arrival to the first CPU execution.

### Q3. How can free disk space be tracked?
**Answer:** Using Bit vectors, Linked free lists, Grouping, or Counting.

### Q4. What causes external fragmentation in disk allocation?
**Answer:** Repeated creation and deletion of files leaves small scattered free blocks that cannot satisfy contiguous block requests.

### Q5. What is CPU utilization?
**Answer:** The percentage of time that the CPU is busy executing user or system processes.
