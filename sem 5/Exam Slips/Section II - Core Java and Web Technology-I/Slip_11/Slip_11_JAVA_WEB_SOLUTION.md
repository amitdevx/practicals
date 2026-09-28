# Slip 11 — Core Java and Web Technology-I Solution Guide

## Question 1: Vehicle Inheritance Hierarchy [15 Marks]

### Problem Statement
Create super class Vehicle (Company, price). Derive LightMotorVehicle (mileage) and HeavyMotorVehicle (capacity_in_tons).

### Concept & Algorithm
Uses single inheritance with constructor chaining using super().

### Compilation & Execution
```bash
javac Slip_11_Q1.java
java Slip_11_Q1
```

### Sample Output
```text
LMV -> Company: Maruti Suzuki, Price: ₹750000.0, Mileage: 22.5 km/l
HMV -> Company: Tata Motors, Price: ₹2800000.0, Capacity: 16.0 tons
```

---

## Question 2: Calculate Total and Average with Arrow Function [15 Marks]

### Problem Statement
Write a JavaScript program using an arrow function to calculate total and average marks of three subjects.

### Concept & Design
Uses arrow function returning structured calculation object, printed via template literals.

### Compilation & Execution
```bash
node Slip_11_Q2.js
```

### Output Preview / Response
```text
Total Marks     : 253
Average Marks   : 84.33
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is inheritance in Java?
**Answer:** A mechanism where one class acquires the properties and behaviors of another parent class.

### Q2. Why does Java not support multiple inheritance with classes?
**Answer:** To prevent ambiguity known as the 'Diamond Problem'; interfaces are used instead.

### Q3. What is object destructuring in JavaScript?
**Answer:** An ES6 feature that unpacks properties from objects into distinct variables.

### Q4. What is method overriding in Java?
**Answer:** Providing a specific implementation of a method in a subclass that is already defined in its superclass.

### Q5. What is the use of super()?
**Answer:** To invoke the immediate parent class constructor.
