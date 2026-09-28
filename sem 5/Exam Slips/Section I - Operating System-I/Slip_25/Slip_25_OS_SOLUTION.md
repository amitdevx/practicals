# Slip 25 — Operating System-I Solution Guide

## Question 1: Orphan Process Demonstration [15 Marks]

### Problem Statement
Write a C program to illustrate orphan process concept. Parent terminates before child finishes. Use fork(), sleep(), getpid(), getppid().

### Concept & Algorithm
1. Demonstrates orphan process adoption by PID 1.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_25_Q1 Slip_25_Q1.c
./Slip_25_Q1
```

### Sample Output
```text
[Child] Woke up! Current Parent PID: 1 (Adopted by systemd/init)
```

---

## Question 2: Custom Shell with search Command [15 Marks]

### Problem Statement
Write C program that behaves like shell ($ prompt). Tokenize and execute via fork. Implement 'search f|c|a pattern filename'.

### Concept & Algorithm
1. Custom shell with search command:
   - search f pattern filename: first occurrence
   - search c pattern filename: count occurrences
   - search a pattern filename: all occurrences.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_25_Q2 Slip_25_Q2.c
./Slip_25_Q2
```

### Sample Output
```text
$ search f main test.c
First occurrence at Line 3: int main() {
$ search c main test.c
Total occurrences of 'main' in 'test.c': 2
$ exit
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is an orphan process vs a daemon process?
**Answer:** An orphan process is accidentally left behind when its parent dies; a daemon process is intentionally orphaned and detached from a terminal to run background services.

### Q2. How does the custom shell handle command execution?
**Answer:** It reads the command string, splits it into arguments using strtok(), and runs execvp() in a child process created with fork().

### Q3. What is the PATH environment variable?
**Answer:** A colon-separated list of directories in which the shell looks for executable commands.

### Q4. What does strstr() do in C?
**Answer:** strstr(haystack, needle) finds the first occurrence of the substring needle in the string haystack.

### Q5. What is signal in Unix?
**Answer:** A signal is an asynchronous notification sent to a process to inform it of an event (e.g. SIGINT, SIGKILL, SIGCHLD).
