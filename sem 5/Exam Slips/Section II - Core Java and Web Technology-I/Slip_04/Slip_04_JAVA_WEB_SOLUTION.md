# Slip 04 — Core Java and Web Technology-I Solution Guide

## Question 1: Multidimensional Array Matrix Operations [15 Marks]

### Problem Statement
Write a menu driven program to perform operations on multidimensional array: addition, multiplication, transpose.

### Concept & Algorithm
Uses 2D integer arrays with nested loops to compute matrix addition, multiplication, and transposition.

### Compilation & Execution
```bash
javac Slip_04_Q1.java
java Slip_04_Q1
```

### Sample Output
```text
Matrix A:
1 2 
3 4 
Matrix B:
5 6 
7 8 

1. Add Matrices
2. Multiply Matrices
3. Transpose of Matrix A
4. Exit
Enter choice: 1
Sum:
6 8 
10 12 
```

---

## Question 2: Change Heading Text [15 Marks]

### Problem Statement
Create a webpage containing a heading and a button. When the button is clicked, change the heading text from "Hello! Welcome" to "Text Changed Successfully!".

### Concept & Design
Uses JavaScript document.getElementById('heading').innerText manipulation on button click event to update heading text.

### Execution
Open `Slip_04_Q2.html` in any standard web browser (Chrome, Firefox, Edge).

### Output Preview / Response
```text
[Heading text changes from "Hello! Welcome" to "Text Changed Successfully!" on button click]
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. How do you declare a 2D array in Java?
**Answer:** int[][] arr = new int[rows][cols];

### Q2. What is the DOM in web development?
**Answer:** Document Object Model: a programming API representing an HTML document as a tree of nodes.

### Q3. What is an event listener in JavaScript?
**Answer:** A procedure that waits for an event to occur (e.g. click, hover) and executes a handler callback.

### Q4. What is garbage collection in Java?
**Answer:** An automatic memory management process that frees memory occupied by unreachable objects.

### Q5. Can Java arrays resize dynamically?
**Answer:** No, arrays have fixed length once allocated; dynamic collections like ArrayList must be used instead.
