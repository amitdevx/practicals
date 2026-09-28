# Slip 27 — Operating System-I Solution Guide

## Question 1: SSTF Disk Scheduling Simulation [15 Marks]

### Problem Statement
Write simulation program for disk scheduling using SSTF algorithm. Request: 30, 10, 60, 95, 120, 150, 175; Start Head: 50.

### Concept & Algorithm
1. Greedily selects the nearest pending request to minimize head movement.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_27_Q1 Slip_27_Q1.c
./Slip_27_Q1
```

### Sample Output
```text
Order of Request Service:
50 -> 60 -> 30 -> 10 -> 95 -> 120 -> 150 -> 175
Total Head Movements: 250 cylinders
```

---

## Question 2: LRU Page Replacement (Counter Method) [15 Marks]

### Problem Statement
Write simulation program to implement demand paging using LRU counter method. String: 3,5,7,2,5,1,2,3,1,3,5,3,1,6,2.

### Concept & Algorithm
1. Discards least recently accessed page based on timestamp counter.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_27_Q2 Slip_27_Q2.c
./Slip_27_Q2
```

### Sample Output
```text
Total Page Faults: 9
Total Hits: 6
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. Why does SSTF perform better than FCFS?
**Answer:** Because it prioritizes requests that are closest to the current head position, reducing total mechanical arm travel distance.

### Q2. What is the primary risk of SSTF?
**Answer:** Starvation for requests on outer tracks if requests near the current position arrive continually.

### Q3. What is a page table?
**Answer:** A data structure maintained by the OS for each process that maps virtual page numbers to physical page frame numbers.

### Q4. What is TLB (Translation Lookaside Buffer)?
**Answer:** A high-speed associative hardware cache that stores recent virtual-to-physical address mappings to speed up translation.

### Q5. What is inverted page table?
**Answer:** A page table structure where there is only one entry per physical frame in memory, rather than one entry per virtual page of every process.
