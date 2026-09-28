# Slip 07 — Operating System-I Solution Guide

## Question 1: Banker's Algorithm Deadlock Avoidance (4 Resources) [15 Marks]

### Problem Statement
Consider system snapshot with 5 processes P0-P4 and 4 resource types A, B, C, D. Allocation, Max, Available given. Display Need, check safety, check if P1 request (0,4,2,0) can be granted.

### Concept & Algorithm
1. Multidimensional resource avoidance with 4 resource types.
2. Computes Need = Max - Allocation for all processes.
3. Evaluates resource request algorithm safety.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_07_Q1 Slip_07_Q1.c
./Slip_07_Q1
```

### Sample Output
```text
Process Allocation     Max             Need
P0      2 0 0 1         4 2 1 2         2 2 1 1 
P1      3 1 2 1         5 2 5 2         2 1 3 1 
P2      2 1 0 3         2 3 1 6         0 2 1 3 
P3      1 3 1 2         1 4 2 4         0 1 1 2 
P4      1 4 3 2         3 6 6 5         2 2 3 3 

Available Resources: 3 3 2 1 
[+] The system is currently in a SAFE state.
Safe Sequence: P0 -> P2 -> P3 -> P1 -> P4

Checking Request from P1: ( 0 4 2 0 )
[-] Error: Process exceeded maximum claim / insufficient available resources.
```

---

## Question 2: Process Priority Adjustment with nice() System Call [15 Marks]

### Problem Statement
Write a program that demonstrates the use of nice() system call. After child process is started using fork(), assign priority using nice().

### Concept & Algorithm
1. nice() system call adds an increment to the nice value of the calling process.
2. In Unix, nice values range from -20 (highest priority) to 19 (lowest priority).

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_07_Q2 Slip_07_Q2.c
./Slip_07_Q2
```

### Sample Output
```text
[Parent] Parent Nice Value: 0
[Child] Initial Nice Value: 0
[Child] After nice(5), Updated Nice Value: 5
[Child] Doing task and finishing...
[Parent] Child execution complete.
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What does the nice value represent in Linux?
**Answer:** The nice value represents the user-space priority hint for CPU scheduling, ranging from -20 (highest priority) to +19 (lowest priority).

### Q2. Can a normal user decrease the nice value (increase priority)?
**Answer:** No, only the superuser (root) can set a negative nice value or decrease an existing nice value.

### Q3. What header file is required for nice() and getpriority()?
**Answer:** `#include <unistd.h>` and `#include <sys/resource.h>`.

### Q4. What is the difference between safe state and unsafe state?
**Answer:** A safe state guarantees that deadlock can be avoided. An unsafe state is not necessarily a deadlock, but deadlock is possible and cannot be prevented with certainty.

### Q5. What is starvation in resource allocation?
**Answer:** Starvation (indefinite postponement) occurs when a process is perpetually denied necessary resources while other processes make continuous progress.
