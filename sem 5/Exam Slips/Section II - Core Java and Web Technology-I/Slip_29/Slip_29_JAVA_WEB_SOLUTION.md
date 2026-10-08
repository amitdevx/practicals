# Slip 29 — Core Java and Web Technology-I Solution Guide

## Question 1: Static Method and Zero Exception Check [15 Marks]

### Problem Statement
Accept number; if zero throw user defined exception 'Number is 0' otherwise check whether prime (Use static keyword).

### Concept & Algorithm
Uses static method checkNumber(n) throwing ZeroNumberException on 0, and checks primality.

### Compilation & Execution
```bash
javac Slip_29_Q1.java
java Slip_29_Q1
```

### Sample Output
```text
Enter a number: 17
17 is a Prime Number.
```

---

## Question 2: File Statistics with fs.stat() in Node.js [15 Marks]

### Problem Statement
Write a Node.js program to demonstrate file statistics using fs.stat(), including size, timestamps, type.

### Concept & Design
Extracts size, isFile(), isDirectory(), birthtime, and mtime using fs.stat().

### Compilation & Execution
```bash
node Slip_29_Q2.js
```

### Output Preview / Response
```text
=== File Statistics ===
File Size:         bytes
Is Directory:      false
Is File:           true
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is a static method in Java?
**Answer:** A method that belongs to the class rather than object instances; it can be called without creating an instance.

### Q2. Can static methods access non-static instance variables directly?
**Answer:** No, static methods cannot access non-static variables directly because they have no 'this' context.

### Q3. What information does fs.stat() return in Node.js?
**Answer:** File size, block size, device ID, inode, mode permissions, UID/GID, and access/modification/creation timestamps.

### Q4. What is stats.isDirectory()?
**Answer:** A method on the fs.Stats object that returns true if the path represents a directory.

### Q5. What is the difference between mtime and ctime in file systems?
**Answer:** mtime (modification time) changes when file contents change; ctime (change time) changes when file metadata (permissions, owner) or contents change.
