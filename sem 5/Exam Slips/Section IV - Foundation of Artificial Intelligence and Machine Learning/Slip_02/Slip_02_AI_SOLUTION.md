# Slip 02 — Foundation of AI & ML Solution Guide

## Question 1: Water Jug Problem using BFS [10 Marks]

### Problem Statement
Write a program to solve the Water Jug Problem using BFS.

### Concept & Algorithm
State space representation (jugA, jugB) exploring valid operations (fill, empty, pour) using a FIFO queue.

### Execution
```bash
python3 Slip_02_Q1.py
```

### Output Preview
```text
=== Water Jug Problem (4L, 3L -> Target 2L) ===
Step 0: Jug A = 0L, Jug B = 0L
Step 1: Jug A = 0L, Jug B = 3L
Step 2: Jug A = 3L, Jug B = 0L
Step 3: Jug A = 3L, Jug B = 3L
Step 4: Jug A = 4L, Jug B = 2L
```

---

## Question 2: Backtracking Algorithm for CSP [20 Marks]

### Problem Statement
Write a program to implement the Backtracking Algorithm for solving a constraint satisfaction problem.

### Concept & Algorithm
Uses depth-first search with backtracking to assign values (colors) to variables (nodes) ensuring no constraints (adjacent nodes having the same color) are violated.

### Execution
```bash
python3 Slip_02_Q2_OptionA.py
```

### Output Preview
```text
=== Constraint Satisfaction Problem (Graph Coloring) ===
Solution found:
WA: Red
NT: Green
SA: Blue
Q: Red
NSW: Green
V: Red
T: Red
```

---

#### OR

## Question 2 (Alternative): Game Tree Representation (Minimax) [20 Marks]

### Problem Statement
Write a program to implement a Game Tree Representation for a two-player game.

### Concept & Algorithm
Recursive adversarial search (Minimax) maximizing payoff for the MAX player and minimizing payoff for the MIN opponent traversing the game tree.

### Execution
```bash
python3 Slip_02_Q2_OptionB.py
```

### Output Preview
```text
=== Minimax Algorithm for Two-Player Game ===
Terminal Node Scores: [3, 5, 2, 9, 12, 5, 23, 23]
Optimal Value at Root (MAX): 12
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is a Constraint Satisfaction Problem (CSP)?
**Answer:** A problem defined by a set of variables, domains for the variables, and constraints specifying allowable combinations of values.

### Q2. What is backtracking in CSP?
**Answer:** A systematic way to iterate through possible assignments by assigning a value, checking constraints, and undoing the assignment (backtracking) if a violation occurs.

### Q3. What is the Minimax algorithm?
**Answer:** A decision rule used in artificial intelligence for minimizing the possible loss for a worst-case scenario.

### Q4. What is the state space in the Water Jug problem?
**Answer:** Pairs of integers (x, y) representing current water volumes in Jug A and Jug B.

### Q5. What is a zero-sum game?
**Answer:** A mathematical representation where one player's gain exactly equals the other player's loss.
