# Slip 16 — Foundation of AI & ML Solution Guide

## Question 1: Depth Limited Search (DLS) [10 Marks]

### Problem Statement
Write a program to implement Depth Limited Search (DLS).

### Concept & Algorithm
DLS is a modification of DFS that places a limit on the depth of the search to prevent infinite loops.

### Execution
```bash
python3 Slip_16_Q1.py
```

### Output Preview
```text
=== Depth Limited Search (DLS) (Limit: 2, Target: 8) ===
Target '8' NOT found within depth limit 2.
```

---

## Question 2: Backward Chaining [20 Marks]

### Problem Statement
Write a program to implement the Backward Chaining inference mechanism.

### Concept & Algorithm
Backward chaining starts with a goal and works backward to see if the available facts support it using logical rules.

### Execution
```bash
python3 Slip_16_Q2_OptionA.py
```

### Output Preview
```text
=== Backward Chaining Inference ===
Known Facts: {'F', 'A', 'B'}
[Investigating Goal] E
[Investigating Goal] D
...
Goal 'E' Proven: True
```

---

#### OR

## Question 2 (Alternative): K-Means Clustering on Country Data [20 Marks]

### Problem Statement
Write a program to implement the K-Means Clustering Algorithm. Use `country_data.csv`. Normalize using StandardScaler(). Apply KMeans (k=3) and use Elbow method to find ideal 'k'.

### Concept & Algorithm
K-Means groups data into K clusters. Standardizing scales the features to mean 0, variance 1. The elbow method plots WCSS vs K to find the "elbow" point.

### Execution
```bash
python3 Slip_16_Q2_OptionB.py
```

### Output Preview
```text
=== K-Means Clustering on Country Data ===
Clusters assigned with k=3:
...
Elbow curve saved as 'elbow_curve.png'.
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is DLS?
**Answer:** Depth Limited Search is DFS with a predetermined depth limit to prevent it from going infinitely deep.

### Q2. How does Backward Chaining differ from Forward Chaining?
**Answer:** Backward chaining works backwards from the goal to facts (goal-driven), while forward chaining works from facts to conclusions (data-driven).

### Q3. Why use StandardScaler before K-Means?
**Answer:** K-Means uses distance (like Euclidean) to cluster points. Scaling ensures that features with larger numeric ranges don't dominate the distance calculations.
