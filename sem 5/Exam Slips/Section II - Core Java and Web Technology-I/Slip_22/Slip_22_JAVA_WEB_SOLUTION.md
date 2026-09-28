# Slip 22 — Core Java and Web Technology-I Solution Guide

## Question 1: Product Interface and Object Counter [15 Marks]

### Problem Statement
Create class Product (id, name, cost, qty) using interface, default/parameterized constructors, display contents and object count.

### Concept & Algorithm
Uses interface implementation and a static counter incremented in constructors.

### Compilation & Execution
```bash
javac Slip_22_Q1.java
java Slip_22_Q1
```

### Sample Output
```text
ID: 101 Name: Laptop  Cost: ₹65000.0  Quantity: 5
Total Product Objects Created: 3
```

---

## Question 2: Asynchronous File Operations in Node.js [15 Marks]

### Problem Statement
Write a Node.js program using fs module to perform file operations asynchronously.

### Concept & Design
Uses fs.writeFile, fs.readFile, and fs.unlink with error-first callback conventions.

### Compilation & Execution
```bash
node Slip_22_Q2.js
```

### Output Preview / Response
```text
[+] File written successfully.
[+] File contents: Initial content written asynchronously.
[+] File cleaned up.
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is a static variable in Java?
**Answer:** A class-level variable shared by all instances of the class; memory is allocated once when the class is loaded.

### Q2. What is an error-first callback in Node.js?
**Answer:** A convention where the first argument of the callback is reserved for an error object (or null if successful).

### Q3. Why is asynchronous I/O preferred in Node.js?
**Answer:** Because it does not block the single thread, allowing the server to handle thousands of concurrent requests.

### Q4. Can an interface have instance variables in Java?
**Answer:** No, all fields declared in an interface are implicitly public, static, and final (constants).

### Q5. What is the difference between interface and abstract class?
**Answer:** An abstract class can have instance state and constructors; an interface cannot have instance state or constructors.
