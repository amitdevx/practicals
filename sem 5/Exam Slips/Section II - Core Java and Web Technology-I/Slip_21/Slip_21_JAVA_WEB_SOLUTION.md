# Slip 21 — Core Java and Web Technology-I Solution Guide

## Question 1: College and Department Hierarchy [15 Marks]

### Problem Statement
Create parent class College (cno, cname, caddr) and derived class Department (dno, dname).

### Concept & Algorithm
Demonstrates single inheritance, parameterized constructor chaining with super, and member access.

### Compilation & Execution
```bash
javac Slip_21_Q1.java
java Slip_21_Q1
```

### Sample Output
```text
College No:   101
College Name: Modern College
Address:      Shivajinagar, Pune
Dept No:      1
Dept Name:    Computer Science
```

---

## Question 2: Node.js Path Module Operations [15 Marks]

### Problem Statement
Write a Node.js program using path module to perform join, resolve and extract file info.

### Concept & Design
Uses path.join(), path.resolve(), path.dirname(), path.basename(), and path.extname().

### Compilation & Execution
```bash
node Slip_21_Q2.js
```

### Output Preview / Response
```text
Joined Path:    /root/projects/node_app/index.js
Directory Name: /home/user/docs
Base Name:      file.txt
Extension:      .txt
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the difference between path.join() and path.resolve()?
**Answer:** path.join() simply concatenates path segments; path.resolve() resolves a sequence of paths into an absolute path from the current working directory.

### Q2. What is the role of super in inheritance?
**Answer:** It calls the constructor of the parent class and allows access to overridden parent methods.

### Q3. What is path.extname() used for?
**Answer:** Returns the file extension, including the leading dot (e.g. '.txt').

### Q4. Can a subclass access private members of a superclass directly?
**Answer:** No, private members can only be accessed via public/protected getter and setter methods.

### Q5. What is __dirname in Node.js?
**Answer:** The absolute directory name of the currently executing JavaScript file.
