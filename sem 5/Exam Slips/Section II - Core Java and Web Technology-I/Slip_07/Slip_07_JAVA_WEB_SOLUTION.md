# Slip 07 — Core Java and Web Technology-I Solution Guide

## Question 1: Driver Class Implementation [15 Marks]

### Problem Statement
Write a class Driver with attributes license_no, name, address and age. Initialize values through the parameterized constructor. If age of Driver is less than 18 then user-defined exception should be generated —Age is below 18 years—.

### Concept & Algorithm
1. Create user-defined exception `InvalidAgeException`.
2. Encapsulate driver properties with parameterized constructor. 
3. Check if age < 18, throw custom exception if true.
4. Catch and display the exception message in main class.

### Compilation & Execution
```bash
javac Slip_07_Q1.java
java Slip_07_Q1
```

### Sample Output
```text
--- Driver 1 Details ---
Driver Name: Amit Patil
License No:  MH12-20230045
Address:     Shivajinagar, Pune
Age:         28

--- Driver 2 Details ---
Exception: Age is below 18 years
```

---

## Question 2: Styled Unordered List of Programming Languages [15 Marks]

### Problem Statement
Create an unordered list of Programming Language names and apply different styles to the first and last list items.(Use :first-child and :last-child).

### Concept & Design
Uses custom list styling with distinct CSS pseudoclass `:first-child` and `:last-child` applying distinct styles.

### Execution
Open `Slip_07_Q2.html` in any standard web browser (Chrome, Firefox, Edge).

### Output Preview / Response
```text
[Styled language items with first and last items differently colored]
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is CSS list-style property?
**Answer:** A shorthand property that sets list-style-type, list-style-position, and list-style-image.

### Q2. What is the default access modifier in Java?
**Answer:** Package-private (default), accessible only within the same package.

### Q3. What is the difference between private and protected in Java?
**Answer:** private is accessible only inside the class; protected is accessible within the package and subclasses.

### Q4. What is CSS specificity?
**Answer:** A system used by browsers to determine which CSS rule applies to an element when multiple rules conflict.

### Q5. What is JVM bytecode?
**Answer:** Intermediate instruction set compiled from Java source code, executable by any platform with a compatible JVM.
