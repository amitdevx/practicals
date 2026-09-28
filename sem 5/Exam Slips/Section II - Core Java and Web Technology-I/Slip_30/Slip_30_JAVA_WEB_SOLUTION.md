# Slip 30 — Core Java and Web Technology-I Solution Guide

## Question 1: MyNumber Class with Command-Line Arguments [15 Marks]

### Problem Statement
Define class MyNumber with private int. Default constructor (0), parameterized constructor. Methods isNegative, isPositive, isOdd, isEven. Use CLI args.

### Concept & Algorithm
Implements number property methods and parses Integer.parseInt(args[0]) from command line.

### Compilation & Execution
```bash
javac Slip_30_Q1.java
java Slip_30_Q1
```

### Sample Output
```text
Number: 25
isPositive: true
isNegative: false
isEven:     false
isOdd:      true
```

---

## Question 2: Mini File Management CLI Application in Node.js [15 Marks]

### Problem Statement
Create a Node.js mini file-management application using fs and path to create, read, update, delete files.

### Concept & Design
Implements unified file CRUD operations with status logging and cleanup.

### Compilation & Execution
```bash
node Slip_30_Q2.js
```

### Output Preview / Response
```text
[+] Created 'cli_test.txt'.
[+] Appended content to 'cli_test.txt'.
--- Content of 'cli_test.txt' ---
Hello Node CLI!
Second Line added.
[+] Deleted 'cli_test.txt'.
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. How do you pass and read command-line arguments in Java?
**Answer:** Through the String[] args array parameter in the main() method.

### Q2. What happens if you access args[0] when no command-line arguments were passed?
**Answer:** It throws java.lang.ArrayIndexOutOfBoundsException.

### Q3. What is process.argv in Node.js?
**Answer:** An array containing command-line arguments passed when launching the Node.js process.

### Q4. Why are instance variables usually declared as private in Java?
**Answer:** To achieve data encapsulation and prevent unauthorized or uncontrolled external modification.

### Q5. What is the difference between Integer.parseInt() and Integer.valueOf()?
**Answer:** parseInt() returns a primitive int; valueOf() returns an Integer object wrapper (often cached).
