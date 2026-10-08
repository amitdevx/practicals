# Slip 12 — Foundation of AI & ML Solution Guide

## Question 1: Monkey Banana Problem (BFS) [10 Marks]

### Problem Statement
Write a program to implement Breadth First Search (BFS) for the Monkey Banana Problem.

### Concept & Algorithm
Breadth-First Search (BFS) explores the state space level by level. In the Monkey Banana problem, the state is defined by the monkey's position, the box's position, whether the monkey is on the box, and whether the monkey has the banana. We start at an initial state and apply valid actions (Move, Push, Climb, Grasp) systematically until a state where the monkey has the banana is reached.

### Execution
```bash
python3 Slip_12_Q1.py
```

### Output Preview
```text
=== Monkey Banana Problem (BFS) ===
Solution found:
Step 1: Move to window
Step 2: Push box to center
Step 3: Climb box
Step 4: Grasp banana
```

---

## Question 2: Support Vector Machine (Linear vs RBF) [20 Marks]

### Problem Statement
Write a program or report to compare Linear SVM and Non-Linear SVM (RBF Kernel).
X = [ [1, 2], [2, 3], [3, 1], [4, 2], [5, 5], [6, 6], [7, 4], [8, 5] ]
Y = [0, 0, 0, 0, 1, 1, 1, 1]

### Concept & Algorithm
A Support Vector Machine (SVM) finds the optimal separating hyperplane.
- **Linear Kernel**: Finds a linear boundary, suitable for linearly separable data.
- **RBF (Radial Basis Function) Kernel**: Transforms data into a higher dimension to find a non-linear boundary, suitable for complex datasets.

### Execution
```bash
python3 Slip_12_Q2_OptionA.py
```

### Output Preview
```text
=== SVM Comparison ===
Linear SVM Accuracy: 100.00%
RBF SVM Accuracy: 100.00%
Linear SVM Predictions: [0 0 0 0 1 1 1 1]
RBF SVM Predictions:    [0 0 0 0 1 1 1 1]
Actual Labels:          [0 0 0 0 1 1 1 1]
```

---

#### OR

## Question 2 (Alternative): ANN for Linear Regression [20 Marks]

### Problem Statement
Write a program to implement an Artificial Neural Network (ANN) for a Linear Regression problem.

### Concept & Algorithm
Artificial Neural Networks (ANN) can approximate any continuous function. For linear regression, an ANN with one or more hidden layers is trained to map input variables to continuous output variables using error metrics like Mean Squared Error (MSE).

### Execution
```bash
python3 Slip_12_Q2_OptionB.py
```

### Output Preview
```text
=== ANN for Linear Regression ===
Input X:
 [1 2 3 4 5 6 7 8]
Actual y:
 [ 3  5  7  9 11 13 15 17]
Predicted y:
 [ 3.  5.  7.  9. 11. 13. 15. 17.]
Mean Squared Error: 0.0000
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
