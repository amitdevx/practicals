# Slip 16 — Operating System-I Solution Guide

## Question 1: LRU Page Replacement (Counter Method) [15 Marks]

### Problem Statement
Write simulation program for demand paging using LRU counter method. String: 3,5,7,2,5,1,2,3,1,3,5,3,1,6,2.

### Concept & Algorithm
1. LRU tracking with time counters for each page frame.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_16_Q1 Slip_16_Q1.c
./Slip_16_Q1
```

### Sample Output
```text
Total Page Faults: 9
Total Hits: 6
```

---

## Question 2: Custom Shell with count Command [15 Marks]

### Problem Statement
Write C program that behaves like shell ($ prompt). Tokenize and execute via fork. Implement 'count c|w|l filename'.

### Concept & Algorithm
1. Interactive prompt with tokenization.
2. Built-in command for counting characters, words, lines in a file.
3. External commands via fork and execvp.

### Compilation & Execution
```bash
gcc -Wall -Wextra -o Slip_16_Q2 Slip_16_Q2.c
./Slip_16_Q2
```

### Sample Output
```text
$ count c sample.txt
Total characters in 'sample.txt': 45
$ count w sample.txt
Total words in 'sample.txt': 8
$ count l sample.txt
Total lines in 'sample.txt': 3
$ exit
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is a shell in an operating system?
**Answer:** A shell is a command-line interpreter that acts as an interface between the user and the operating system kernel.

### Q2. How does a shell execute built-in vs external commands?
**Answer:** Built-in commands (like cd, exit, count) are executed directly in the shell process. External commands require forking a child process and calling execvp().

### Q3. Why does LRU not suffer from Belady's anomaly?
**Answer:** Because LRU belongs to the class of stack algorithms, where the set of pages in memory for n frames is always a subset of pages for n+1 frames.

### Q4. How does strtok() work in C?
**Answer:** strtok() breaks a string into a sequence of zero or more non-empty tokens based on delimiter characters.

### Q5. What is EOF in C file handling?
**Answer:** EOF is a macro representing End Of File, returned by functions like fgetc() when the end of the file is reached.
