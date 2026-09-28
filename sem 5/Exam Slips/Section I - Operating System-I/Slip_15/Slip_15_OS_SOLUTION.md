# Slip 15 — Operating System-I Solution Guide

## Question 1: Illustration of Orphan Process [15 Marks]

### Problem Statement
Write a C program to illustrate the concept of orphan process. Parent process creates a child and terminates before child has finished. Use fork(), sleep(), getpid(), getppid().

### Concept & Algorithm
1. An orphan process is a running process whose parent has terminated.
2. Orphan processes are immediately adopted by the `systemd` / `init` process (PID 1).

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_15_Q1 Slip_15_Q1.c
./Slip_15_Q1
```

### Sample Output
```text
[Parent] PID: 4120, Child PID: 4121
[Parent] Terminating immediately without waiting for child.
[Child] PID: 4121, Initial Parent PID: 4120
[Child] Sleeping for 4 seconds to become orphan...
[Child] Woke up! Current Parent PID: 1 (Adopted by systemd/init)
[Child] Exiting normally.
```

---

## Question 2: Preemptive Priority CPU Scheduling [15 Marks]

### Problem Statement
Write program to simulate Preemptive Priority scheduling. Arrival time, burst time, priority input. Output Gantt chart, TAT, WT, avg TAT & WT.

### Concept & Algorithm
1. When a new process arrives with higher priority than the currently running process, the current process is preempted.
2. Lower priority number denotes higher priority.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_15_Q2 Slip_15_Q2.c
./Slip_15_Q2
```

### Sample Output
```text
--- Gantt Chart ---
 | P1 | P2 | P3 |
Total Time: 15

Average Turnaround Time: 10.00
Average Waiting Time: 5.00
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is an orphan process?
**Answer:** An orphan process is a process whose parent has finished or terminated, leaving the child still running.

### Q2. What happens to an orphan process in Linux?
**Answer:** It is automatically adopted by PID 1 (init / systemd), which reaps its exit status when it terminates.

### Q3. What is a zombie process?
**Answer:** A zombie (defunct) process is a process that has completed execution but still has an entry in the process table because its parent hasn't read its exit status with wait().

### Q4. How does Priority Preemptive scheduling work?
**Answer:** The CPU scheduler immediately preempts the currently running process if a newly arrived process has a higher priority.

### Q5. What is process starvation in priority scheduling, and how is it solved?
**Answer:** Lower-priority processes may wait indefinitely; it is solved using Aging, which gradually increases the priority of waiting processes.
