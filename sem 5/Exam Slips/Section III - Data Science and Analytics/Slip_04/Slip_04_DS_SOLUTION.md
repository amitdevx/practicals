# Slip 04 — Data Science and Analytics Solution Guide

## Question 1: Payment Methods Preferred Distribution (Pie Chart) [10 Marks]

### Problem Statement
Survey of customer payment methods: Credit Card, UPI, COD, Debit Card, Wallet. Plot customized Pie Chart.

### Concept & Methodology
Visualizes categorical market share with percentage callouts using plt.pie.

### Execution
```bash
python3 Slip_04_Q1.py
```

### Output Preview
```text
Plot saved as ds_slip_04_q1_piechart.png
```

---

## Question 2: Logistic Regression on Food Delivery Dataset [20 Marks]

### Problem Statement
Apply Logistic Regression on Online Food Delivery dataset to classify repeat vs non-repeat customers.

### Concept & Machine Learning Algorithm
Binary classification predicting repeat order probability based on order value, time, and discount.

### Execution
```bash
python3 Slip_04_Q2_OptionA.py
```

### Output Preview
```text
Model Accuracy: > 0.85
```

---

#### OR

## Question 2 (Alternative): Customer Segmentation using K-Means Clustering [20 Marks]

### Problem Statement
Apply K-Means clustering algorithm on Mall Customer dataset (Annual Income and Spending Score).

### Concept & Algorithm
Partitions customers into k distinct clusters by minimizing inertia (within-cluster sum of squares).

### Execution
```bash
python3 Slip_04_Q2_OptionB.py
```

### Output Preview
```text
Clustered dataframe with Cluster IDs (0, 1, 2)
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. When should you use a pie chart?
**Answer:** When showing the proportional composition of a categorical variable whose slices sum to 100%.

### Q2. How does K-Means clustering determine cluster centers?
**Answer:** By randomly initializing k centroids and iteratively assigning points to the nearest centroid and recomputing centroids as cluster means.

### Q3. What is the Elbow Method in K-Means?
**Answer:** A heuristic used to determine the optimal number of clusters by plotting inertia vs k and identifying the inflection point (elbow).

### Q4. What is the Confusion Matrix?
**Answer:** A table showing True Positives, False Positives, True Negatives, and False Negatives for classification evaluation.

### Q5. What is Precision vs Recall?
**Answer:** Precision = TP / (TP + FP); Recall = TP / (TP + FN).
