# Slip 19 — Operating System-I Solution Guide

## Question 1: Preemptive Priority CPU Scheduling [15 Marks]

### Problem Statement
Write program to simulate Preemptive Priority scheduling. Input arrival time, burst time, priority. Output Gantt chart, TAT, WT, avg TAT & WT.

### Concept & Algorithm
1. Preempts current process if higher priority job arrives.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_19_Q1 Slip_19_Q1.c
./Slip_19_Q1
```

### Sample Output
```text
Average Turnaround Time: 10.00
Average Waiting Time: 5.00
```

---

## Question 2: Demonstration of nice() System Call [15 Marks]

### Problem Statement
Write program that demonstrates use of nice() system call. After child process started using fork(), assign higher priority using nice().

### Concept & Algorithm
1. Demonstrates priority changes via nice().

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_19_Q2 Slip_19_Q2.c
./Slip_19_Q2
```

### Sample Output
```text
[Child] After nice(5), Updated Nice Value: 5
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the effect of passing a positive integer to nice()?
**Answer:** A positive value makes the process 'nicer' to other processes by lowering its scheduling priority.

### Q2. What is priority inversion?
**Answer:** Priority inversion occurs when a low-priority process holds a shared resource needed by a high-priority process, while a medium-priority process preempts the low-priority process.

### Q3. How is priority inversion resolved?
**Answer:** Using the Priority Inheritance Protocol, where the low-priority process temporarily inherits the high-priority process's priority level.

### Q4. Can child and parent communicate through global variables after fork?
**Answer:** No, because each process has its own private virtual memory space; inter-process communication (IPC) like pipes or shared memory is needed.

### Q5. What is exit() vs _exit() in C?
**Answer:** exit() flushes standard I/O buffers and calls registered atexit functions before terminating. _exit() terminates immediately without flushing buffers.
