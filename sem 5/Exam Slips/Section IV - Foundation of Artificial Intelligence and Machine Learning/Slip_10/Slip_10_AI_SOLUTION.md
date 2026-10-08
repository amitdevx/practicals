# Slip 10 — Foundation of AI & ML Solution Guide

## Question 1: Means-End Analysis (Goal-Driven Planning) [10 Marks]

### Problem Statement
Write a program to implement Means-End Analysis for solving a goal-based problem.

### Concept & Algorithm
Means-End Analysis attempts to reduce the difference between the current state and the goal state by finding and applying suitable operators. If the operator's preconditions are not met, they are set as subgoals.

### Execution
```bash
python3 Slip_10_Q1.py
```

### Output Preview
```text
Initial State: {'Has_Money'}
Goal State:    {'At_Destination'}
Subgoal needed: Has_Fuel
[Applied Operator] Fill_Fuel
Subgoal needed: Has_Car
[Applied Operator] Buy_Car
[Applied Operator] Drive_Car
Current State: {'Has_Car', 'At_Destination', 'Has_Fuel', 'Has_Money'}
Solution Plan: Fill_Fuel -> Buy_Car -> Drive_Car
```

---

## Question 2: Random Forest Classifier on Student Dataset [20 Marks]

### Problem Statement
Write a program to implement the Random Forest Classifier for classification tasks.

### Concept & Algorithm
Random Forest is an ensemble learning method for classification that operates by constructing a multitude of decision trees at training time and outputting the mode of the classes of the individual trees.

### Execution
```bash
python3 Slip_10_Q2_OptionA.py
```

### Output Preview
```text
=== Random Forest Classifier ===
Prediction for [Study:6h, Attend:80%, Score:75]: Pass
```

---

#### OR

## Question 2 (Alternative): SVM Pipeline with StandardScaler and LinearSVC [20 Marks]

### Problem Statement
Write a program to demonstrate hyperplane classification using a Support Vector Machine on the iris dataset. Create a Pipeline containing a StandardScaler and a LinearSVC (with c =1 and use hinge loss).

### Concept & Algorithm
The scikit-learn Pipeline standardizes features by removing the mean and scaling to unit variance (StandardScaler) and then performs linear support vector classification (LinearSVC).

### Execution
```bash
python3 Slip_10_Q2_OptionB.py
```

### Output Preview
```text
=== SVM Pipeline on Iris Dataset ===
              precision    recall  f1-score   support
...
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
