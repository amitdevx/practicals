# Slip 14 — Operating System-I Solution Guide

## Question 1: Process Forking and Array Binary Search [15 Marks]

### Problem Statement
Implement C program that accepts an integer array. Main function forks child process. Parent sorts array; child performs binary search.

### Concept & Algorithm
1. Parent sorts array using sorting algorithm.
2. Child performs binary search on the sorted data.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_14_Q1 Slip_14_Q1.c
./Slip_14_Q1
```

### Sample Output
```text
[Parent] Original Array: 45 12 89 23 7 
[Parent] Sorted Array: 7 12 23 45 89 
[Child PID: 12350] Binary Searching for 23 in sorted array...
[Child] Element 23 found at index 2!
[Parent] Child search operation completed.
```

---

## Question 2: FIFO Page Replacement Simulation [15 Marks]

### Problem Statement
Write simulation program for demand paging and show page scheduling and total page faults using FIFO. String: 3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6.

### Concept & Algorithm
1. Replaces the oldest page present in the frame queue when a page fault occurs.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_14_Q2 Slip_14_Q2.c
./Slip_14_Q2
```

### Sample Output
```text
Total Page Faults: 13
Total Hits: 2
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is binary search and its time complexity?
**Answer:** Binary search is an efficient search algorithm on sorted arrays that divides the search interval in half each time; its time complexity is O(log n).

### Q2. What is execve() system call?
**Answer:** execve() executes the program referred to by pathname, replacing the current process image with a new process image.

### Q3. What happens to open file descriptors upon fork()?
**Answer:** Child inherits duplicates of all open file descriptors from the parent, pointing to the same file table entries.

### Q4. What is the replacement victim in FIFO?
**Answer:** The page that entered memory earliest (at the front of the queue).

### Q5. What is virtual memory?
**Answer:** Virtual memory is a memory management capability that provides an idealized abstraction of storage resources, allowing execution of processes larger than physical RAM.
