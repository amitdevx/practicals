# Slip 09 — Core Java and Web Technology-I Solution Guide

## Question 1: Array of Employee Objects [15 Marks]

### Problem Statement
Write a program which define class Employee with data member as id, name and salary Store the information of 'n' employees and display the name of employee having maximum salary (Use array of object).

### Concept & Algorithm
Creates an array of `Employee` references, reads inputs for 'n' employees from standard input, and finds the maximum salary while iterating through the array.

### Compilation & Execution
```bash
javac Slip_09_Q1.java
java Slip_09_Q1
```

### Sample Output
```text
Enter number of employees: 3
Enter details for employee 1:
ID: 101
Name: Aarav
Salary: 55000
Enter details for employee 2:
ID: 102
Name: Pooja
Salary: 72000
Enter details for employee 3:
ID: 103
Name: Rohan
Salary: 48000

Employee with maximum salary:
ID: 102	Name: Pooja	Salary: 72000.0
```

---

## Question 2: JavaScript Arrow Functions for Math Operations [15 Marks]

### Problem Statement
Write a JavaScript program to demonstrate Arrow Functions for addition, subtraction, multiplication and division.

### Concept & Design
Uses ES6 arrow function syntax (`() => ...`) for concise arithmetic operation handlers.

### Compilation & Execution
```bash
node Slip_09_Q2.js
```

### Output Preview / Response
```text
=== Demonstration of Arrow Functions ===
20 + 5 = 25
20 - 5 = 15
20 * 5 = 100
20 / 5 = 4
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is an arrow function in ES6?
**Answer:** A concise syntax for writing function expressions using '=>', which lexically binds the 'this' value.

### Q2. How do arrow functions handle 'this' differently from normal functions?
**Answer:** Arrow functions do not have their own 'this'; they inherit 'this' from the enclosing lexical scope.

### Q3. How do you create an array of objects in Java?
**Answer:** `ClassName[] arr = new ClassName[size];` followed by instantiating each element.

### Q4. What is the memory representation of an object array in Java?
**Answer:** An array of references, where each cell stores the memory address of an actual object heap instance.

### Q5. What is the difference between const, let, and var in JavaScript?
**Answer:** var is function-scoped; let and const are block-scoped. const variables cannot be reassigned.
