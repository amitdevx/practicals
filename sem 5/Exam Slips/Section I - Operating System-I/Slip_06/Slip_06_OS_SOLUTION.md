# Slip 06 — Operating System-I Solution Guide

## Question 1: Sequential File Allocation Simulation [15 Marks]

### Problem Statement
Write a program to simulate Sequential (Contiguous) file allocation method. Assume disk with n blocks. Randomly mark allocated blocks, maintain free list, menu: Show Bit Vector, Create New File, Show Directory, Exit.

### Concept & Algorithm
1. In contiguous allocation, each file occupies a set of consecutive blocks on disk.
2. Fast access since disk head movement is minimized.
3. Suffer from external fragmentation.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_06_Q1 Slip_06_Q1.c
./Slip_06_Q1
```

### Sample Output
```text
=== SEQUENTIAL (CONTIGUOUS) FILE ALLOCATION MENU ===
1. Show Bit Vector
2. Create New File
3. Show Directory
4. Exit
Enter your choice (1-4): 2
Enter file name: data.bin
Enter number of contiguous blocks required: 4
[+] File 'data.bin' allocated sequentially from block 3 to 6.
```

---

## Question 2: C-SCAN Disk Scheduling Simulation [15 Marks]

### Problem Statement
Write a simulation program for disk scheduling using C-SCAN algorithm. Request: 82, 170, 43, 140, 24, 16, 190, 65; Start Head: 50; Direction: Left.

### Concept & Algorithm
1. C-SCAN (Circular SCAN) provides a more uniform wait time.
2. The head moves in one direction servicing requests until it reaches the edge, then returns immediately to the opposite edge without servicing requests on the return trip.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_06_Q2 Slip_06_Q2.c
./Slip_06_Q2
```

### Sample Output
```text
Order of Request Service:
50 -> 43 -> 24 -> 16 -> 0 -> 199 -> 190 -> 170 -> 140 -> 82 -> 65

Total Head Movements: 383 cylinders
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is contiguous file allocation?
**Answer:** Each file occupies a sequence of contiguous physical disk blocks.

### Q2. What is external fragmentation in contiguous allocation?
**Answer:** Free disk space is broken into small pieces over time, so large files cannot be allocated even if total free space is sufficient.

### Q3. Why does C-SCAN provide more uniform wait times than SCAN?
**Answer:** Because in regular SCAN, cylinders near the middle get serviced twice per cycle while edge cylinders wait longer. C-SCAN treats cylinders circularly, giving equal waiting distribution.

### Q4. What is cylinder in a hard disk?
**Answer:** A cylinder is the collection of all tracks across all platters located at the same radial distance from the spindle center.

### Q5. What is disk bandwidth?
**Answer:** Disk bandwidth is the total number of bytes transferred divided by the total time between the first request service and the completion of the last transfer.
