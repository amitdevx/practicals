# Slip 10 — Foundation of AI & ML Solution Guide

## Question 1: Means-End Analysis (Goal-Driven Planning) [10 Marks]

### Problem Statement
Write a program to implement Means-End Analysis for solving a goal-based problem.

### Concept & Algorithm
Detects differences between current state and goal state, applying operators to reduce difference.

### Execution
```bash
python3 Slip_10_Q1.py
```

### Output Preview
```text
Operators Applied and Goal Achieved.
```

---

## Question 2: Random Forest Classifier on Student Dataset [20 Marks]

### Problem Statement
Write a program to implement Random Forest Classifier for classification tasks.

### Concept & Algorithm
Ensemble classification aggregating decision tree votes.

### Execution
```bash
python3 Slip_10_Q2_OptionA.py
```

### Output Preview
```text
Prediction: Pass
```

---

#### OR

## Question 2 (Alternative): SVM Pipeline with StandardScaler and LinearSVC [20 Marks]

### Problem Statement
Write program to demonstrate hyperplane classification using SVM on Iris dataset with Pipeline (StandardScaler + LinearSVC).

### Concept & Algorithm
Constructs scikit-learn Pipeline with feature scaling and linear support vector classification.

### Execution
```bash
python3 Slip_10_Q2_OptionB.py
```

### Output Preview
```text
Classification report printed.
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
