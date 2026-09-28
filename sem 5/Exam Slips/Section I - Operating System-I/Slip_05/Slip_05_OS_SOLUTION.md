# Slip 05 — Operating System-I Solution Guide

## Question 1: FIFO Page Replacement Simulation [15 Marks]

### Problem Statement
Write the simulation program for demand paging and show page scheduling and total page faults using FIFO. Reference string: 3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6; n frames.

### Concept & Algorithm
1. FIFO (First-In, First-Out) replaces the oldest page in memory when a page fault occurs and all frames are full.
2. Maintained using a circular queue or index pointer.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_05_Q1 Slip_05_Q1.c
./Slip_05_Q1
```

### Sample Output
```text
Step    Page    Frames          Status
-------------------------------------------------
1       3       [ 3 - - ]       PAGE FAULT
2       4       [ 3 4 - ]       PAGE FAULT
3       5       [ 3 4 5 ]       PAGE FAULT
4       6       [ 6 4 5 ]       PAGE FAULT
...
Total Page Faults: 13
Total Hits: 2
```

---

## Question 2: Banker's Resource Allocation Representation [15 Marks]

### Problem Statement
Consider a system with ‘n’ processes and ‘m’ resource types. Accept number of instances for every resource, Allocation, and Max matrix. Calculate and display Need matrix and Available vector.

### Concept & Algorithm
1. Accepts dynamic dimensions n and m.
2. Computes Available = Total - Sum(Allocated for each resource).
3. Computes Need = Max - Allocation.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_05_Q2 Slip_05_Q2.c
./Slip_05_Q2
```

### Sample Output
```text
Enter number of processes: 3
Enter number of resource types: 3
Enter total instances: 10 10 10
--- Need Matrix ---
P0: 2 1 3 
P1: 1 2 0 
P2: 0 1 2 
--- Available Vector ---
4 3 5
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is demand paging?
**Answer:** Demand paging is a paging system where pages are loaded into memory only when they are referenced (demanded) during execution.

### Q2. What is a page fault?
**Answer:** A page fault is an interrupt raised by hardware when a running program accesses a memory page that is not currently loaded in physical RAM.

### Q3. What is Belady's Anomaly?
**Answer:** Belady's Anomaly is a phenomenon where increasing the number of page frames results in an increase in the number of page faults for certain page replacement algorithms (such as FIFO).

### Q4. Does LRU suffer from Belady's Anomaly?
**Answer:** No, LRU is a stack algorithm and does not suffer from Belady's Anomaly.

### Q5. What is thrashing?
**Answer:** Thrashing occurs when a computer spends more time swapping pages in and out of memory than executing actual instructions.
