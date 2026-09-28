# Slip 27 — Core Java and Web Technology-I Solution Guide

## Question 1: Person Class with 'this' Keyword [15 Marks]

### Problem Statement
Write a program to define class Person (personname, aadharno, panno). Accept and display 5 objects using this keyword.

### Concept & Algorithm
Demonstrates variable shadowing resolution and field assignment using 'this.variable = variable'.

### Compilation & Execution
```bash
javac Slip_27_Q1.java
java Slip_27_Q1
```

### Sample Output
```text
Name: Amit Kumar    Aadhar: 1234-5678-9012  PAN: ABCDE1234F
Name: Sneha Joshi   Aadhar: 2345-6789-0123  PAN: BCDEF2345G
```

---

## Question 2: Read, Modify and Update JSON File in Node.js [15 Marks]

### Problem Statement
Write a Node.js program to read JSON file, modify selected properties, and write updated data back.

### Concept & Design
Reads JSON file, parses with JSON.parse(), updates properties, and writes back formatted with JSON.stringify().

### Compilation & Execution
```bash
node Slip_27_Q2.js
```

### Output Preview / Response
```text
Original Object: { username: 'amit_dev', role: 'Student', active: false }
Updated Object written to file:
{
  "username": "amit_dev",
  "role": "Administrator",
  "active": true
}
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What are the uses of 'this' keyword in Java?
**Answer:** 1. Disambiguate shadowed instance variables. 2. Invoke current class constructors (this()). 3. Pass current object as argument.

### Q2. What does the 3rd argument in JSON.stringify(obj, null, 2) mean?
**Answer:** It specifies the indentation space count for pretty-printing JSON output.

### Q3. What is method chaining using 'this' in Java?
**Answer:** Returning 'this' from setter methods allowing cascading method calls (e.g. obj.setName().setAge()).

### Q4. Why is JSON preferred over XML?
**Answer:** JSON is lighter, faster to parse, and maps directly to native JavaScript data structures.

### Q5. What happens if JSON.parse() receives malformed JSON?
**Answer:** It throws a SyntaxError exception.
