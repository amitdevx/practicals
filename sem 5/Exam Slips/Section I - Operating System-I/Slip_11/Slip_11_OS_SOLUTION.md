# Slip 11 — Operating System-I Solution Guide

## Question 1: Banker's Algorithm Deadlock Avoidance [15 Marks]

### Problem Statement
Write a C program to simulate Banker’s algorithm for Deadlock avoidance. Given Allocation, Max, Available. Display Need, check safety, test P1 request (1,0,2).

### Concept & Algorithm
1. Full safety algorithm implementation verifying safe state and testing resource request.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_11_Q1 Slip_11_Q1.c
./Slip_11_Q1
```

### Sample Output
```text
[+] The system is currently in a SAFE state.
Safe Sequence: P1 -> P3 -> P4 -> P0 -> P2
Checking Request from P1: ( 1 0 2 )
[+] Request can be granted immediately! System remains safe.
```

---

## Question 2: LRU Page Replacement Simulation [15 Marks]

### Problem Statement
Write simulation program for demand paging and show page scheduling and total page faults using LRU. String: 3, 5, 7, 2, 5, 1, 2, 3, 1, 3, 5, 3, 1, 6, 2; n frames.

### Concept & Algorithm
1. LRU replaces the page that has not been used for the longest period of time.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_11_Q2 Slip_11_Q2.c
./Slip_11_Q2
```

### Sample Output
```text
Total Page Faults: 9
Total Hits: 6
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the Banker's safety algorithm complexity?
**Answer:** The time complexity is O(m * n^2), where n is the number of processes and m is the number of resource types.

### Q2. What is the principle of locality of reference?
**Answer:** Programs tend to reuse data and instructions they have used recently (temporal locality) or that are close to those recently accessed (spatial locality).

### Q3. Why does LRU perform well in practice?
**Answer:** Because program execution exhibits strong temporal locality, recently used pages are likely to be accessed again soon.

### Q4. What is a dirty bit (modify bit) in paging?
**Answer:** A dirty bit indicates whether a page in memory has been modified since it was loaded from disk, avoiding unnecessary writes during page replacement.

### Q5. What is deadlock detection vs avoidance?
**Answer:** Deadlock avoidance prevents the system from entering an unsafe state dynamically. Deadlock detection allows deadlocks to occur, periodically checks for them, and initiates recovery.
