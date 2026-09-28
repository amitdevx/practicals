# Slip 24 — Core Java and Web Technology-I Solution Guide

## Question 1: Abstract Class Shape with Cylinder Area and Volume [15 Marks]

### Problem Statement
Create abstract class Shape with methods area & volume. Derive class Cylinder (radius, height). Calculate area and volume.

### Concept & Algorithm
Implements abstract methods in Cylinder: surface area = 2*pi*r*(r+h), volume = pi*r^2*h.

### Compilation & Execution
```bash
javac Slip_24_Q1.java
java Slip_24_Q1
```

### Sample Output
```text
Cylinder (Radius: 5.0, Height: 10.0):
Surface Area: 471.24 sq. units
Volume:       785.40 cubic units
```

---

## Question 2: Synchronous vs Asynchronous File Operations in Node.js [15 Marks]

### Problem Statement
Write a Node.js program to demonstrate synchronous and asynchronous file operations and compare.

### Concept & Design
Compares blocking synchronous methods (writeFileSync, readFileSync) with non-blocking asynchronous callbacks.

### Compilation & Execution
```bash
node Slip_24_Q2.js
```

### Output Preview / Response
```text
--- Starting Synchronous Execution ---
Read Synchronous: Synchronous file content.
--- Starting Asynchronous Execution ---
Read Asynchronous: Asynchronous file content.
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. When should you use synchronous vs asynchronous file methods in Node.js?
**Answer:** Use synchronous methods only during startup or in simple CLI scripts; use asynchronous methods in production web servers to prevent blocking the event loop.

### Q2. What does Math.PI represent in Java?
**Answer:** A static final constant in java.lang.Math representing the mathematical ratio pi (~3.14159).

### Q3. What is an abstract method?
**Answer:** A method declared without an implementation (without braces) ending with a semicolon.

### Q4. What happens if a concrete subclass fails to implement all abstract methods?
**Answer:** The subclass itself must be declared abstract, and cannot be instantiated.

### Q5. What is the event-driven architecture of Node.js?
**Answer:** Components emit named events that trigger registered listener functions via EventEmitter.
