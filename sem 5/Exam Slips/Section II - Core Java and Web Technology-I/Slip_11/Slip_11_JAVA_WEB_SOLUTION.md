# Slip 11 — Core Java and Web Technology-I Solution Guide

## Question 1: Vehicle Inheritance Hierarchy [15 Marks]

### Problem Statement
Write a program to create a super class Vehicle having members Company and price. Derive two different classes LightMotorVehicle (mileage) and HeavyMotorVehicle (capacity_in_tons). Accept the information for "n" vehicles and display the information in appropriate form. While taking data, ask user about the type of vehicle first.

### Concept & Algorithm
Uses single inheritance with constructor chaining using `super()`. Reads "n" inputs via standard I/O (Scanner) and dynamically instantiates subclasses based on the requested vehicle type.

### Compilation & Execution
```bash
javac Slip_11_Q1.java
java Slip_11_Q1
```

### Sample Output
```text
Enter number of vehicles (n): 2
Select Vehicle Type for Vehicle 1: (1) Light Motor Vehicle (2) Heavy Motor Vehicle
1
Enter Company: Maruti Suzuki
Enter Price: 750000
Enter Mileage: 22.5
Select Vehicle Type for Vehicle 2: (1) Light Motor Vehicle (2) Heavy Motor Vehicle
2
Enter Company: Tata Motors
Enter Price: 2800000
Enter Capacity in Tons: 16.0

--- Vehicle Information ---
LMV -> Company: Maruti Suzuki, Price: ₹750000.0, Mileage: 22.5 km/l
HMV -> Company: Tata Motors, Price: ₹2800000.0, Capacity: 16.0 tons
```

---

## Question 2: Calculate Total and Average with Arrow Function [15 Marks]

### Problem Statement
Write a JavaScript program using an arrow function to calculate the total and average marks of three subjects. Display the result using template literals.

### Concept & Design
Uses arrow function returning structured calculation object, printed via template literals.

### Compilation & Execution
```bash
node Slip_11_Q2.js
```

### Output Preview / Response
```text
Subject 1 Marks : 78
Subject 2 Marks : 85
Subject 3 Marks : 90
-------------------------
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
