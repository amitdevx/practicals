# Slip 08 — Foundation of AI & ML Solution Guide

## Question 1: A* Search Algorithm [10 Marks]

### Problem Statement
Write a program to implement A* Search Algorithm to find shortest path.

### Concept & Algorithm
Combines Dijkstra's algorithm and Best-First Search with heuristic evaluation.

### Execution
```bash
python3 Slip_08_Q1.py
```

### Output Preview
```text
Optimal Path: S -> A -> C -> G
Cost: 6
```

---

## Question 2: Machine Learning Model Implementation (Slip 08) [20 Marks]

### Problem Statement
Implement machine learning / neural network model for prediction.

### Concept & Algorithm
Supervised learning training and prediction pipeline.

### Execution
```bash
python3 Slip_08_Q2_OptionA.py
```

### Output Preview
```text
Model fitted and output predicted.
```

---

#### OR

## Question 2 (Alternative): Rule-Based Expert System [20 Marks]

### Problem Statement
Write a program to design a Rule-Based Expert System for decision-making.

### Concept & Algorithm
Rule engine evaluating conditional domain knowledge to diagnose conditions.

### Execution
```bash
python3 Slip_08_Q2_OptionB.py
```

### Output Preview
```text
Diagnosis: Common Viral Flu
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the difference between informed and uninformed search?
**Answer:** Uninformed search (BFS, DFS) has no knowledge of how close a state is to the goal; Informed search (A*, Best-First) uses heuristic functions to guide search.

### Q2. What is the difference between Forward Chaining and Backward Chaining?
**Answer:** Forward Chaining is data-driven, starting from known facts to infer new conclusions; Backward Chaining is goal-driven, starting from a goal to verify supporting facts.

### Q3. What is a Support Vector Machine (SVM)?
**Answer:** A supervised algorithm that finds the optimal hyperplane that maximizes the margin between classes.

### Q4. What is the Kernel Trick in SVM?
**Answer:** A method of mapping input data into higher-dimensional feature spaces to make non-linearly separable data linearly separable without computing explicit coordinates.

### Q5. What is an activation function in Neural Networks?
**Answer:** A mathematical function (e.g. ReLU, Sigmoid, Tanh) applied to a neuron's weighted sum to introduce non-linearity into the network.
