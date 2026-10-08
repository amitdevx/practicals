# Slip 14 — Core Java and Web Technology-I Solution Guide

## Question 1: GUI Prime Number Checker [15 Marks]

### Problem Statement
Write a GUI program that takes numeric input via TextField and displays whether it is prime upon clicking Process button.

### Concept & Algorithm
Uses Java Swing JFrame, GridLayout, ActionListener, and prime testing logic.

### Compilation & Execution
```bash
javac --module-path /path/to/javafx/lib --add-modules javafx.controls Slip_14_Q1.java
java --module-path /path/to/javafx/lib --add-modules javafx.controls Slip_14_Q1
```

### Sample Output
```text
[GUI window with input field, result field, and Process button]
```

---

## Question 2: Object Destructuring for Employee Details [15 Marks]

### Problem Statement
Create an object containing employee details (name, department, salary) and extract using object destructuring.

### Concept & Design
Extracts employee attributes cleanly using const { name, department, salary } = employee.

### Compilation & Execution
```bash
node Slip_14_Q2.js
```

### Output Preview / Response
```text
Employee Name : Rohan Varma
Department    : Cloud Engineering
Salary        : ₹85000
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is an ActionListener in Java GUI?
**Answer:** An interface that handles action events such as clicking a button or pressing enter.

### Q2. What is SwingUtilities.invokeLater()?
**Answer:** A utility method that queues a task for execution on the Event Dispatch Thread (EDT) for thread safety.

### Q3. What is object destructuring default value syntax in ES6?
**Answer:** const { name = 'Default' } = obj;

### Q4. What is a prime number?
**Answer:** A natural number greater than 1 that has no positive divisors other than 1 and itself.

### Q5. Why is checking up to sqrt(n) sufficient for primality test?
**Answer:** Because if n has a factor larger than sqrt(n), the corresponding paired factor must be smaller than sqrt(n).
