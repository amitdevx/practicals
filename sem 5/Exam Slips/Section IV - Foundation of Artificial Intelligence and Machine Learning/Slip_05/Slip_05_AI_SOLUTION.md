# Slip 05 — Foundation of AI & ML Solution Guide

## Question 1: Depth Limited Search (DLS) [10 Marks]

### Problem Statement
Write a program to implement Depth Limited Search (DLS).

### Concept & Algorithm
Depth Limited Search (DLS) is a variant of Depth-First Search (DFS) that limits the maximum depth of the search to a specified cutoff limit. It prevents DFS from wandering down infinite paths.

### Execution
```bash
python3 Slip_05_Q1.py
```

### Output Preview
```text
=== Depth Limited Search (DLS) (Limit: 2, Target: 8) ===
Target '8' NOT found within depth limit 2.
```

---

## Question 2: Bernoulli NB Classifier [20 Marks]

### Problem Statement
Write a program to implement Bernoulli NB classifier with 2 classes on numeric data, use make_classification to create a dataset X of 300 sample points in 2D space with the following parameters : n_features=2, n_informative=2, n_redundant=0, n_classes=2. For testing (Prediction), use the following values to test the Bernoulli NB Classifier.
Input (Values) : [[0, 0], [0, 1], [1, 0], [1, 1]]

### Concept & Algorithm
Bernoulli Naive Bayes algorithm. Uses `make_classification` to generate a binary dataset of 300 points, trains a `BernoulliNB` model from `sklearn.naive_bayes`, and then predicts the class for a given set of test inputs.

### Execution
```bash
python3 Slip_05_Q2_OptionA.py
```

### Output Preview
```text
Test Inputs: [[0, 0], [0, 1], [1, 0], [1, 1]]
Predicted Output: [0, 0, 1, 1]
```

---

#### OR

## Question 2 (Alternative): Support Vector Machine (SVM) [20 Marks]

### Problem Statement
Write a program to implement a Support Vector Machine (SVM) classifier on the Iris dataset. With a given subset of X and y arrays and specific X_test values.

### Concept & Algorithm
Support Vector Machine (SVM). Trains a standard `SVC` model from `sklearn.svm` on the given input arrays, mapping the multi-class dataset, and generates predictions for the requested `X_test` data points.

### Execution
```bash
python3 Slip_05_Q2_OptionB.py
```

### Output Preview
```text
Test Inputs: [[5.2, 3.4, 1.5, 0.2], [6.5, 3.0, 4.6, 1.5], [6.2, 3.0, 5.2, 2.0]]
SVM Predictions: [0, 1, 1]
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
