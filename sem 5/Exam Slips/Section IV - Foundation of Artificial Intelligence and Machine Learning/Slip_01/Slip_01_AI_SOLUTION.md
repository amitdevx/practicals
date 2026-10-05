# Slip 01 — Foundation of AI & ML Solution Guide

## Question 1: Breadth-First Search (BFS) for State-Space Problem [10 Marks]

### Problem Statement
Write a program to implement Breadth First Search for solving a state-space search problem.

### Concept & Algorithm
BFS explores the shallowest unexpanded nodes first using a FIFO queue; guarantees optimal solution for uniform step costs.

### Execution
```bash
python3 Slip_01_Q1.py
```

### Output Preview
```text
BFS Order: V1 -> V2 -> V3 -> V5 -> V4
```

---

## Question 2: A* Search Algorithm [20 Marks]

### Problem Statement
Write a program to implement A* Search Algorithm to find shortest path between source and destination.

### Concept & Algorithm
A* evaluates nodes by f(n) = g(n) + h(n), combining actual cost g(n) and admissible heuristic h(n).

### Execution
```bash
python3 Slip_01_Q2_OptionA.py
```

### Output Preview
```text
Optimal Path: A -> B -> D -> G
Total Path Cost: 6
```

---

#### OR

## Question 2 (Alternative): Map Coloring Problem using CSP [20 Marks]

### Problem Statement
Write a program to solve Map Coloring Problem using Constraint Satisfaction Problem (CSP) approach.

### Concept & Algorithm
Backtracking search assigns domain colors to regions such that no two adjacent regions share the same color.

### Execution
```bash
python3 Slip_01_Q2_OptionB.py
```

### Output Preview
```text
Map Coloring Solution: WA: Red, NT: Green, SA: Blue...
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is heuristic function in AI?
**Answer:** A function that estimates the cost or distance from the current state to the nearest goal state.

### Q2. Why must a heuristic be admissible in A*?
**Answer:** An admissible heuristic never overestimates the true cost to reach the goal, guaranteeing A* finds the optimal path.

### Q3. What is the time and space complexity of BFS?
**Answer:** Time: O(b^d), Space: O(b^d), where b is branching factor and d is solution depth.

### Q4. What is Constraint Satisfaction Problem (CSP)?
**Answer:** A problem defined by variables, domains of possible values, and a set of constraints restricting allowable combinations.

### Q5. What is forward checking in CSP?
**Answer:** A technique that keeps track of remaining valid domain values for unassigned variables to prune failure branches early.
