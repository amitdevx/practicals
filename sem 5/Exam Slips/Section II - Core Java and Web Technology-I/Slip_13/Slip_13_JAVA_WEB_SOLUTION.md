# Slip 13 — Core Java and Web Technology-I Solution Guide

## Question 1: Clock Class with AM/PM Mode [15 Marks]

### Problem Statement
Define Clock class: a. Accept Hours, Minutes, Seconds b. Check validity c. Set time to AM/PM mode.

### Concept & Algorithm
Validates time ranges (0-23 hours, 0-59 mins/secs) and converts 24-hr time to 12-hr AM/PM format.

### Compilation & Execution
```bash
javac Slip_13_Q1.java
java Slip_13_Q1
```

### Sample Output
```text
24-hr Time (14:35:20) in AM/PM mode: Time: 02:35:20 PM
```

---

## Question 2: Array Destructuring Value Swap [15 Marks]

### Problem Statement
Write a JavaScript program to swap two numbers without using a third variable using array destructuring.

### Concept & Design
Uses ES6 array destructuring assignment: [a, b] = [b, a].

### Compilation & Execution
```bash
node Slip_13_Q2.js
```

### Output Preview / Response
```text
Before Swap: a = 42, b = 99
After Swap:  a = 99, b = 42
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. How does array destructuring swap work in ES6?
**Answer:** A temporary array is created on the right-hand side and immediately unpacked into the left-hand variables.

### Q2. What is data validation in OOP?
**Answer:** Ensuring that internal object state remains consistent and adheres to specified domain constraints.

### Q3. What does printf format specifier %02d mean in Java?
**Answer:** Prints an integer with at least 2 digits, zero-padded if necessary.

### Q4. What is the difference between primitive data types and reference types in Java?
**Answer:** Primitives hold raw values in memory stack; reference types store references to objects in the heap.

### Q5. Can an interface have concrete methods in modern Java?
**Answer:** Yes, since Java 8, interfaces can contain default and static concrete methods.
