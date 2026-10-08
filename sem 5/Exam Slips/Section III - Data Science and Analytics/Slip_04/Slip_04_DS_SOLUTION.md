# Slip 04 — Data Science and Analytics Solution Guide

## Question 1: Pie Chart for Payment Methods [10 Marks]

### Problem Statement
A survey was conducted to determine the preferred payment method among customers:
payment_methods = ["UPI", "Credit Card", "Debit Card", "Cash", "Net Banking"]
customers = [150, 80, 60, 40, 30]
Create a Pie Chart to represent the percentage of customers using each payment method. Display the percentage contribution of each category and add an appropriate title.

### Execution
```bash
python3 Slip_04_Q1.py
```

---

## Question 2: Logistic Regression on Online Gaming Dataset [20 Marks]

### Problem Statement
Apply Logistic Regression on an Online Gaming dataset to classify players as Casual or Professional gamers based on features such as daily play time, achievements unlocked, in-game purchases, and gaming level. Evaluate the model using Accuracy, Precision, Recall, F1-Score, and Confusion Matrix.

### Execution
```bash
python3 Slip_04_Q2_OptionA.py
```

---

#### OR

## Question 2 (Alternative): K-Means Clustering on E-commerce Dataset [20 Marks]

### Problem Statement
Apply the K-Means Clustering algorithm on an E-commerce Customer dataset. Inspect and preprocess the data by handling missing values and selecting suitable numerical features. Apply K-Means clustering to segment the customers into different categories and interpret the resulting clusters.

### Execution
```bash
python3 Slip_04_Q2_OptionB.py
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is Logistic Regression used for?
**Answer:** It is used for binary classification tasks, predicting the probability that an instance belongs to a given class.

### Q2. How does K-Means clustering work?
**Answer:** It partitions data into K distinct clusters by iteratively assigning each data point to the cluster with the nearest centroid and updating the centroids.

### Q3. Why is handling missing values important?
**Answer:** Missing values can lead to biased models or cause algorithms to fail, as most machine learning models require numerical input without NaN values.

### Q4. What is a Confusion Matrix?
**Answer:** A table that describes the performance of a classification model by showing the true positives, false positives, true negatives, and false negatives.
