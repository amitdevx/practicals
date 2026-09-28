# Slip 01 — Operating System-I Solution Guide

## Question 1: Banker's Algorithm Data Structures [15 Marks]

### Problem Statement
Write a C Menu driven Program to implement following functionality:
- **a)** Accept Available
- **b)** Display Allocation, Max
- **c)** Display the contents of need matrix
- **d)** Display Available

**Given System Snapshot:**

| Process | Allocation (A B C) | Max (A B C) | Available (A B C) |
| :---: | :---: | :---: | :---: |
| **P0** | 2 3 2 | 9 7 5 | 3 3 2 |
| **P1** | 4 0 0 | 5 2 2 | |
| **P2** | 5 0 4 | 1 0 4 | |
| **P3** | 4 3 3 | 4 4 4 | |
| **P4** | 2 2 4 | 6 5 5 | |

---

### Concept & Algorithm
1. **Banker's Algorithm** is a deadlock avoidance algorithm developed by Edsger Dijkstra. It tests for safety by simulating the allocation of predetermined maximum possible amounts of all resources.
2. **Data Structures**:
   - `Allocation[n][m]`: Resources currently allocated to each process.
   - `Max[n][m]`: Maximum demand of resources for each process.
   - `Available[m]`: Number of available instances of each resource type.
   - `Need[n][m]`: Remaining resource need of each process, calculated as:
     $$\text{Need}[i][j] = \text{Max}[i][j] - \text{Allocation}[i][j]$$

### Compilation & Execution
```bash
# Compile the C program
gcc -Wall -Wextra -o Slip_01_Q1 Slip_01_Q1.c

# Run the program
./Slip_01_Q1
```

### Sample Program Output
```text
=============================================
   BANKER'S ALGORITHM - MENU DRIVEN PROGRAM
=============================================
1. Accept Available
2. Display Allocation and Max
3. Display Contents of Need Matrix
4. Display Available
5. Exit
Enter your choice (1-5): 2

Process    | Allocation       | Max             
           | A   B   C        | A   B   C   
------------------------------------------------------------
P0         | 2   3   2        | 9   7   5   
P1         | 4   0   0        | 5   2   2   
P2         | 5   0   4        | 1   0   4   
P3         | 4   3   3        | 4   4   4   
P4         | 2   2   4        | 6   5   5   

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
Process    | A   B   C   
--------------------------------
P0         | 7   4   3   
P1         | 1   2   2   
P2         | -4  0   0   
P3         | 0   1   1   
P4         | 4   3   1   

=============================================
   BANKER'S ALGORITHM - MENU DRIVEN PROGRAM
=============================================
1. Accept Available
2. Display Allocation and Max
3. Display Contents of Need Matrix
4. Display Available
5. Exit
Enter your choice (1-5): 4

Available Resources Vector:
Resource A: 3
Resource B: 3
Resource C: 2
```

---

## Question 2: Custom Shell with `count` Command [15 Marks]

### Problem Statement
Write a C program that behaves like a shell which displays the command prompt `$`. It accepts the command, tokenizes the command line, and executes it by creating a child process. Also implement the additional custom command `count` as:
- **a.** `$ count c filename`: It will display the number of characters in given file
- **b.** `$ count w filename`: It will display the number of words in given file
- **c.** `$ count l filename`: It will display the number of lines in given file

---

### Concept & Algorithm
1. **Interactive Loop**: Display the prompt `$` and read input line using `fgets()`.
2. **Tokenization**: Parse the line into arguments (`args[]`) using `strtok()`.
3. **Built-in Command Handling**:
   - If the command is `count`, handle it directly in the parent process:
     - Open file using `fopen()`.
     - Read character-by-character using `fgetc()`.
     - Count characters, count lines on newline (`\n`), and count words using whitespace transitions.
   - If the command is `exit` or `quit`, break the loop.
4. **External Commands**:
   - Use `fork()` to create a child process.
   - In the child process (`pid == 0`), call `execvp(args[0], args)`.
   - In the parent process, use `waitpid(pid, &status, 0)` to wait for the child to complete.

### Compilation & Execution
```bash
# Compile the custom shell
gcc -Wall -Wextra -o Slip_01_Q2 Slip_01_Q2.c

# Run the shell
./Slip_01_Q2
```

### Sample Shell Session
```bash
$ count c sample.txt
Total characters in 'sample.txt': 32

$ count w sample.txt
Total words in 'sample.txt': 6

$ count l sample.txt
Total lines in 'sample.txt': 2

$ ls
os_slip_01.md  Slip_01_OS_SOLUTION.pdf  Slip_01_Q1.c  Slip_01_Q2.c  sample.txt

$ pwd
/home/amitdevx/Code/practicals/sem 5/Exam Slips/Section I - Operating System-I/Slip_01

$ exit
Exiting shell.
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the Banker's Algorithm and why is it called so?
**Answer:** It is a deadlock avoidance algorithm developed by Edsger Dijkstra. It is named Banker's Algorithm because it is modeled after a banking system that never allocates available cash in such a way that it can no longer satisfy the maximum cash demands of all its customers.

### Q2. How is the Need Matrix calculated?
**Answer:** The Need Matrix represents the remaining resources each process may still request. It is calculated element-wise as:
$$\text{Need}[i][j] = \text{Max}[i][j] - \text{Allocation}[i][j]$$

### Q3. What is the role of `fork()` in Unix process creation?
**Answer:** `fork()` creates an exact duplicate child process of the calling process. It returns `0` to the newly created child process, returns the child's PID to the parent process, and returns `-1` if process creation fails.

### Q4. What does the `execvp()` system call do?
**Answer:** `execvp()` replaces the current process image with a new process specified by the executable file and argument vector. It searches for the executable along the `PATH` environment variable.

### Q5. Why does the parent shell process call `wait()` or `waitpid()`?
**Answer:** If the parent does not wait for the child process to finish, the child could finish and become a **zombie process** (defunct process remaining in the process table). Calling `wait()` ensures proper resource cleanup and allows the shell prompt to reappear only after the command completes.
