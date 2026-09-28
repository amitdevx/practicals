# Slip 04 — Operating System-I Solution Guide

## Question 1: Banker's Algorithm Menu Driven Program [15 Marks]

### Problem Statement
Implement Menu driven Banker's algorithm for accepting Allocation, Max from user. Menu: Accept Available, Display Allocation/Max, Find Need and display, Display Available. Resources A:7, B:2, C:6.

### Concept & Algorithm
1. Need Matrix calculation: Need[i][j] = Max[i][j] - Allocation[i][j].
2. Tracks available resources and displays allocation state interactively.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_04_Q1 Slip_04_Q1.c
./Slip_04_Q1
```

### Sample Output
```text
=============================================
   BANKER'S ALGORITHM - MENU DRIVEN PROGRAM
=============================================
1. Accept Available
2. Display Allocation and Max
3. Display Contents of Need Matrix
4. Display Available
5. Exit
Enter your choice (1-5): 3

Need Matrix (Need = Max - Allocation):
Process Need (A B C)
P0      0 -1 0 
P1      1 2 2 
P2      -4 0 0 
P3      0 1 1 
P4      4 3 1
```

---

## Question 2: SCAN Disk Scheduling Simulation [15 Marks]

### Problem Statement
Write a simulation program for disk scheduling using SCAN algorithm. Request: 82, 170, 43, 140, 24, 16, 190, 65; Start Head: 50; Direction: Left.

### Concept & Algorithm
1. SCAN (Elevator algorithm) moves the head towards one end of the disk servicing requests, reaches the end (0), and reverses direction towards the other end.
2. Eliminates starvation seen in SSTF.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_04_Q2 Slip_04_Q2.c
./Slip_04_Q2
```

### Sample Output
```text
Order of Request Service:
50 -> 43 -> 24 -> 16 -> 0 -> 65 -> 82 -> 140 -> 170 -> 190

Total Head Movements: 240 cylinders
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. Why is the SCAN algorithm called the elevator algorithm?
**Answer:** Because it behaves like an elevator in a building: moving in one direction servicing requests until it reaches the boundary, then reversing direction.

### Q2. What is the difference between SCAN and LOOK?
**Answer:** SCAN goes all the way to the disk boundary (e.g. cylinder 0 or max) before reversing, whereas LOOK only goes as far as the last pending request in that direction before reversing.

### Q3. What does the Need matrix signify in Banker's algorithm?
**Answer:** It represents the remaining resources each process may still request before it finishes execution.

### Q4. What happens if a process requests more resources than its Max claim?
**Answer:** The operating system raises an error condition and rejects the request because the process exceeded its declared maximum claim.

### Q5. What is rotational latency in disk access?
**Answer:** Rotational latency is the time required for the desired disk sector to rotate under the read/write head.
