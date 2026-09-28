# Slip 20 — Operating System-I Solution Guide

## Question 1: LOOK Disk Scheduling Simulation [15 Marks]

### Problem Statement
Write simulation program for disk scheduling using LOOK algorithm. Request: 86, 147, 91, 177, 45, 12, 130; Start Head: 60; Direction: Right.

### Concept & Algorithm
1. Scans in current direction to farthest request, then reverses.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_20_Q1 Slip_20_Q1.c
./Slip_20_Q1
```

### Sample Output
```text
Order of Request Service:
60 -> 86 -> 91 -> 130 -> 147 -> 177 -> 45 -> 12
Total Head Movements: 282 cylinders
```

---

## Question 2: LRU Page Replacement (Counter Method) [15 Marks]

### Problem Statement
Write simulation program for demand paging using LRU (counter method). String: 3,5,7,2,5,1,2,3,1,3,5,3,1,6,2.

### Concept & Algorithm
1. Replaces least recently used frame based on timestamp counter.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_20_Q2 Slip_20_Q2.c
./Slip_20_Q2
```

### Sample Output
```text
Total Page Faults: 9
Total Hits: 6
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. Why is LOOK disk scheduling an improvement over SCAN?
**Answer:** Because it does not travel to cylinder 0 or the maximum disk cylinder unless there is an actual request at those extremes.

### Q2. What hardware support is required for demand paging?
**Answer:** A page table with valid/invalid bits and secondary storage (swap disk) to hold pages not in RAM.

### Q3. What is the cost of a page fault?
**Answer:** Servicing a page fault involves an OS trap, disk read I/O (millisecond delay), frame allocation, and process restart.

### Q4. How does LRU stack implementation work?
**Answer:** A doubly linked list of page numbers is maintained; when a page is referenced, it is moved to the top of the stack. The bottom of the stack is always the LRU page.

### Q5. What is cylinder skew in modern hard drives?
**Answer:** Cylinder skew offsets the starting sector of each track to account for head switch time when moving between adjacent cylinders.
