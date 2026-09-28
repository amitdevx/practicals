# Slip 23 — Core Java and Web Technology-I Solution Guide

## Question 1: Multilevel Inheritance: Continent-Country-State [15 Marks]

### Problem Statement
Multilevel inheritance: Country inherited from Continent, State inherited from Country. Display place, State, Country, Continent.

### Concept & Algorithm
Demonstrates 3-tier multilevel inheritance chaining using super() calls.

### Compilation & Execution
```bash
javac Slip_23_Q1.java
java Slip_23_Q1
```

### Sample Output
```text
Place:     Pune
State:     Maharashtra
Country:   India
Continent: Asia
```

---

## Question 2: Node.js fs: Write, Read, Append, and Delete [15 Marks]

### Problem Statement
Write a Node.js program to create, write, read and append data to a file using the fs module.

### Concept & Design
Uses fs.writeFileSync, fs.appendFileSync, fs.readFileSync, and fs.unlinkSync.

### Compilation & Execution
```bash
node Slip_23_Q2.js
```

### Output Preview / Response
```text
[+] Created and wrote to file.
[+] Appended data to file.
--- Current File Contents ---
Initial Line 1.
Appended Line 2.
[+] File deleted.
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is multilevel inheritance?
**Answer:** A chain of inheritance where a derived class inherits from another derived class (A -> B -> C).

### Q2. What is the difference between appendFile and writeFile in Node.js?
**Answer:** writeFile overwrites existing content; appendFile appends data to the end of the file.

### Q3. What encoding is commonly specified when reading text files with fs.readFile?
**Answer:** 'utf8'.

### Q4. Can a class inherit from more than one class in Java?
**Answer:** No, Java supports single class inheritance only.

### Q5. What is the Object class in Java?
**Answer:** The root class of all Java classes; every class implicitly inherits from Object.
