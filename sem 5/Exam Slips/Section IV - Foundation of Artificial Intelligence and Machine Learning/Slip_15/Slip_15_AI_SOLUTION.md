# Slip 15 — Foundation of AI & ML Solution Guide

## Question 1: DFS for State-Space Search [10 Marks]

### Problem Statement
Write a program to solve a state-space search problem using DFS. Start vertex - 1

### Concept & Algorithm
Depth-First Search (DFS) explores as far as possible along each branch before backtracking.

### Execution
```bash
python3 Slip_15_Q1.py
```

### Output Preview
```text
=== DFS Graph Traversal ===
DFS Order starting from 1: 1 -> 2 -> 5 -> 3 -> 6 -> 4 -> 7
```

---

## Question 2: Clustering Objective Functions [20 Marks]

### Problem Statement
Write Python program to demonstrate objective functions (K-Means Inertia & Silhouette Coefficient) and plot the curves.

### Concept & Algorithm
Uses scikit-learn to cluster data and evaluate the clustering quality via WCSS and Silhouette Score, plotting them with matplotlib.

### Execution
```bash
python3 Slip_15_Q2_OptionA.py
```

### Output Preview
```text
=== Clustering Objective Functions ===
Generated 'clustering_metrics.png' showing Elbow curve and Silhouette scores.
```

---

#### OR

## Question 2 (Alternative): Knowledge Base [20 Marks]

### Problem Statement
Write a program to build a Knowledge Base using logical rules and facts.

### Concept & Algorithm
A simple knowledge base can be built using dictionaries for facts and functions for rules that infer new information based on the facts.

### Execution
```bash
python3 Slip_15_Q2_OptionB.py
```

### Output Preview
```text
=== Simple Knowledge Base ===
Facts: {'is_raining': True, 'has_umbrella': False}
Inference 1: You will get wet.
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is DFS?
**Answer:** Depth-First Search is an algorithm that explores a graph by going as deep as possible before backtracking.

### Q2. What is K-Means Inertia (WCSS)?
**Answer:** WCSS is the sum of squared distances between each data point and its assigned cluster centroid.

### Q3. What is the Silhouette Score?
**Answer:** A metric to calculate the goodness of a clustering technique. It ranges from -1 to 1, where 1 means clusters are well apart.
