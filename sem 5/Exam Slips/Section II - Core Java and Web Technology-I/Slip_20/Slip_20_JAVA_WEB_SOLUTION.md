# Slip 20 — Core Java and Web Technology-I Solution Guide

## Question 1: Mouse Events Handler GUI [15 Marks]

### Problem Statement
Design a screen to handle Mouse Events (MOUSE_MOVED and MOUSE_CLICK) and display position in TextField.

### Concept & Algorithm
Implements MouseListener and MouseMotionListener to display live cursor coordinates.

### Compilation & Execution
```bash
javac Slip_20_Q1.java
java Slip_20_Q1
```

### Sample Output
```text
Mouse Moved at (145, 82)
Mouse Clicked at (145, 82)
```

---

## Question 2: Promise Division with Zero Handling [15 Marks]

### Problem Statement
Write a JavaScript program using Promise to divide two numbers. Reject if denominator is zero.

### Concept & Design
Constructs a Promise resolving quotient or rejecting Error('Division by zero').

### Compilation & Execution
```bash
node Slip_20_Q2.js
```

### Output Preview / Response
```text
100 / 4 = 25
Caught rejection: Division by zero error: Denominator cannot be 0.
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the difference between MouseListener and MouseMotionListener?
**Answer:** MouseListener handles clicks, presses, releases, enters, and exits; MouseMotionListener handles movements and drags.

### Q2. How do you obtain mouse coordinates in MouseEvent?
**Answer:** Using e.getX() and e.getY().

### Q3. What is the purpose of Promise.prototype.catch()?
**Answer:** To schedule a callback function to be called when the Promise is rejected.

### Q4. What is callback hell in JavaScript?
**Answer:** A situation where multiple nested asynchronous callbacks make code difficult to read and maintain; solved by Promises/async-await.

### Q5. Can a Promise change its state once resolved?
**Answer:** No, once a Promise is settled (fulfilled or rejected), its state and result are immutable.
