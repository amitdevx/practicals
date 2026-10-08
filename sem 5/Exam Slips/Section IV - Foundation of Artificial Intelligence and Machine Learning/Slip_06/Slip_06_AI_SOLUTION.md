# Slip 06 — Foundation of AI & ML Solution Guide

## Question 1: DFS Traversal for a graph (Slip 06) [10 Marks]

### Problem Statement
Write a program to implement DFS traversal for a graph.

### Concept & Algorithm
Depth-First Search (DFS) algorithm exploring node connectivity systematically until exhaustion, typically using recursion (call stack).

### Execution
```bash
python3 Slip_06_Q1.py
```

### Output Preview
```text
DFS Traversal starting from A:
A B D E F C 
```

---

## Question 2: Non-Linear Support Vector Machine (SVM) (Slip 06) [20 Marks]

### Problem Statement
Write a program to implement a Non-Linear Support Vector Machine (SVM) using the Radial Basis Function (RBF) Kernel.
Input Data : X = [ [1, 2], [2, 3],[5, 5] ] 
Class Labels : y = [0, 0, 1] 
Test Input : [4, 4]

### Concept & Algorithm
SVM classifier training with non-linear RBF kernel to handle complex datasets boundaries.

### Execution
```bash
python3 Slip_06_Q2_OptionA.py
```

### Output Preview
```text
Input Data (X): [[1, 2], [2, 3], [5, 5]]
Class Labels (y): [0, 0, 1]
Test Input: [[4, 4]]
Predicted Class: 1
```

---

#### OR

## Question 2 (Alternative): Basic Artificial Neural Network (ANN) (Slip 06) [20 Marks]

### Problem Statement
Write a program to implement a Basic Artificial Neural Network (ANN) for predicting outputs from input data as given below. Use different values for the hyperparameters for the learning rate and number of epochs. Find the ideal value for learning rate and # of epochs.
Learning rate: 0.1, and number of epoch = 20 (initially).
Input_vectors = [ [3, 1.5], [2, 1], [4, 1.5], [3, 4], [3.5, 0.5], [2, 0.5], [5.5, 1], [1, 1] ] and targets = [0, 1, 0, 1, 0, 1, 1, 0]

### Concept & Algorithm
Trains a multi-layer perceptron (ANN) over provided inputs, systematically evaluating over varying hyperparameters (epochs, learning rates).

### Execution
```bash
python3 Slip_06_Q2_OptionB.py
```

### Output Preview
```text
Evaluating Basic ANN with different hyperparameters:

LR: 0.01, Epochs: 20   -> Accuracy: 0.50
LR: 0.01, Epochs: 100  -> Accuracy: 0.75
LR: 0.01, Epochs: 500  -> Accuracy: 0.75
...
Ideal Hyperparameters found:
Learning Rate: 0.01, Epochs: 100
Best Accuracy: 0.75
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
