# Slip 10 — Core Java and Web Technology-I Solution Guide

## Question 1: Display File Contents in Uppercase [15 Marks]

### Problem Statement
Write a program to read contents of abc.txt file. Display contents in uppercase.

### Concept & Algorithm
Uses BufferedReader and FileReader to read lines and converts strings to uppercase using toUpperCase().

### Compilation & Execution
```bash
javac Slip_10_Q1.java
java Slip_10_Q1
```

### Sample Output
```text
CORE JAVA AND WEB TECHNOLOGY PRACTICAL EXAMINATION 2026-2027.
```

---

## Question 2: Student Grade Report with Template Literals [15 Marks]

### Problem Statement
Write a JavaScript program to store student information and marks and generate formatted report using template literals.

### Concept & Design
Demonstrates ES6 template literals (backticks `...`) and string interpolation (${expr}).

### Compilation & Execution
```bash
node Slip_10_Q2.js
```

### Output Preview / Response
```text
Student Name : Aarav Sharma
Total Marks  : 265 / 300
Percentage   : 88.33%
Final Status : PASS
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What are template literals in JavaScript?
**Answer:** String literals allowing embedded expressions, tagged templates, and multiline strings delimited by backticks (`).

### Q2. How do you format decimal numbers in JavaScript?
**Answer:** Using number.toFixed(digits).

### Q3. What exception is thrown when a file does not exist in Java?
**Answer:** java.io.FileNotFoundException.

### Q4. What is the difference between toUpperCase() and toLowerCase()?
**Answer:** Converts all characters of the String to upper or lower case using default locale rules.

### Q5. Why is finally block used in Java exception handling?
**Answer:** To execute critical cleanup code (like closing streams) regardless of whether an exception occurs.
