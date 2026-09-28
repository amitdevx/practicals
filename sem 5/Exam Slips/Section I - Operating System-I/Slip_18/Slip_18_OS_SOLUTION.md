# Slip 18 — Operating System-I Solution Guide

## Question 1: Preemptive Shortest Job First (SJF / SRTF) CPU Scheduling [15 Marks]

### Problem Statement
Write program to simulate Preemptive Shortest Job First (SJF) scheduling. Input arrival time and first CPU burst. Output Gantt chart, TAT, WT, avg TAT & WT.

### Concept & Algorithm
1. Shortest Remaining Time First (SRTF) preempts the running process if a new process arrives with a shorter remaining burst time.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_18_Q1 Slip_18_Q1.c
./Slip_18_Q1
```

### Sample Output
```text
--- Gantt Chart ---
 | P1 | P2 | P3 |
Total Time: 12
Average Turnaround Time: 6.00
Average Waiting Time: 2.00
```

---

## Question 2: Orphan Process Illustration [15 Marks]

### Problem Statement
Write a C program to illustrate the concept of orphan process. Parent process creates a child and terminates before child has finished its task. Use fork(), sleep(), getpid(), getppid().

### Concept & Algorithm
1. Demonstrates orphan process adoption by init/systemd (PID 1).

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_18_Q2 Slip_18_Q2.c
./Slip_18_Q2
```

### Sample Output
```text
[Parent] Terminating immediately without waiting for child.
[Child] Woke up! Current Parent PID: 1 (Adopted by systemd/init)
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the difference between non-preemptive SJF and preemptive SJF?
**Answer:** In non-preemptive SJF, a process keeps the CPU until it finishes its burst. In preemptive SJF (SRTF), a newly arrived process with a shorter burst preempts the running process.

### Q2. What system call returns the parent PID of a process?
**Answer:** `getppid()` returns the process ID of the parent.

### Q3. What system call returns the current process PID?
**Answer:** `getpid()` returns the process ID of the current process.

### Q4. Why does the child process sleep in the orphan demonstration?
**Answer:** Sleeping gives the parent process enough time to exit first, leaving the child orphaned.

### Q5. What is CPU burst vs I/O burst?
**Answer:** A CPU burst is a period when the process is executing instructions on the CPU; an I/O burst is a period when the process is waiting for an I/O operation to complete.
