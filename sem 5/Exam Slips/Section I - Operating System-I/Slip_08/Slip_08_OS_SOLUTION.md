# Slip 08 — Operating System-I Solution Guide

## Question 1: Indexed File Allocation Simulation [15 Marks]

### Problem Statement
Write a program to simulate Index file allocation method. Disk with n blocks. Randomly mark allocated, maintain free list, menu: Show Bit Vector, Create New File, Show Directory, Exit.

### Concept & Algorithm
1. In indexed allocation, each file has its own index block containing an array of disk-block addresses.
2. Supports direct/random access without external fragmentation.
3. Requires extra overhead for index blocks.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_08_Q1 Slip_08_Q1.c
./Slip_08_Q1
```

### Sample Output
```text
=== INDEXED FILE ALLOCATION MENU ===
1. Show Bit Vector
2. Create New File
3. Show Directory
4. Exit
Enter your choice (1-4): 2
Enter file name: doc.pdf
Enter number of data blocks required: 3
[+] File 'doc.pdf' allocated with Index Block at 1.

=== INDEXED FILE ALLOCATION MENU ===
1. Show Bit Vector
2. Create New File
3. Show Directory
4. Exit
Enter your choice (1-4): 3
File Name       Index Block     Length  Data Blocks
doc.pdf         1               3       3 5 8
```

---

## Question 2: Demonstration of nice() System Call [15 Marks]

### Problem Statement
Write a program that demonstrates the use of nice () system call. After child process is started using fork(), assign priority using nice().

### Concept & Algorithm
1. Demonstrates process creation via fork() and altering CPU priority via nice().

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_08_Q2 Slip_08_Q2.c
./Slip_08_Q2
```

### Sample Output
```text
[Parent] Parent Nice Value: 0
[Child] Initial Nice Value: 0
[Child] After nice(5), Updated Nice Value: 5
[Parent] Child execution complete.
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is an index block in indexed file allocation?
**Answer:** An index block is a dedicated disk block storing pointers/addresses to all the data blocks belonging to a file.

### Q2. What happens if a file is larger than what a single index block can store?
**Answer:** Techniques like linked index blocks, multilevel indexing (indirect blocks, like in Unix inodes), or combined indexing are used.

### Q3. Compare indexed allocation with linked allocation.
**Answer:** Indexed allocation supports direct/random access, whereas linked allocation only supports sequential access. However, indexed allocation has higher space overhead for small files.

### Q4. What happens to nice value upon fork()?
**Answer:** The child process inherits the parent's nice value at the time of fork().

### Q5. What is CFS in Linux?
**Answer:** CFS stands for Completely Fair Scheduler, the default Linux CPU scheduler which uses red-black trees based on virtual runtime (vruntime).
