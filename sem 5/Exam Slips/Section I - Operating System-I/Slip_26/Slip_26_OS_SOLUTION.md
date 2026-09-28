# Slip 26 — Operating System-I Solution Guide

## Question 1: Preemptive Priority CPU Scheduling [15 Marks]

### Problem Statement
Write program to simulate Preemptive Priority scheduling. Input arrival time, burst time, priority. Output Gantt chart, TAT, WT, avg TAT & WT.

### Concept & Algorithm
1. Preempts current process if higher priority job arrives.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_26_Q1 Slip_26_Q1.c
./Slip_26_Q1
```

### Sample Output
```text
Average Turnaround Time: 10.00
Average Waiting Time: 5.00
```

---

## Question 2: FIFO Page Replacement Simulation [15 Marks]

### Problem Statement
Write simulation program for demand paging and show page scheduling and total page faults using FIFO. String: 3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6.

### Concept & Algorithm
1. FIFO page replacement algorithm simulation.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_26_Q2 Slip_26_Q2.c
./Slip_26_Q2
```

### Sample Output
```text
Total Page Faults: 13
Total Hits: 2
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. Explain the term 'Page Fault Frequency'.
**Answer:** The rate at which page faults occur in a process; high PFF indicates the process needs more frames, low PFF indicates it has too many.

### Q2. What is working set model in memory management?
**Answer:** The working set model is based on locality and states that a process can execute efficiently only if its working set of pages is in memory.

### Q3. What is starvation in Priority scheduling?
**Answer:** Low priority processes may never execute if high priority processes keep arriving.

### Q4. Why does Belady's anomaly occur in FIFO?
**Answer:** Because FIFO does not take recency or frequency of access into account, dropping pages that may still be frequently referenced.

### Q5. What is page hit ratio?
**Answer:** Hit Ratio = (Total References - Page Faults) / Total References.
