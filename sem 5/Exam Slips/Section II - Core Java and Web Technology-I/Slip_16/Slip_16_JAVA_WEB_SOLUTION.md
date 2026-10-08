# Slip 16 — Core Java and Web Technology-I Solution Guide

## Question 1: Shopping Cart Simulator GUI [15 Marks]

### Problem Statement
Write a JavaFX application that simulates a shopping cart with item buttons and running total.

### Concept & Algorithm
Uses JavaFX ListView, and action listeners to add items and update cumulative bill total.

### Compilation & Execution
```bash
javac --module-path $PATH_TO_FX --add-modules javafx.controls Slip_16_Q1.java
java --module-path $PATH_TO_FX --add-modules javafx.controls Slip_16_Q1
```

### Sample Output
```text
[Shopping cart GUI displaying items added and updated bill total]
```

---

## Question 2: Rest Parameter for Variable Arguments Sum [15 Marks]

### Problem Statement
Write a JavaScript program using rest parameter to accept any number of values and calculate sum.

### Concept & Design
Uses (...numbers) => numbers.reduce(...) to sum an arbitrary argument list.

### Compilation & Execution
```bash
node Slip_16_Q2.js
```

### Output Preview / Response
```text
Sum of (10, 20, 30): 60
Sum of (5, 15, 25, 35, 45): 125
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the rest parameter in ES6?
**Answer:** A syntax that allows a function to accept an indefinite number of arguments as an array.

### Q2. What is the difference between rest parameter and spread operator?
**Answer:** Rest parameter gathers multiple elements into an array; spread operator expands an array into individual elements.

### Q3. What is reduce() in JavaScript arrays?
**Answer:** An array method that executes a reducer callback on each element to accumulate a single result.

### Q4. What is DefaultListModel in Java Swing?
**Answer:** A concrete implementation of ListModel used to dynamically add, remove, and manage items in a JList.

### Q5. Can a rest parameter appear anywhere in a function parameter list?
**Answer:** No, the rest parameter must strictly be the last parameter in the function declaration.
