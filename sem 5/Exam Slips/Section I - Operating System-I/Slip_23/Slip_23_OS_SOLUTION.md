# Slip 23 — Operating System-I Solution Guide

## Question 1: Fork System Call with Bubble Sort and Insertion Sort [15 Marks]

### Problem Statement
Implement C program to accept n integers. Main function creates child. Parent sorts using bubble sort and waits; child sorts using insertion sort.

### Concept & Algorithm
1. Child process performs insertion sort; parent waits and performs bubble sort.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_23_Q1 Slip_23_Q1.c
./Slip_23_Q1
```

### Sample Output
```text
[Child] Sorted Array: 3 6 9 12 15 
[Parent] Sorted Array: 3 6 9 12 15
```

---

## Question 2: Non-preemptive SJF CPU Scheduling [15 Marks]

### Problem Statement
Write program to simulate Non-preemptive Shortest Job First (SJF) scheduling. Input arrival time and burst time. Output Gantt chart, TAT, WT, avg TAT & WT.

### Concept & Algorithm
1. Non-preemptive scheduling prioritizing shortest job.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_23_Q2 Slip_23_Q2.c
./Slip_23_Q2
```

### Sample Output
```text
Average Turnaround Time: 6.33
Average Waiting Time: 2.33
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is a system call?
**Answer:** A system call is a programmatic way in which a computer program requests a service from the kernel of the operating system.

### Q2. How does the CPU switch between user mode and kernel mode?
**Answer:** Via software interrupts, traps, or special CPU instructions (e.g. `syscall` or `sysenter`).

### Q3. What is a race condition?
**Answer:** A race condition occurs when multiple processes access and manipulate shared data concurrently, and the outcome depends on the order of execution.

### Q4. Why is wait() necessary in parent process?
**Answer:** To collect child termination status and prevent zombie processes.

### Q5. How does insertion sort work?
**Answer:** It builds the sorted array one item at a time by repeatedly taking the next element and inserting it into its correct position among the already-sorted elements.
