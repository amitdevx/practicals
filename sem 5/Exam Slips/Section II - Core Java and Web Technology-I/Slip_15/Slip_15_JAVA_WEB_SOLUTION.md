# Slip 15 — Core Java and Web Technology-I Solution Guide

## Question 1: Simple GUI Calculator [15 Marks]

### Problem Statement
Write a GUI program to build a simple calculator with digit buttons (0-9) and operators (+, -, *, /).

### Concept & Algorithm
Implements interactive calculator GUI with BorderLayout and GridLayout button keypad.

### Compilation & Execution
```bash
javac --module-path /path/to/javafx/lib --add-modules javafx.controls Slip_15_Q1.java
java --module-path /path/to/javafx/lib --add-modules javafx.controls Slip_15_Q1
```

### Sample Output
```text
[Interactive calculator GUI displaying calculation results]
```

---

## Question 2: Spread Operator for Array Copy and Extension [15 Marks]

### Problem Statement
Write a JavaScript program to create copy of existing array using spread operator and add new element.

### Concept & Design
Uses [...original, newItem] to perform a shallow clone and append an element.

### Compilation & Execution
```bash
node Slip_15_Q2.js
```

### Output Preview / Response
```text
Original Array: [ 'Apple', 'Banana', 'Cherry' ]
Copied & Extended Array: [ 'Apple', 'Banana', 'Cherry', 'Dragonfruit' ]
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the spread operator (...) in JavaScript?
**Answer:** An operator that expands an iterable (like an array) into individual elements.

### Q2. Does the spread operator create a shallow or deep copy?
**Answer:** It creates a shallow copy: top-level elements are cloned, but nested objects are still referenced.

### Q3. How do you handle division by zero in Java?
**Answer:** For integers, it throws ArithmeticException; for floating point (double), it evaluates to Infinity or NaN.

### Q4. What layout manager arranges components in five regions (North, South, East, West, Center)?
**Answer:** BorderLayout.

### Q5. What is the Event Dispatch Thread (EDT) in Java Swing?
**Answer:** The dedicated thread responsible for handling GUI events and painting components.
