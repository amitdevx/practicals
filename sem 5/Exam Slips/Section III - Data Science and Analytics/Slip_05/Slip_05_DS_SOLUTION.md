# Slip 05 — Data Science and Analytics Solution Guide

## Question 1: Monthly Sales Trend (Line Chart) [10 Marks]

### Problem Statement
Create dataframe of sales units over 6 months and plot customized Line Chart.

### Concept & Methodology
Uses plt.plot with markers and grid to display temporal trends.

### Execution
```bash
python3 Slip_05_Q1.py
```

### Output Preview
```text
Plot saved as ds_slip_05_q1_linechart.png
```

---

## Question 2: Streaming Services Subscribers Comparison (Native Venn & Overlap) [20 Marks]

### Problem Statement
Generate customer information for Netflix and Amazon Prime users and visualize overlap.

### Concept & Machine Learning Algorithm
Represents audience overlap and exclusive subscriber shares using native matplotlib circles.

### Execution
```bash
python3 Slip_05_Q2_OptionA.py
```

### Output Preview
```text
Plot saved as ds_slip_05_q2_streaming.png
```

---

#### OR

## Question 2 (Alternative): KNN Student Grade Classifier [20 Marks]

### Problem Statement
Use K-Nearest Neighbors (KNN) to classify students into grades based on Attendance and Marks.

### Concept & Algorithm
Assigns grade based on majority vote of the k nearest student instances in feature space.

### Execution
```bash
python3 Slip_05_Q2_OptionB.py
```

### Output Preview
```text
Predicted Grade for [80, 75]: B
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is Euclidean distance in KNN?
**Answer:** The straight-line distance between two points in Euclidean space.

### Q2. How does choice of k affect KNN?
**Answer:** Small k is sensitive to noise; large k produces a smoother boundary.

### Q3. Why is feature scaling essential for KNN?
**Answer:** Because distance calculations are dominated by large numeric scales.

### Q4. What is a line chart best suited for?
**Answer:** Displaying continuous time-series trends over sequential intervals.

### Q5. What is parametric vs non-parametric algorithms?
**Answer:** Parametric models assume a functional form; non-parametric models make no strong assumptions.
