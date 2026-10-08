# Slip 03 — Foundation of AI & ML Solution Guide

## Question 1: BFS Graph Traversal [10 Marks]

### Problem Statement
Write a program to implement BFS traversal for a graph.

### Concept & Algorithm
Level-order traversal visiting all adjacent vertices before descending deeper.

### Execution
```bash
python3 Slip_03_Q1.py
```

### Output Preview
```text
=== BFS Graph Traversal ===
BFS Order starting from V1: V1 -> V2 -> V3 -> V5 -> V4
```

---

## Question 2: Alpha-Beta Pruning Algorithm [20 Marks]

### Problem Statement
Write a program to implement Alpha-Beta Pruning for optimizing the Minimax search process.

### Concept & Algorithm
Prunes subtrees that cannot influence the final minimax decision (when beta <= alpha).

### Execution
```bash
python3 Slip_03_Q2_OptionA.py
```

### Output Preview
```text
=== Alpha-Beta Pruning Simulation ===
[Pruning] Pruned at MIN node
[Pruning] Pruned at MIN node
Optimal Game Value at Root: 3
```

---

#### OR

## Question 2 (Alternative): Propositional Logic Truth Table [20 Marks]

### Problem Statement
Write a program to implement Propositional Logic and evaluate logical expressions using operators such as AND, OR, and NOT.

### Concept & Algorithm
Constructs truth tables for logical connectives: conjunction (AND), disjunction (OR), and negation (NOT).

### Execution
```bash
python3 Slip_03_Q2_OptionB.py
```

### Output Preview
```text
=== Propositional Logic Evaluator ===
P	Q	NOT P	P AND Q	P OR Q
-------------------------------------------------------
True	True	False	True	True
True	False	False	False	True
False	True	True	False	True
False	False	True	False	False
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is Alpha and Beta in Alpha-Beta pruning?
**Answer:** Alpha is the best value achieved so far for MAX; Beta is the best value achieved so far for MIN.

### Q2. Does Alpha-Beta pruning change the final minimax value?
**Answer:** No, it returns the exact same minimax value but evaluates fewer nodes.

### Q3. What is material implication (P -> Q)?
**Answer:** True in all cases except when P is True and Q is False ((not P) or Q).

### Q4. What is a tautology?
**Answer:** A propositional statement that evaluates to True under every possible truth assignment.

### Q5. What is BFS completeness?
**Answer:** BFS is complete if the branching factor b is finite, meaning it will always find a solution if one exists.
