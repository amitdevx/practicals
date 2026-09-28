# Slip 16 — Foundation of AI & ML Solution Guide

## Question 1: Depth Limited Search (DLS) [10 Marks]

### Problem Statement
Write a program to implement Depth Limited Search (DLS).

### Concept & Algorithm
DFS executed with a predefined depth cutoff limit to avoid infinite paths.

### Execution
```bash
python3 Slip_16_Q1.py
```

### Output Preview
```text
Target found within limit or depth boundary respected.
```

---

## Question 2: Backward Chaining Inference Engine [20 Marks]

### Problem Statement
Write a program to implement Backward Chaining inference mechanism.

### Concept & Algorithm
Goal-driven inference establishing subgoals to prove the target hypothesis.

### Execution
```bash
python3 Slip_16_Q2_OptionA.py
```

### Output Preview
```text
Subgoals investigated and target goal proven.
```

---

#### OR

## Question 2 (Alternative): Comparative Analysis / Alternative ML (Slip 16) [20 Marks]

### Problem Statement
Provide comparative evaluation or alternative machine learning model.

### Concept & Algorithm
Evaluates architectural trade-offs between machine learning paradigms.

### Execution
```bash
python3 Slip_16_Q2_OptionB.py
```

### Output Preview
```text
Evaluation completed.
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
