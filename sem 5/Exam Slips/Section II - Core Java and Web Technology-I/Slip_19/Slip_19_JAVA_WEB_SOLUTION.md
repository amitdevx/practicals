# Slip 19 — Core Java and Web Technology-I Solution Guide

## Question 1: File Character, Word, and Line Counter [15 Marks]

### Problem Statement
Write a Java program to accept file name and count characters, words, and lines.

### Concept & Algorithm
Reads text line by line, accumulates line count, character length, and splits by regex \s+ for words.

### Compilation & Execution
```bash
javac Slip_19_Q1.java
java Slip_19_Q1
```

### Sample Output
```text
Enter file name: sample.txt
Total Characters: 78
Total Words:      11
Total Lines:      3
```

---

## Question 2: Async/Await User Authentication Simulation [15 Marks]

### Problem Statement
Write a JavaScript program using async/await to simulate user login with try/catch error handling.

### Concept & Design
Uses Promise inside async function, resolved on valid credentials and rejected on invalid inputs.

### Compilation & Execution
```bash
node Slip_19_Q2.js
```

### Output Preview / Response
```text
[+] Success: Login Successful! Welcome to the dashboard.
[-] Error: Invalid Username or Password!
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What does async/await do in JavaScript?
**Answer:** It provides syntactic sugar over Promises, making asynchronous code look and behave like synchronous code.

### Q2. What happens when an error is thrown inside an async function?
**Answer:** It returns a rejected Promise, which can be captured by a try...catch block.

### Q3. How does Java regular expression '\s+' split words?
**Answer:** It matches one or more consecutive whitespace characters (spaces, tabs, newlines).

### Q4. What is Promise in JavaScript?
**Answer:** An object representing the eventual completion or failure of an asynchronous operation.

### Q5. What are the three states of a Promise?
**Answer:** Pending, Fulfilled, Rejected.
