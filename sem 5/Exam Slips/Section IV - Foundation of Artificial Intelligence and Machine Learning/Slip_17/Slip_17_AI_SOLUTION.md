# Slip 17 — Foundation of AI & ML Solution Guide

## Question 1: Best First Search [10 Marks]

### Problem Statement
Write a program to implement the Best First Search Algorithm using heuristic values to find a path from a start node to a goal node.

### Concept & Algorithm
Best First Search is an informed search algorithm that uses an evaluation function \( f(n) = h(n) \), expanding the most promising node chosen according to the heuristic function.

### Execution
```bash
python3 Slip_17_Q1.py
```

### Output Preview
```text
=== Best First Search Algorithm ===
Path found: S -> B -> E -> G
```

---

## Question 2: Propositional Logic [20 Marks]

### Problem Statement
Write a program to implement Propositional Logic and evaluate logical expressions using operators such as AND, OR, and IMPLIES.

### Concept & Algorithm
Logical operators map boolean inputs to boolean outputs. The IMPLIES operator (P -> Q) is logically equivalent to (NOT P OR Q).

### Execution
```bash
python3 Slip_17_Q2_OptionA.py
```

### Output Preview
```text
=== Propositional Logic Evaluation ===
P: True, Q: False
P AND Q: False
P OR Q: True
P IMPLIES Q: False
...
```

---

#### OR

## Question 2 (Alternative): Euclidean Distance [20 Marks]

### Problem Statement
Write a program to calculate and demonstrate the Euclidean Distance between two data points. Inputs: `2 3 4` and `5 7 6`.

### Concept & Algorithm
The Euclidean distance between two points in Euclidean space is the length of the line segment between them, computed using the Pythagorean formula.

### Execution
```bash
python3 Slip_17_Q2_OptionB.py
```

### Output Preview
```text
Input :
Data Point: 2 3 4
Data Point: 5 7 6

Output :
Data Point : [2, 3, 4]
Data Point : [5, 7, 6]
Euclidean Distance = 5.099
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is Best First Search?
**Answer:** It is an informed search algorithm that expands the node that is closest to the goal, as estimated by a heuristic function \( h(n) \).

### Q2. How is IMPLIES implemented in propositional logic?
**Answer:** The implication \( P \implies Q \) is logically equivalent to \( \neg P \lor Q \).

### Q3. What is the formula for Euclidean Distance in 3D?
**Answer:** \( \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2 + (z_2 - z_1)^2} \)
