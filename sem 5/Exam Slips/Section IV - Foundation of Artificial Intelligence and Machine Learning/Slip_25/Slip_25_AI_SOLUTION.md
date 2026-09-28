# Slip 25 — Foundation of AI & ML Solution Guide

## Question 1: AO* Search Algorithm on AND-OR Graph [10 Marks]

### Problem Statement
Write a program to implement AO* Algorithm for AND-OR graphs.

### Concept & Algorithm
Finds optimal hyperpaths in AND-OR graphs by updating heuristic node estimates.

### Execution
```bash
python3 Slip_25_Q1.py
```

### Output Preview
```text
AO* Solution Path Cost: 12
```

---

## Question 2: Forward Chaining Inference Engine [20 Marks]

### Problem Statement
Write a program to implement Forward Chaining inference mechanism.

### Concept & Algorithm
Data-driven inference firing rules whose premises are satisfied by existing facts.

### Execution
```bash
python3 Slip_25_Q2_OptionA.py
```

### Output Preview
```text
Rules fired and goal proven.
```

---

#### OR

## Question 2 (Alternative): Comparative Analysis / Alternative ML (Slip 25) [20 Marks]

### Problem Statement
Provide comparative evaluation or alternative machine learning model.

### Concept & Algorithm
Evaluates architectural trade-offs between machine learning paradigms.

### Execution
```bash
python3 Slip_25_Q2_OptionB.py
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
