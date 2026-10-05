# Slip 06 — Data Science and Analytics Solution Guide

## Question 1: Vehicle Engine Size vs Fuel Efficiency Visualization [10 Marks]

### Problem Statement
Create DataFrame containing car model, engine size, fuel efficiency. Plot scatter plot.

### Concept & Methodology
Scatter plots reveal inverse correlation between engine displacement and fuel economy.

### Execution
```bash
python3 Slip_06_Q1.py
```

### Output Preview
```text
[+] Scatter plot saved.
```

---

## Question 2: Multiple Linear Regression for Salary Prediction [20 Marks]

### Problem Statement
Apply Multiple Linear Regression to predict salary based on Years of Experience and Education Level.

### Concept & Machine Learning Algorithm
Supervised machine learning training, validation split, and metric evaluation (R2 Score, MSE).

### Execution
```bash
python3 Slip_06_Q2_OptionA.py
```

### Output Preview
```text
=== Multiple Linear Regression for Salary Prediction ===
R2 Score: -3.8125
Mean Squared Error: 154000000.0
```

---

#### OR

## Question 2 (Alternative): Polynomial Regression Curve Fitting [20 Marks]

### Problem Statement
Apply Polynomial Regression on a non-linear dataset.

### Concept & Algorithm
Transforms features into polynomial combinations to fit non-linear data using a linear model.

### Execution
```bash
python3 Slip_06_Q2_OptionB.py
```

### Output Preview
```text
=== Polynomial Regression Curve Fitting ===
R2 Score: 0.941...
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
