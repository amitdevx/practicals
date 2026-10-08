# Slip 21 — Operating System-I Solution Guide

## Question 1: MFU Page Replacement Simulation [15 Marks]

### Problem Statement
Write simulation program for demand paging using MFU. Reference string: 8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2. Assume memory of n frames.

### Concept & Algorithm
1. Most Frequently Used (MFU) page replacement algorithm replaces the page with the highest reference count in memory.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_21_Q1 Slip_21_Q1.c
./Slip_21_Q1
```

### Sample Output
```text
Total Page Faults: 10
Total Hits: 5
```

---

## Question 2: Demonstration of nice() System Call [15 Marks]

### Problem Statement
Write a program that demonstrates the use of nice() system call. After child process started using fork(), assign higher priority using nice().

### Concept & Algorithm
1. Changes scheduling priority using nice(-5).

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_21_Q2 Slip_21_Q2.c
./Slip_21_Q2
```

### Sample Output
```text
[Child] After nice(-5), Updated Nice Value: -1
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the range of nice values in POSIX systems?
**Answer:** -20 (highest scheduling priority) to +19 (lowest scheduling priority).

### Q2. What is Belady's Anomaly and in which algorithm is it observed?
**Answer:** Belady's Anomaly is when more frames cause more page faults. It is observed in FIFO page replacement.

### Q3. What is a stack algorithm in page replacement?
**Answer:** An algorithm for which the set of pages in memory for n frames is always a subset of the pages for n+1 frames (e.g. LRU, Optimal).

### Q4. What is the function of the swap space?
**Answer:** Swap space on secondary storage holds memory pages that are inactive, freeing physical RAM for active pages.

### Q5. How does a process terminate in Unix?
**Answer:** By calling exit(), _exit(), or receiving an unhandled terminating signal.
