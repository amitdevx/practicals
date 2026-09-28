# Slip 17 — Core Java and Web Technology-I Solution Guide

## Question 1: Key Combination Background Color Switcher [15 Marks]

### Problem Statement
Write a GUI application that changes background color based on combination of keys pressed (e.g. Ctrl+Alt+O for orange).

### Concept & Algorithm
Implements KeyListener interface and checks KeyEvent modifiers (isControlDown(), isAltDown()).

### Compilation & Execution
```bash
javac Slip_17_Q1.java
java Slip_17_Q1
```

### Sample Output
```text
[GUI window changes background color when key combination is triggered]
```

---

## Question 2: JavaScript Module Export and Import [15 Marks]

### Problem Statement
Create a JavaScript module containing arithmetic operations, export functions and import them.

### Concept & Design
Implements modular JavaScript patterns exporting utility arithmetic functions.

### Compilation & Execution
```bash
node Slip_17_Q2.js
```

### Output Preview / Response
```text
Add(15, 5) : 20
Multiply(15, 5) : 75
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is KeyListener in Java?
**Answer:** An interface that receives keyboard events (keyPressed, keyReleased, keyTyped).

### Q2. How do you detect if Ctrl key is pressed during a KeyEvent?
**Answer:** Using e.isControlDown().

### Q3. What are CommonJS modules vs ES6 modules?
**Answer:** CommonJS uses require() and module.exports (synchronous, Node default); ES6 uses import and export (static, asynchronous).

### Q4. What is setFocusable(true) in Swing?
**Answer:** Ensures that a component can gain keyboard focus to receive KeyEvents.

### Q5. What is module bundler in modern web development?
**Answer:** A tool (like Webpack, Vite) that packages modular JavaScript files into single or optimized bundles for browsers.
