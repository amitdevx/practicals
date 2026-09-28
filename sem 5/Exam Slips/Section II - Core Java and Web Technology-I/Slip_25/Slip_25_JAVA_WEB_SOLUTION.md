# Slip 25 — Core Java and Web Technology-I Solution Guide

## Question 1: Calculator Interface and SimpleCalc Class [15 Marks]

### Problem Statement
Write a Java program that defines interface Calculator containing add() and subtract() and implements in class SimpleCalc.

### Concept & Algorithm
Demonstrates interface definition and implementation using class SimpleCalc implements Calculator.

### Compilation & Execution
```bash
javac Slip_25_Q1.java
java Slip_25_Q1
```

### Sample Output
```text
45.5 + 12.3 = 57.8
45.5 - 12.3 = 33.2
```

---

## Question 2: Directory Management and JSON Operations in Node.js [15 Marks]

### Problem Statement
Write a Node.js program to perform directory management and JSON parsing/writing.

### Concept & Design
Uses fs.mkdirSync, fs.writeFileSync, JSON.stringify, and JSON.parse.

### Compilation & Execution
```bash
node Slip_25_Q2.js
```

### Output Preview / Response
```text
[+] Directory 'test_dir' created.
[+] JSON data written.
[+] Parsed JSON Student Name: Snehal
[+] Cleanup complete.
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is JSON?
**Answer:** JavaScript Object Notation, a lightweight data interchange format that is easy for humans to read and machines to parse.

### Q2. What is JSON.stringify() vs JSON.parse()?
**Answer:** JSON.stringify() serializes a JavaScript object into a JSON string; JSON.parse() deserializes a JSON string into an object.

### Q3. Can a class implement multiple interfaces in Java?
**Answer:** Yes, a class can implement any number of interfaces separated by commas.

### Q4. What is fs.mkdir() in Node.js?
**Answer:** Asynchronously creates a new directory in the file system.

### Q5. What is a marker interface in Java?
**Answer:** An interface with no methods or constants (e.g. Serializable, Cloneable), used to mark class capabilities.
