# Slip 13 — Foundation of AI & ML Solution Guide

## Question 1: Water Jug Problem using BFS [10 Marks]

### Problem Statement
Write a program to solve the Water Jug Problem using BFS.

### Concept & Algorithm
Explores state transitions using breadth-first search queue.

### Execution
```bash
python3 Slip_13_Q1.py
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

## Question 2: Voting Classifier Ensemble [20 Marks]

### Problem Statement
Write a program to implement a Voting Classifier by combining multiple machine learning models such as Logistic Regression and Decision Tree.

### Concept & Algorithm
Combines Logistic Regression and Decision Tree via hard voting classifier.

### Execution
```bash
python3 Slip_13_Q2_OptionA.py
```

### Output Preview
```text
=== Voting Classifier Ensemble ===
Ensemble Accuracy: 1.0
```

---

#### OR

## Question 2 (Alternative): Knowledge Graph [20 Marks]

### Problem Statement
Write a program to develop a simple Knowledge Graph representing relationships among entities.

### Concept & Algorithm
Represents entities and relationships using a dictionary-based graph structure.

### Execution
```bash
python3 Slip_13_Q2_OptionB.py
```

### Output Preview
```text
=== Simple Knowledge Graph ===
Alice --[knows]--> Bob
Alice --[is interested in]--> Artificial Intelligence
Bob --[studies]--> Computer Science
Computer Science --[includes]--> Artificial Intelligence
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
