# Slip 03 — Core Java and Web Technology-I Solution Guide

## Question 1: Custom Package String Operations [15 Marks]

### Problem Statement
Write a package for String operation with classes Con and Comp.

### Concept & Algorithm
Con implements string concatenation; Comp implements string equality comparison.

### Compilation & Execution
```bash
javac Slip_03/stringop/*.java Slip_03/Slip_03_Q1.java
java -cp Slip_03 Slip_03_Q1
```

### Sample Output
```text
String 1: Pune
String 2: University
String 3: Pune
Concatenation of String 1 and 2: PuneUniversity
Comparison of String 1 and 2: false
Comparison of String 1 and 3: true
```

---

## Question 2: Responsive College Homepage (CSS Flexbox) [15 Marks]

### Problem Statement
Create a responsive webpage using CSS Flexbox for college homepage containing header, nav, content, sidebar, footer.

### Concept & Design
Implements a responsive layout using display: flex, media queries, and semantic containers.

### Execution
Open `Slip_03_Q2.html` in any standard web browser (Chrome, Firefox, Edge).

### Output Preview / Response
```text
[Responsive College Homepage rendered with header, flex columns, and footer]
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is a package in Java?
**Answer:** A namespace that organizes a set of related classes and interfaces.

### Q2. What is CSS Flexbox?
**Answer:** A one-dimensional layout model that distributes space and aligns items along a main axis or cross axis.

### Q3. What does flex-direction do?
**Answer:** It establishes the main-axis direction (row, column, row-reverse, column-reverse).

### Q4. What is the difference between equals() and == in Java strings?
**Answer:** '==' checks reference equality (memory location), whereas equals() checks content equality.

### Q5. Why is String immutable in Java?
**Answer:** For security, synchronization, caching (String pool), and hashcode consistency.
