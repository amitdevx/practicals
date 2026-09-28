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
Step 0: Jug A = 0L, Jug B = 0L
Step 1: Jug A = 4L, Jug B = 0L
... Target reached!
```

---

## Question 2: Naive Bayes Classification [20 Marks]

### Problem Statement
Write a program to implement the Naive Bayes Classifier.

### Concept & Algorithm
Applies Bayes Theorem with the naive assumption of conditional feature independence given class label.

### Execution
```bash
python3 Slip_02_Q2_OptionA.py
```

### Output Preview
```text
Accuracy: 0.9778
```

---

#### OR

## Question 2 (Alternative): Minimax Algorithm for Two-Player Game [20 Marks]

### Problem Statement
Write a program to implement a Game Tree using Minimax Algorithm.

### Concept & Algorithm
Recursive adversarial search maximizing payoff for MAX player and minimizing payoff for MIN opponent.

### Execution
```bash
python3 Slip_02_Q2_OptionB.py
```

### Output Preview
```text
Optimal Value at Root (MAX): 5
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is Bayes' Theorem?
**Answer:** P(A|B) = P(B|A) * P(A) / P(B).

### Q2. Why is Naive Bayes called 'naive'?
**Answer:** Because it assumes that all input features are mutually independent given the class label.

### Q3. What is the zero-frequency problem in Naive Bayes and how is it resolved?
**Answer:** If a category never appears with a class, its probability becomes zero; resolved using Laplace smoothing (+1).

### Q4. What is the state space in Water Jug problem?
**Answer:** Pairs of integers (x, y) representing current water volumes in Jug A and Jug B.

### Q5. What is a zero-sum game?
**Answer:** A mathematical representation where one player's gain exactly equals the other player's loss.
