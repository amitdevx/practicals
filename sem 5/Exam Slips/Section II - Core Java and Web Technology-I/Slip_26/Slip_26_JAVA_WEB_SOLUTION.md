# Slip 26 — Core Java and Web Technology-I Solution Guide

## Question 1: User-Defined Exception for Student Attendance [15 Marks]

### Problem Statement
Define class Student (name, roll, total, attended). If attendance < 75%, throw exception 'Student is Not Eligible for Exam'.

### Concept & Algorithm
Custom exception class extends Exception; thrown when ((attended/total)*100) < 75.0.

### Compilation & Execution
```bash
javac Slip_26_Q1.java
java Slip_26_Q1
```

### Sample Output
```text
Roll No: 101 Name: Pooja  Status: Eligible for Exam
Exception caught: Student is Not Eligible for Exam (Attendance: 62.5%)
```

---

## Question 2: Copy, Rename and Delete Files Asynchronously [15 Marks]

### Problem Statement
Write a Node.js program using fs module to copy, rename and delete files asynchronously.

### Concept & Design
Uses fs.copyFile, fs.rename, and fs.unlink with error handling.

### Compilation & Execution
```bash
node Slip_26_Q2.js
```

### Output Preview / Response
```text
[+] File copied successfully.
[+] File renamed successfully.
[+] File deleted successfully.
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. How do you create a user-defined exception in Java?
**Answer:** By creating a class that extends java.lang.Exception (or RuntimeException) and providing a constructor that passes the message to super(message).

### Q2. What is the difference between throw and throws in Java?
**Answer:** throw is used to explicitly throw an exception object; throws is declared in a method signature to specify exceptions the method might propagate.

### Q3. What does fs.copyFile() do in Node.js?
**Answer:** Asynchronously copies src to dest; overwrites dest by default.

### Q4. What is checked vs unchecked exception in Java?
**Answer:** Checked exceptions (subclasses of Exception excluding RuntimeException) are checked at compile time; unchecked exceptions (subclasses of RuntimeException) occur at runtime.

### Q5. What is fs.rename() in Node.js?
**Answer:** Asynchronously renames or moves a file or directory from one path to another.
