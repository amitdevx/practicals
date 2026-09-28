# Slip 01 — Data Science and Analytics Solution Guide

## Question 1: Product Outlier Detection using Boxplot [10 Marks]

### Problem Statement
Create a dataframe containing information about products (Price, Rating, Sales) and generate Boxplot to detect outliers.

### Concept & Methodology
Box plots display the five-number summary: minimum, first quartile (Q1), median, third quartile (Q3), and maximum, highlighting points beyond 1.5*IQR as outliers.

### Execution
```bash
python3 Slip_01_Q1.py
```

### Output Preview
```text
Plot saved as ds_slip_01_q1_boxplot.png
```

---

## Question 2: Loan Application Dataset Generation & Statistical Summary [20 Marks]

### Problem Statement
Create a dataset named Loan_application.csv containing Application_ID, Age, Income, Credit_Score, Loan_Amount, Approval_Status and summarize.

### Concept & Machine Learning Algorithm
Generates realistic financial loan application data and uses describe() for statistical distribution analysis.

### Execution
```bash
python3 Slip_01_Q2_OptionA.py
```

### Output Preview
```text
Loan_application.csv created and summary printed.
```

---

#### OR

## Question 2 (Alternative): Logistic Regression on Iris Dataset [20 Marks]

### Problem Statement
Using built-in Iris dataset, apply Logistic Regression to classify flower species. Evaluate accuracy and classification report.

### Concept & Algorithm
Multiclass logistic regression using softmax function to classify iris species.

### Execution
```bash
python3 Slip_01_Q2_OptionB.py
```

### Output Preview
```text
Accuracy: 1.00
Precision/Recall: 1.00
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is an outlier and how does a boxplot identify it?
**Answer:** An outlier is an observation distant from other observations; points outside Q1 - 1.5*IQR and Q3 + 1.5*IQR are flagged as outliers.

### Q2. What is IQR in statistics?
**Answer:** Interquartile Range = Q3 - Q1, representing the middle 50% of the distribution.

### Q3. What is Logistic Regression?
**Answer:** A supervised classification algorithm that models the probability of a categorical outcome using the sigmoid (or softmax) function.

### Q4. What is the difference between supervised and unsupervised learning?
**Answer:** Supervised learning uses labeled training data; unsupervised learning discovers patterns and groupings in unlabeled data.

### Q5. What does df.describe() provide?
**Answer:** Count, mean, standard deviation, min, 25%, 50% (median), 75%, and max values for numeric columns.
