# Slip 03 — Operating System-I Solution Guide

## Question 1: Banker's Deadlock Avoidance Algorithm [15 Marks]

### Problem Statement
Write a C program to simulate Banker’s algorithm for deadlock avoidance. Check safety and test if request from P1 (1, 0, 2) can be granted.

### Concept & Algorithm
1. Need = Max - Allocation.
2. System is in safe state if a sequence of processes exists where each process can satisfy its maximum demand using available plus released resources.
3. Resource Request Algorithm tests safety before granting requests.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_03_Q1 Slip_03_Q1.c
./Slip_03_Q1
```

### Sample Output
```text
Process Allocation     Max             Need
P0      0 1 0           7 5 3           7 4 3 
P1      2 0 0           3 2 2           1 2 2 
P2      3 0 2           9 0 2           6 0 0 
P3      2 1 1           2 2 2           0 1 1 
P4      0 0 2           4 3 3           4 3 1 

Available Resources: 3 3 2 
[+] The system is currently in a SAFE state.
Safe Sequence: P1 -> P3 -> P4 -> P0 -> P2

Checking Request from P1: ( 1 0 2 )
[+] Request can be granted immediately! System remains safe.
```

---

## Question 2: SSTF Disk Scheduling Simulation [15 Marks]

### Problem Statement
Write a simulation program for disk scheduling using SSTF algorithm. Request: 30, 10, 60, 95, 120, 150, 175; Start Head: 50.

### Concept & Algorithm
1. SSTF (Shortest Seek Time First) chooses the pending request with the minimum seek distance from the current head position.
2. Reduces average seek time compared to FCFS, but may lead to starvation of distant requests.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_03_Q2 Slip_03_Q2.c
./Slip_03_Q2
```

### Sample Output
```text
Order of Request Service:
50 -> 60 -> 30 -> 10 -> 95 -> 120 -> 150 -> 175

Total Head Movements: 250 cylinders
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What are the 4 necessary conditions for Deadlock?
**Answer:** Mutual Exclusion, Hold and Wait, No Preemption, and Circular Wait.

### Q2. What is the difference between Deadlock Prevention and Deadlock Avoidance?
**Answer:** Prevention eliminates at least one of the 4 deadlock conditions statically. Avoidance dynamically monitors resource allocation to ensure the system never enters an unsafe state.

### Q3. What is SSTF disk scheduling?
**Answer:** Shortest Seek Time First services the request closest to the current head position to minimize head movement.

### Q4. Can SSTF cause starvation?
**Answer:** Yes, continuous arrival of nearby requests can cause distant cylinder requests to starve indefinitely.

### Q5. What is safe state in Banker's algorithm?
**Answer:** A state is safe if the system can allocate resources to each process in some order without encountering a deadlock.
