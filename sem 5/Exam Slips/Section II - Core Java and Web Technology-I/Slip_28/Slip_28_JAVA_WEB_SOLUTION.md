# Slip 28 — Core Java and Web Technology-I Solution Guide

## Question 1: Custom InvalidDateException Class [15 Marks]

### Problem Statement
Define class MyDate(Day, Month, year) to accept/display date. Throw user defined exception 'InvalidDateException' if date is invalid.

### Concept & Algorithm
Implements leap year calculation and calendar month day boundary validation; throws InvalidDateException on bad dates.

### Compilation & Execution
```bash
javac Slip_28_Q1.java
java Slip_28_Q1
```

### Sample Output
```text
Date: 25/09/2026
Exception caught: Invalid Date: 31/2/2026
```

---

## Question 2: Filter Directory Files by Extensions in Node.js [15 Marks]

### Problem Statement
Create a Node.js program to list files in directory and filter based on extensions (.txt, .json, .js).

### Concept & Design
Reads directory entries with fs.readdirSync and filters using path.extname().

### Compilation & Execution
```bash
node Slip_28_Q2.js
```

### Output Preview / Response
```text
Filtering files in '.' for: .txt, .json, .js
Matching Files:
  -> Slip_28_Q2.js
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. How do you check for leap year in calendar validation?
**Answer:** A year is leap if (year % 400 == 0) or (year % 4 == 0 and year % 100 != 0).

### Q2. What is path.extname() return value for files without extensions?
**Answer:** It returns an empty string ('').

### Q3. What is the difference between readdir and readdirSync in Node.js?
**Answer:** readdir is asynchronous and non-blocking with callback; readdirSync is synchronous and blocking.

### Q4. Why should exceptions represent exceptional conditions rather than normal flow control?
**Answer:** Because creating and throwing exception objects involves stack unwinding, which is computationally expensive.

### Q5. What is the base class of all exceptions and errors in Java?
**Answer:** java.lang.Throwable.
