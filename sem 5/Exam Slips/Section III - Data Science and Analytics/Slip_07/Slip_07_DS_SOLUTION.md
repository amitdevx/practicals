# Slip 07 — Data Science and Analytics Solution Guide

## Question 1: Feature Scaling & Distribution Plot [10 Marks]

### Problem Statement
Generate random data, apply scaling and plot distributions.

### Concept & Methodology
Demonstrates how StandardScaler or MinMaxScaler changes distribution ranges without changing shape.

### Execution
```bash
python3 Slip_07_Q1.py
```

### Output Preview
```text
[+] Distribution plot saved.
```

---

## Question 2: Decision Tree Classifier on Iris Dataset [20 Marks]

### Problem Statement
Train a Decision Tree Classifier on the Iris dataset and output accuracy.

### Concept & Machine Learning Algorithm
Decision Tree recursively splits data based on feature conditions to maximize information gain/Gini impurity.

### Execution
```bash
python3 Slip_07_Q2_OptionA.py
```

### Output Preview
```text
=== Decision Tree Classifier on Iris Dataset ===
Accuracy: 1.0
Classification Report: ...
```

---

#### OR

## Question 2 (Alternative): Decision Tree Regressor Model [20 Marks]

### Problem Statement
Apply Decision Tree Regression to predict continuous targets for a non-linear dataset.

### Concept & Algorithm
Regression trees predict continuous variables by splitting the dataset into intervals and outputting the average target value for each interval.

### Execution
```bash
python3 Slip_07_Q2_OptionB.py
```

### Output Preview
```text
=== Decision Tree Regressor Model ===
R2 Score: 0.95...
Mean Squared Error: 0.02...
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the difference between R2 score and MSE?
**Answer:** MSE measures average squared prediction error (lower is better); R2 score measures proportion of explained variance from 0 to 1 (higher is better).

### Q2. What is data normalization (Min-Max Scaling)?
**Answer:** Rescaling feature values into the range [0, 1] using (x - min) / (max - min).

### Q3. What is K-Fold Cross Validation?
**Answer:** A resampling method dividing the dataset into K folds, training on K-1 folds and testing on the remaining fold K times.

### Q4. What is the curse of dimensionality?
**Answer:** The phenomenon where data becomes sparse in high-dimensional feature spaces, degrading distance-based algorithm performance.

### Q5. What library in Python is used for statistical machine learning?
**Answer:** Scikit-Learn (sklearn).
