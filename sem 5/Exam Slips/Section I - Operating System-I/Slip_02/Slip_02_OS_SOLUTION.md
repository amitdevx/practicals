# Slip 02 — Operating System-I Solution Guide

## Question 1: Linked File Allocation Simulation [15 Marks]

### Problem Statement
Write a program to simulate Linked file allocation method. Assume disk with ‘n’ number of blocks. Give value of ‘n’ as input. Randomly mark some block as allocated and accordingly maintain the list of free blocks. Write menu driven program with options: Show Bit Vector, Create New File, Show Directory, Exit.

### Concept & Algorithm
1. In linked file allocation, each file is a linked list of disk blocks scattered anywhere on disk.
2. The directory contains a pointer to the first and optionally last block of the file.
3. No external fragmentation occurs, and files can grow dynamically.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_02_Q1 Slip_02_Q1.c
./Slip_02_Q1
```

### Sample Output
```text
=== LINKED FILE ALLOCATION MENU ===
1. Show Bit Vector
2. Create New File
3. Show Directory
4. Exit
Enter your choice (1-4): 2
Enter file name: report.txt
Enter number of blocks required: 3
[+] File 'report.txt' created successfully using Linked Allocation.

=== LINKED FILE ALLOCATION MENU ===
1. Show Bit Vector
2. Create New File
3. Show Directory
4. Exit
Enter your choice (1-4): 3
File Name       Start Block     Length  Linked Blocks
report.txt      2               3       2 -> 7 -> 11
```

---

## Question 2: FCFS Disk Scheduling Simulation [15 Marks]

### Problem Statement
Write a simulation program for disk scheduling using FCFS algorithm. Accept total number of disk blocks, disk request string, and current head position from user. Display request service order and total head movements. Request: 55, 58, 39, 18, 90, 160, 150, 38, 184; Start Head: 50.

### Concept & Algorithm
1. FCFS (First-Come, First-Served) disk scheduling services requests in the order they arrive.
2. Head movement is calculated as |Request[i] - Request[i-1]|.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_02_Q2 Slip_02_Q2.c
./Slip_02_Q2
```

### Sample Output
```text
Order of Request Service:
50 -> 55 -> 58 -> 39 -> 18 -> 90 -> 160 -> 150 -> 38 -> 184

Total Head Movements: 498 cylinders
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is linked file allocation and its main advantage?
**Answer:** In linked allocation, each file is a linked list of disk blocks. Its primary advantage is that there is no external fragmentation and files can grow without contiguous space.

### Q2. What is a bit vector?
**Answer:** A bit vector (or bitmap) is an array of bits where each bit represents the status of a disk block (0 for free, 1 for allocated).

### Q3. What is the major disadvantage of FCFS disk scheduling?
**Answer:** It does not optimize head movement, leading to severe arm swinging (seek latency) and poor throughput compared to SSTF or SCAN.

### Q4. What is seek time in hard disk drives?
**Answer:** Seek time is the time taken by the read/write head arm to position itself over the target cylinder/track.

### Q5. How does linked allocation handle file corruption?
**Answer:** If any pointer in the linked chain is damaged or lost, the subsequent blocks of the file become inaccessible.
