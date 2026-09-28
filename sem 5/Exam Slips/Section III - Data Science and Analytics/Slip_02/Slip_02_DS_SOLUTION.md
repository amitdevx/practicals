# Slip 02 — Data Science and Analytics Solution Guide

## Question 1: Student Subject Marks Bar Chart [10 Marks]

### Problem Statement
Write a Python program to create an examination marks dataset across subjects and plot a customized Bar Chart.

### Concept & Methodology
Uses Matplotlib plt.bar with value annotations above each bar.

### Execution
```bash
python3 Slip_02_Q1.py
```

### Output Preview
```text
Plot saved as ds_slip_02_q1_barchart.png
```

---

## Question 2: YouTube Multiple Linear Regression [20 Marks]

### Problem Statement
Apply Linear Regression on YouTube dataset to predict revenue based on views, likes, and comments.

### Concept & Machine Learning Algorithm
Multiple linear regression models linear relationship between multiple independent variables and target revenue.

### Execution
```bash
python3 Slip_02_Q2_OptionA.py
```

### Output Preview
```text
R2 Score: 0.98
MSE: 412.35
```

---

#### OR

## Question 2 (Alternative): Apriori Market Basket Analysis on Video Resources [20 Marks]

### Problem Statement
Apply Apriori algorithm to discover frequent learning resources itemsets and association rules.

### Concept & Algorithm
Apriori algorithm finds frequent itemsets whose support exceeds a minimum support threshold.

### Execution
```bash
python3 Slip_02_Q2_OptionB.py
```

### Output Preview
```text
Frequent 1-Itemsets generated with support >= 0.40
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the difference between a bar chart and a histogram?
**Answer:** Bar charts represent categorical data with discrete bars; histograms show the frequency distribution of continuous numerical data.

### Q2. What does R-squared (R2 score) measure?
**Answer:** The proportion of variance in the dependent variable that is predictable from the independent variables (0 to 1).

### Q3. What is Support in Apriori algorithm?
**Answer:** Support(A) = Count(transactions containing A) / Total transactions.

### Q4. What is Confidence in association rule mining?
**Answer:** Confidence(A -> B) = Support(A U B) / Support(A).

### Q5. What is Overfitting in machine learning?
**Answer:** When a model learns noise and specific details of the training data so well that it fails to generalize to unseen test data.
