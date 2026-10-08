# Slip 04 — Foundation of AI & ML Solution Guide

## Question 1: BFS Traversal [10 Marks]

### Problem Statement
Write a program to solve a state-space search problem using BFS. Start Vertex = A

### Concept & Algorithm
Explores layer by layer using a FIFO queue.

### Execution
```bash
python3 Slip_04_Q1.py
```

### Output Preview
```text
=== BFS State-Space Search ===
BFS Order starting from A: A -> B -> C -> D -> E -> F -> G
```

---

## Question 2: Predicate Logic (Option A) [20 Marks]

### Problem Statement
Write a program to implement Predicate Logic using predicates, variables, and quantifier.

### Concept & Algorithm
We define predicates as functions that return a boolean value, and variables over a domain of people. We use `all()` for universal quantifier and `any()` for existential quantifier.

### Execution
```bash
python3 Slip_04_Q2_OptionA.py
```

### Output Preview
```text
=== Predicate Logic ===
Universal Quantifier (∀): Do all students love AI? False
Existential Quantifier (∃): Does any student love AI? True
```

---

#### OR

## Question 2: Gaussian NB Classifier (Option B) [20 Marks]

### Problem Statement
Write a program to implement Gaussian NB classifier with 3 classes on numeric data, use make_blobs to create a dataset X of 200 sample points in 2D Space, 3 clusters and each cluster spread (SD) over 1.5. For testing (Prediction), use the following values to test the Gaussian NB Classifier. Input (Values) : [-2, 5], [0,0], [6, -0.3] Output : [0 1 1].

### Concept & Algorithm
Generates dummy data using `make_blobs` and trains a Gaussian Naive Bayes classifier from `sklearn`. Predicts on given input and prints accuracy.

### Execution
```bash
python3 Slip_04_Q2_OptionB.py
```

### Output Preview
```text
=== Gaussian NB Classifier ===
Input Values:
 [[-2.   5. ]
 [ 0.   0. ]
 [ 6.  -0.3]]
Predicted Output: [0 1 1]
Accuracy Score: 0.9850
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
