# Slip 03 — Data Science and Analytics Solution Guide

## Question 1: Hierarchical Clustering Dendrogram of Products [10 Marks]

### Problem Statement
Create dataframe of products (Price, Rating, Sales) and generate Dendrogram to group similar products.

### Concept & Methodology
Ward's linkage hierarchical agglomerative clustering visualized using SciPy dendrogram.

### Execution
```bash
python3 Slip_03_Q1.py
```

### Output Preview
```text
Plot saved as ds_slip_03_q1_dendrogram.png
```

---

## Question 2: Simple Linear Regression on Salary Dataset [20 Marks]

### Problem Statement
Apply Simple Linear Regression on Salary dataset to predict salary using years of experience.

### Concept & Machine Learning Algorithm
Fits y = mx + c line minimizing ordinary least squares errors.

### Execution
```bash
python3 Slip_03_Q2_OptionA.py
```

### Output Preview
```text
Slope: ~9300
Intercept: ~25000
R2 Score: > 0.95
```

---

#### OR

## Question 2 (Alternative): Random Forest Classifier on Wine Dataset [20 Marks]

### Problem Statement
Apply Random Forest algorithm on Wine dataset to classify wine cultivars.

### Concept & Algorithm
Ensemble of decision trees voting on class membership to reduce variance and avoid overfitting.

### Execution
```bash
python3 Slip_03_Q2_OptionB.py
```

### Output Preview
```text
Accuracy: 1.00
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is a Dendrogram?
**Answer:** A tree diagram representing hierarchical clustering relationships among items.

### Q2. What is the difference between Agglomerative and Divisive clustering?
**Answer:** Agglomerative is bottom-up (starts with individual points and merges); Divisive is top-down (starts with one cluster and splits).

### Q3. What is an Ensemble model?
**Answer:** A technique that combines predictions from multiple base models (e.g. decision trees) to improve overall predictive performance.

### Q4. What is Ordinary Least Squares (OLS)?
**Answer:** A method for estimating unknown parameters in linear regression by minimizing the sum of squared residuals.

### Q5. What is the purpose of train_test_split?
**Answer:** To evaluate model performance on unseen data and prevent data leakage and overfitting.
