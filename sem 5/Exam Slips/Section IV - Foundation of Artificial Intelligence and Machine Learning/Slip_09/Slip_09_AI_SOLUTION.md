# Slip 09 — Foundation of AI & ML Solution Guide

## Question 1: Hill Climbing Optimization Algorithm [10 Marks]

### Problem Statement
Write a program to demonstrate Hill Climbing Algorithm for finding maximum of objective function F(x) = -x^2 + 4x.

### Concept & Algorithm
Iterative local search moving in the direction of increasing value until a peak is reached.

### Execution
```bash
python3 Slip_09_Q1.py
```

### Output Preview
```text
Maximum found at x = 2.0000 with F(x) = 4.0000
```

---

## Question 2: Forward Chaining Inference Engine [20 Marks]

### Problem Statement
Write a program to implement Forward Chaining inference mechanism.

### Concept & Algorithm
Data-driven inference firing rules whose premises are satisfied by existing facts.

### Execution
```bash
python3 Slip_09_Q2_OptionA.py
```

### Output Preview
```text
Rules fired and goal proven.
```

---

#### OR

## Question 2 (Alternative): Decision Tree Classifier (Slip 09) [20 Marks]

### Problem Statement
Write a program to implement the Decision Tree Classifier for a classification problem using the provided Diabetes dataset. Split the dataset into 70:30 (train:test). Evaluate using accuracy_score() and optimize by tuning criterion (entropy) and max_depth (2, 3, 4).

### Concept & Algorithm
A supervised learning method that splits data based on feature conditions to maximize information gain (entropy) or minimize Gini impurity, creating a tree-like model of decisions.

### Execution
```bash
python3 Slip_09_Q2_OptionB.py
```

### Output Preview
```text
Accuracy (Default): 1.0000
Accuracy (Entropy, max_depth=2): 1.0000
Accuracy (Entropy, max_depth=3): 1.0000
Accuracy (Entropy, max_depth=4): 1.0000
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
