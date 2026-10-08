# Slip 08 — Core Java and Web Technology-I Solution Guide

## Question 1: Abstract Class Shape Hierarchy [15 Marks]

### Problem Statement
Write a program to create an abstract class Shape that contains two integers and an empty method named printArea(). Provide three classes named Rectangle, Triangle and Circle such that each one of the classes extends the class Shape. Each one of the classes contain only the method printArea() that prints the area of the given shape. (use method overriding).

### Concept & Algorithm
Demonstrates abstraction and polymorphism: base abstract class declares abstract `printArea()`, overridden in subclasses.

### Compilation & Execution
```bash
javac Slip_08_Q1.java
java Slip_08_Q1
```

### Sample Output
```text
Area of Rectangle (10 x 5): 50
Area of Triangle (0.5 x 8 x 4): 16.0
Area of Circle (radius 7): 153.93804002589985
```

---

## Question 2: DOM Image and Button Interaction [15 Marks]

### Problem Statement
Create a webpage using JavaScript DOM manipulation and event handling with an image and a button. When the button is clicked, replace the displayed image with another image.

### Concept & Design
Toggles an `<img>` tag's `src` attribute state on button click via `document.getElementById()`.

### Execution
Open `Slip_08_Q2.html` in any standard web browser (Chrome, Firefox, Edge).

### Output Preview / Response
```text
[Image element swaps to a different picture upon button click]
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. Can an abstract class be instantiated directly?
**Answer:** No, an abstract class cannot be instantiated using new; it must be subclassed.

### Q2. What is runtime polymorphism in Java?
**Answer:** Method overriding where the call to an overridden method is resolved at runtime based on object type.

### Q3. What is the super keyword used for?
**Answer:** To refer to the direct parent class object or call the parent constructor.

### Q4. What is event bubbling in DOM?
**Answer:** An event propagation phase where the event starts from the target element and bubbles up to the root.

### Q5. What is document.getElementById()?
**Answer:** A DOM method that returns the element object matching the specified ID string.
