# Slip 20 — Data Science and Analytics Solution Guide

## Question 1: DataFrame Operations and Summary (Slip 20) [10 Marks]

### Problem Statement
Create DataFrame with relevant business attributes and perform summary operations.

### Concept & Methodology
Data exploration and statistical profiling using pandas describe() and info().

### Execution
```bash
python3 Slip_20_Q1.py
```

### Output Preview
```text
Summary statistics printed.
```

---

## Question 2: Machine Learning Model Implementation (Slip 20) [20 Marks]

### Problem Statement
Apply predictive modeling / classification on given dataset attributes.

### Concept & Machine Learning Algorithm
Supervised machine learning training, validation split, and metric evaluation.

### Execution
```bash
python3 Slip_20_Q2_OptionA.py
```

### Output Preview
```text
Model successfully fitted with high R2 / Accuracy.
```

---

#### OR

## Question 2 (Alternative): Clustering / Pattern Mining Alternative (Slip 20) [20 Marks]

### Problem Statement
Apply alternative clustering or pattern mining algorithm on specified features.

### Concept & Algorithm
Unsupervised clustering partitioning feature space into coherent groups.

### Execution
```bash
python3 Slip_20_Q2_OptionB.py
```

### Output Preview
```text
Clusters formed and labeled.
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
