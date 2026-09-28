#!/usr/bin/env python3
"""
generate_topics_md.py
Generates the 4 subject topic files:
- Section I - Operating System-I/OS_topics.md
- Section II - Core Java and Web Technology-I/JAVA_WEB_topics.md
- Section III - Data Science and Analytics/DS_topics.md
- Section IV - Foundation of Artificial Intelligence and Machine Learning/AI_ML_topics.md
"""

import os
import re

BASE_DIR = "/home/amitdevx/Code/practicals/sem 5/Exam Slips"

def generate_os_topics():
    content = """# Operating System-I (CS-305-MJ-P) Comprehensive Topic Analysis

> Strategic overview and breakdown of all 30 exam practical slips for SPPU TYBSc Computer Science (Sem V).

---

## 1. Core Practical Topics & Distribution

```
 OPERATING SYSTEM-I PRACTICAL CURRICULUM
 │
 ├── CPU Scheduling Algorithms [10 Slips]
 │   ├── First-Come First-Served (FCFS) [Slips: 02, 10, 20]
 │   ├── Shortest Job First (SJF - Non-Preemptive & Preemptive) [Slips: 03, 11, 21]
 │   ├── Priority Scheduling (Non-Preemptive & Preemptive) [Slips: 04, 12, 22]
 │   └── Round Robin (RR with Time Quantum) [Slips: 05, 13, 23]
 │
 ├── Deadlock Avoidance: Banker's Algorithm [10 Slips]
 │   ├── Data Structures & Need Matrix Calculation [Slips: 01, 14, 24]
 │   ├── Safety Algorithm & Safe Sequence Finding [Slips: 06, 16, 26]
 │   └── Resource Request Algorithm [Slips: 07, 17, 27]
 │
 ├── Page Replacement Algorithms [10 Slips]
 │   ├── First-In-First-Out (FIFO) [Slips: 08, 18, 28]
 │   ├── Least Recently Used (LRU - Counting / Stack) [Slips: 09, 19, 29]
 │   └── Optimal / MFU / LFU Page Replacement [Slips: 15, 25, 30]
 │
 └── Unix Shell Simulation (Extended Shell Commands) [All 30 Slips]
     ├── count Command (lines 'c', words 'w', characters 'l') [Slips: 01, 05, 09, 13, 17, 21, 25, 29]
     ├── typeline Command (+n first n lines, -n last n lines, a all) [Slips: 02, 06, 10, 14, 18, 22, 26, 30]
     ├── search Command (find string occurrences: 'f' first, 'a' all, 'c' count) [Slips: 03, 07, 11, 15, 19, 23, 27]
     └── list Command (list directory files: 'f' files, 'n' count, 'i' inode) [Slips: 04, 08, 12, 16, 20, 24, 28]
```

---

## 2. Complete Slip-wise Question Matrix (30 Slips)

| Slip | Question 1 (15 Marks) | Question 2 (15 Marks) | Total Marks | Key Concepts |
| :---: | :--- | :--- | :---: | :--- |
| **01** | Banker's Algorithm: Data Structures & Need Matrix | Custom Shell: `count` (c, w, l) | 30 + 5 Viva | Need = Max - Allocation, File I/O |
| **02** | CPU Scheduling: First-Come First-Served (FCFS) | Custom Shell: `typeline` (+n, -n, a) | 30 + 5 Viva | Non-preemptive, Gantt chart, Turnaround & Waiting |
| **03** | CPU Scheduling: Shortest Job First (SJF) | Custom Shell: `search` (f, a, c) | 30 + 5 Viva | Burst time sort, Context switching |
| **04** | CPU Scheduling: Priority (Non-Preemptive) | Custom Shell: `list` (f, n, i) | 30 + 5 Viva | Priority queue, Directory traversal (`opendir`) |
| **05** | CPU Scheduling: Round Robin (RR) | Custom Shell: `count` (c, w, l) | 30 + 5 Viva | Ready queue, Time Quantum, Circular queue |
| **06** | Banker's Algorithm: Safety Algorithm | Custom Shell: `typeline` (+n, -n, a) | 30 + 5 Viva | Work, Finish vectors, Safe sequence |
| **07** | Banker's Algorithm: Resource Request Algorithm | Custom Shell: `search` (f, a, c) | 30 + 5 Viva | Request <= Need & Request <= Available |
| **08** | Page Replacement: First-In-First-Out (FIFO) | Custom Shell: `list` (f, n, i) | 30 + 5 Viva | Queue simulation, Page Fault counter |
| **09** | Page Replacement: Least Recently Used (LRU) | Custom Shell: `count` (c, w, l) | 30 + 5 Viva | Timestamp/Counter stack, Locality of reference |
| **10** | CPU Scheduling: FCFS with Arrival Times | Custom Shell: `typeline` (+n, -n, a) | 30 + 5 Viva | Idle CPU handling, Completion times |
| **11** | CPU Scheduling: Preemptive SJF (SRTF) | Custom Shell: `search` (f, a, c) | 30 + 5 Viva | Remaining burst time, Preemption logic |
| **12** | CPU Scheduling: Preemptive Priority Scheduling | Custom Shell: `list` (f, n, i) | 30 + 5 Viva | Dynamic priority evaluation, Starvation |
| **13** | CPU Scheduling: Round Robin with Variable Quantum | Custom Shell: `count` (c, w, l) | 30 + 5 Viva | Context switch overhead, Quantum tuning |
| **14** | Banker's Algorithm: Need Matrix & Verification | Custom Shell: `typeline` (+n, -n, a) | 30 + 5 Viva | Multi-resource vector arithmetic |
| **15** | Page Replacement: Optimal (OPT) Algorithm | Custom Shell: `search` (f, a, c) | 30 + 5 Viva | Future reference distance, Belady's anomaly |
| **16** | Banker's Algorithm: Safe State Determination | Custom Shell: `list` (f, n, i) | 30 + 5 Viva | Deadlock avoidance, Safety state check |
| **17** | Banker's Algorithm: Additional Request Granting | Custom Shell: `count` (c, w, l) | 30 + 5 Viva | Safety validation after temporary allocation |
| **18** | Page Replacement: FIFO with Variable Frame Size | Custom Shell: `typeline` (+n, -n, a) | 30 + 5 Viva | Frame allocation comparison (3 vs 4 frames) |
| **19** | Page Replacement: LRU using Counter Method | Custom Shell: `search` (f, a, c) | 30 + 5 Viva | Clock tick simulation, Page hit/fault ratio |
| **20** | CPU Scheduling: FCFS Scheduling Simulation | Custom Shell: `list` (f, n, i) | 30 + 5 Viva | Process control block representation |
| **21** | CPU Scheduling: Non-Preemptive SJF Simulation | Custom Shell: `count` (c, w, l) | 30 + 5 Viva | Average Turnaround & Waiting time |
| **22** | CPU Scheduling: Priority Scheduling Simulation | Custom Shell: `typeline` (+n, -n, a) | 30 + 5 Viva | Priority order, Process dispatching |
| **23** | CPU Scheduling: Round Robin Algorithm Simulation | Custom Shell: `search` (f, a, c) | 30 + 5 Viva | Time sharing, Fair-share scheduling |
| **24** | Banker's Algorithm: Resource Allocation Matrix | Custom Shell: `list` (f, n, i) | 30 + 5 Viva | Allocation matrix, Available vector |
| **25** | Page Replacement: Most Frequently Used (MFU) | Custom Shell: `count` (c, w, l) | 30 + 5 Viva | Frequency counting, Page eviction |
| **26** | Banker's Algorithm: Complete Safety Algorithm | Custom Shell: `typeline` (+n, -n, a) | 30 + 5 Viva | Safe sequence tracing, Deadlock avoidance |
| **27** | Banker's Algorithm: Immediate Allocation Check | Custom Shell: `search` (f, a, c) | 30 + 5 Viva | State rollback if request unsafe |
| **28** | Page Replacement: FIFO Page Hit & Miss Ratio | Custom Shell: `list` (f, n, i) | 30 + 5 Viva | Fault rate percentage, Performance evaluation |
| **29** | Page Replacement: LRU with Reference Strings | Custom Shell: `count` (c, w, l) | 30 + 5 Viva | Memory footprint, Cache locality |
| **30** | Page Replacement: Least Frequently Used (LFU) | Custom Shell: `typeline` (+n, -n, a) | 30 + 5 Viva | Eviction of least used page, Tie-breaking |

---

## 3. Quick Compilation & Execution Guide

```bash
# Question 1 (C program)
gcc -Wall -Wextra -o Slip_XX_Q1 Slip_XX_Q1.c
./Slip_XX_Q1

# Question 2 (Custom Shell C program)
gcc -Wall -Wextra -o Slip_XX_Q2 Slip_XX_Q2.c
./Slip_XX_Q2
```
"""
    with open(os.path.join(BASE_DIR, "Section I - Operating System-I", "OS_topics.md"), "w", encoding="utf-8") as f:
        f.write(content.strip() + "\n")
    print("✓ Created OS_topics.md")

def generate_java_web_topics():
    content = """# Core Java and Web Technology-I (CS-306-MJ-P) Comprehensive Topic Analysis

> Strategic overview and breakdown of all 30 exam practical slips for SPPU TYBSc Computer Science (Sem V).

---

## 1. Core Practical Topics & Distribution

```
 CORE JAVA & WEB TECHNOLOGY-I
 │
 ├── Section A: Core Java [30 Slips - 15 Marks each]
 │   ├── Basic Java, Loops, Arrays & Math [Slips: 01, 02, 04, 29, 30]
 │   │   └── Array sum, Armstrong numbers, Matrix arithmetic, Prime/Zero checks, MyNumber
 │   ├── Object-Oriented Programming (Classes & Objects) [Slips: 06, 09, 13, 27, 28]
 │   │   └── Account, Employee, Clock, Person, MyDate date validation
 │   ├── Inheritance, Abstract Classes & Interfaces [Slips: 08, 11, 12, 21, 22, 23, 24, 25]
 │   │   └── Shape hierarchy, Vehicle hierarchy, Indoor/Outdoor games, College/Department,
 │   │       Product hierarchy, Multilevel inheritance, Cylinder volume, Calculator interface
 │   ├── Custom Exception Handling [Slips: 26, 28, 29]
 │   │   └── NotEligibleForExamException, InvalidDateException, ZeroNumberException
 │   ├── File Handling & Streams [Slips: 05, 10, 19]
 │   │   └── Reverse file content, Case conversion in files, File character/line/word count
 │   ├── Strings & Packages [Slips: 03, 07]
 │   │   └── String manipulation (concatenate, compare, reverse), Package creation & import
 │   └── Swing GUI & Event Handling [Slips: 14, 15, 16, 17, 18, 20]
 │       └── Prime check GUI, Simple Calculator GUI, Shopping Cart GUI, Key listener background,
 │           Color buttons GUI, Mouse motion/click tracker
 │
 └── Section B: Web Technology-I [30 Slips - 15 Marks each]
     ├── Client-Side Web: HTML5, CSS3 & JavaScript [Slips: 01 - 08]
     │   ├── HTML5 Form validation & CSS layout [Slips: 01, 02]
     │   ├── JavaScript Date/Time display & greeting [Slip: 03]
     │   ├── JavaScript String & Array operations [Slips: 04, 05]
     │   └── Interactive dynamic DOM manipulation [Slips: 06, 07, 08]
     │
     └── Server-Side Web: Node.js Core Modules & Server [Slips: 09 - 30]
         ├── HTTP Server (`http.createServer`) [Slips: 09, 10, 15, 20, 25]
         ├── File System Module (`fs.readFile`, `fs.writeFile`, `fs.appendFile`) [Slips: 11, 12, 16, 19, 21, 26, 27]
         ├── URL Module & Query String Parsing (`url.parse`) [Slips: 13, 14, 18, 22, 28]
         ├── Custom Modules & `exports` / `require` [Slips: 17, 23, 29]
         └── Events & Buffers (`events.EventEmitter`, `Buffer`) [Slips: 24, 30]
```

---

## 2. Complete Slip-wise Question Matrix (30 Slips)

| Slip | Question 1: Core Java (15 Marks) | Question 2: Web Technology (15 Marks) | File Format |
| :---: | :--- | :--- | :--- |
| **01** | Array sum and element display | Student Registration Form with HTML5 Validation | `Slip_01_Q1.java`, `Slip_01_Q2.html` |
| **02** | Armstrong numbers in given range | Responsive layout with CSS Flexbox / Grid | `Slip_02_Q1.java`, `Slip_02_Q2.html` |
| **03** | String operations (Concat, Compare, Reverse) | Real-time digital clock and greeting banner | `Slip_03_Q1.java`, `Slip_03_Q2.html` |
| **04** | Matrix Addition, Multiplication, Transpose | Factorial and Fibonacci generator in JS | `Slip_04_Q1.java`, `Slip_04_Q2.html` |
| **05** | Reverse file contents using FileReader | Email and Mobile Regex validation | `Slip_05_Q1.java`, `Slip_05_Q2.html` |
| **06** | Bank Account class with deposit/withdraw | Dynamic HTML table generator via JS | `Slip_06_Q1.java`, `Slip_06_Q2.html` |
| **07** | Custom Package creation & Driver import | Interactive Image Slider with auto-play | `Slip_07_Q1.java`, `Slip_07_Q2.html` |
| **08** | Shape abstract class (Rectangle, Triangle, Circle) | Multi-level dropdown navigation menu | `Slip_08_Q1.java`, `Slip_08_Q2.html` |
| **09** | Employee details and highest salary display | Node.js HTTP Hello World Web Server | `Slip_09_Q1.java`, `Slip_09_Q2.js` |
| **10** | Convert file contents to UPPERCASE | Node.js Web Server returning system information | `Slip_10_Q1.java`, `Slip_10_Q2.js` |
| **11** | Vehicle hierarchy (Light & Heavy Motor Vehicle) | Node.js Async File Reader (`fs.readFile`) | `Slip_11_Q1.java`, `Slip_11_Q2.js` |
| **12** | Indoor & Outdoor Games inheritance | Node.js File Copy and append utility | `Slip_12_Q1.java`, `Slip_12_Q2.js` |
| **13** | Clock class with AM/PM validation | Node.js URL Query String parser | `Slip_13_Q1.java`, `Slip_13_Q2.js` |
| **14** | Prime Checker Swing GUI | Node.js Search Query Parameter responder | `Slip_14_Q1.java`, `Slip_14_Q2.js` |
| **15** | Simple Arithmetic Calculator Swing GUI | Node.js Static File Web Server | `Slip_15_Q1.java`, `Slip_15_Q2.js` |
| **16** | Shopping Cart Item Selection Swing GUI | Node.js JSON Data API endpoint | `Slip_16_Q1.java`, `Slip_16_Q2.js` |
| **17** | Key listener background color change GUI | Custom Math Module export and calculation | `Slip_17_Q1.java`, `Slip_17_Q2.js` |
| **18** | Color buttons (Red, Green, Blue) Swing GUI | Node.js HTTP Request Method & Header inspector | `Slip_18_Q1.java`, `Slip_18_Q2.js` |
| **19** | Count characters, words and lines in file | Node.js Asynchronous Directory Lister | `Slip_19_Q1.java`, `Slip_19_Q2.js` |
| **20** | Mouse coordinates and click tracker GUI | Node.js Basic Routing Server (Home, About, Contact) | `Slip_20_Q1.java`, `Slip_20_Q2.js` |
| **21** | College & Department containment model | Node.js File Deletion and Rename utility | `Slip_21_Q1.java`, `Slip_21_Q2.js` |
| **22** | Product object array & highest price finder | Node.js HTTP POST Body parser | `Slip_22_Q1.java`, `Slip_22_Q2.js` |
| **23** | Continent -> Country -> State inheritance | Node.js Custom String Utilities Module | `Slip_23_Q1.java`, `Slip_23_Q2.js` |
| **24** | Cylinder volume and surface area calculation | Node.js EventEmitter custom event handling | `Slip_24_Q1.java`, `Slip_24_Q2.js` |
| **25** | Calculator interface implementation | Node.js Web Server returning current timestamp | `Slip_25_Q1.java`, `Slip_25_Q2.js` |
| **26** | User Exception: NotEligibleForExamException | Node.js File Stats inspector (size, birthtime) | `Slip_26_Q1.java`, `Slip_26_Q2.js` |
| **27** | Person class with address and details | Node.js File line-by-line stream reader | `Slip_27_Q1.java`, `Slip_27_Q2.js` |
| **28** | User Exception: InvalidDateException | Node.js Query parameter addition calculator | `Slip_28_Q1.java`, `Slip_28_Q2.js` |
| **29** | User Exception: ZeroNumberException for primes | Node.js Custom Date Formatter Module | `Slip_29_Q1.java`, `Slip_29_Q2.js` |
| **30** | MyNumber class with isNegative, isOdd, isEven | Node.js Buffer operations and Base64 conversion | `Slip_30_Q1.java`, `Slip_30_Q2.js` |

---

## 3. Quick Compilation & Execution Guide

```bash
# Compile and run Java Question 1
javac Slip_XX_Q1.java
java Slip_XX_Q1

# Run Web Technology Question 2
# For Slips 01 - 08 (HTML):
xdg-open Slip_XX_Q2.html   # or double-click to open in browser

# For Slips 09 - 30 (Node.js):
node Slip_XX_Q2.js
```
"""
    with open(os.path.join(BASE_DIR, "Section II - Core Java and Web Technology-I", "JAVA_WEB_topics.md"), "w", encoding="utf-8") as f:
        f.write(content.strip() + "\n")
    print("✓ Created JAVA_WEB_topics.md")

def generate_ds_topics():
    content = """# Data Science and Analytics (CS-308-MJ-P) Comprehensive Topic Analysis

> Strategic overview and breakdown of all 25 exam practical slips for SPPU TYBSc Computer Science (Sem V).

---

## 1. Core Practical Topics & Distribution

```
 DATA SCIENCE AND ANALYTICS CURRICULUM
 │
 ├── Data Cleaning & Preprocessing (Pandas / NumPy) [Slips: 01, 04, 07, 10, 15, 18, 22]
 │   ├── Handling Missing / Null Values (Imputation & Dropping)
 │   ├── Outlier Detection & Treatment (IQR, Z-Score, Boxplots)
 │   ├── Feature Scaling: Normalization (MinMaxScaler) & Standardization (StandardScaler)
 │   └── Categorical Encoding (One-Hot Encoding, Label Encoding)
 │
 ├── Exploratory Data Analysis & Visualization (Matplotlib / Seaborn) [Slips: 02, 05, 08, 12, 16, 20, 24]
 │   ├── Distribution Visualizations: Histograms, KDE, Boxplots, Violin plots
 │   ├── Correlation Matrix Heatmaps & Pairplots
 │   ├── Bar charts, Pie charts, Line plots for categorical & time series
 │   └── Scatter plots with regression lines
 │
 ├── Supervised Machine Learning Algorithms (scikit-learn) [Slips: 03, 06, 09, 11, 14, 17, 21, 23, 25]
 │   ├── Simple & Multiple Linear Regression (OLS, R² Score, MSE/RMSE)
 │   ├── Logistic Regression for Binary Classification (Confusion Matrix, Precision, Recall, F1)
 │   ├── Decision Tree Classifier & Regressor (Tree visualization, Hyperparameters)
 │   └── K-Nearest Neighbors (KNN) & Support Vector Machines (SVM)
 │
 └── Unsupervised Learning & Clustering (scikit-learn / SciPy) [Slips: 03, 13, 19]
     ├── K-Means Clustering (Elbow method, Silhouette score)
     ├── Hierarchical Clustering (Dendrogram, Agglomerative clustering)
     └── Principal Component Analysis (PCA) Dimensionality Reduction
```

---

## 2. Complete Slip-wise Question Matrix (25 Slips)

| Slip | Question 1 (15 Marks) | Question 2 Option A (15 Marks) | Question 2 Option B (15 Marks) |
| :---: | :--- | :--- | :--- |
| **01** | Boxplot Outlier Detection on Loan Dataset | Simple Linear Regression on Housing Data | Multiple Linear Regression Model Evaluation |
| **02** | Categorical Bar Chart & Summary Stats | K-Means Clustering with Elbow Method | K-Means Silhouette Score Evaluation |
| **03** | Hierarchical Clustering Dendrogram | Logistic Regression on Binary Classification | Confusion Matrix & Classification Report |
| **04** | Missing Values Imputation & Cleaning | Feature Scaling: MinMaxScaler vs StandardScaler | One-Hot Encoding vs Label Encoding |
| **05** | Time Series Line Chart Analysis | Simple Moving Average & Trend Line | Exponential Smoothing Trend Model |
| **06** | Correlation Heatmap & Scatter Matrix | Multiple Linear Regression for Salary Prediction | Polynomial Regression Curve Fitting |
| **07** | Feature Scaling & Distribution Plot | Decision Tree Classifier on Iris Dataset | Decision Tree Regressor Model |
| **08** | Pie Chart & Doughnut Chart Breakdown | KNN Classifier with k-Value Tuning | KNN Distance Metric Comparison |
| **09** | Outlier Capping using IQR Method | Logistic Regression on Customer Churn | ROC Curve & AUC Score Calculation |
| **10** | Histogram & Density (KDE) Comparison | Naive Bayes Classifier on Text/Features | Gaussian Naive Bayes Model |
| **11** | Normalization & Z-score Transformation | Support Vector Classifier (SVC Linear) | SVC with RBF Kernel & Gamma Tuning |
| **12** | Violin Plot & Distribution Comparison | Random Forest Classifier Evaluation | Feature Importance Plotting |
| **13** | Sales Dataset EDA & Bar Chart | K-Means Customer Segmentation | PCA Dimensionality Reduction 2D Plot |
| **14** | Pairplot Multivariate Analysis | Multiple Regression with Feature Selection | Ridge & Lasso Regularized Regression |
| **15** | Null Value Replacement Strategy | Logistic Regression Heart Disease Detection | Stratified K-Fold Cross Validation |
| **16** | Cumulative Distribution Function Plot | Decision Tree Gini vs Entropy Split | Pruned Decision Tree vs Unpruned |
| **17** | Boxplot with Jittered Data Points | KNN Classification with Cross Validation | Grid Search CV for Hyperparameter Tuning |
| **18** | Standardization & Skewness Check | Linear Regression Diagnostic Residual Plot | Log Transformation of Target Variable |
| **19** | Bivariate Scatter Plot with Hue Grouping | Hierarchical Agglomerative Clustering | K-Medoids Clustering Comparison |
| **20** | Heatmap of Covariance Matrix | Logistic Regression on Titanic Dataset | Precision-Recall Tradeoff Curve |
| **21** | GroupBy Aggregations & Barplot | Multiple Linear Regression Car Price Model | Multicollinearity & VIF Calculation |
| **22** | IQR Filtering & Trimmed Mean | Decision Tree Classification on Wine Data | Confusion Matrix Heatmap Display |
| **23** | FacetGrid Multi-Plot Distribution | KNN Classifier on Digits Dataset | KNN Boundary Decision Surface |
| **24** | Subplots Grid for Multiple Metrics | Simple Linear Regression Sales Trend | Multiple Regression with ANOVA Summary |
| **25** | Correlation Matrix Ranking & Filter | Logistic Regression Bank Marketing Data | Model Evaluation: Accuracy, F1, Recall |

---

## 3. Quick Execution Guide

```bash
# Run Question 1
python3 Slip_XX_Q1.py

# Run Question 2 Option A
python3 Slip_XX_Q2_OptionA.py

# Run Question 2 Option B
python3 Slip_XX_Q2_OptionB.py
```
"""
    with open(os.path.join(BASE_DIR, "Section III - Data Science and Analytics", "DS_topics.md"), "w", encoding="utf-8") as f:
        f.write(content.strip() + "\n")
    print("✓ Created DS_topics.md")

def generate_ai_topics():
    content = """# Foundation of Artificial Intelligence & Machine Learning (CS-321-VSC-P) Comprehensive Topic Analysis

> Strategic overview and breakdown of all 25 exam practical slips for SPPU TYBSc Computer Science (Sem V).

---

## 1. Core Practical Topics & Distribution

```
 AI & MACHINE LEARNING PRACTICAL CURRICULUM
 │
 ├── Classical AI Search Algorithms [Slips: 01, 02, 05, 06, 09, 10, 13, 14, 17, 18, 21, 22]
 │   ├── Uninformed Search: Breadth-First Search (BFS) & Depth-First Search (DFS)
 │   ├── Informed / Heuristic Search: A* Search Algorithm & Best-First Search
 │   └── Uniform Cost Search (UCS) & Iterative Deepening Search (IDS)
 │
 ├── Constraint Satisfaction Problems (CSP) & Games [Slips: 03, 07, 11, 15, 19, 23]
 │   ├── N-Queens Problem (Backtracking & State Representation)
 │   ├── Cryptarithmetic Puzzle Solving (Constraint propagation)
 │   ├── Tic-Tac-Toe Game with AI Agent
 │   └── Minimax Algorithm with Alpha-Beta Pruning
 │
 ├── Knowledge Representation & Reasoning [Slips: 04, 08, 12, 16, 20, 24]
 │   ├── Propositional Logic Resolution & Inference
 │   ├── First-Order Logic (FOL) Unification
 │   └── Forward Chaining & Backward Chaining Rule Engines
 │
 └── Core Machine Learning Foundations [Slips: 01 - 25 Option A/B]
     ├── Decision Tree Classifier & Decision Surfaces
     ├── Naive Bayes Classifier (Gaussian & Multinomial)
     ├── K-Nearest Neighbors (KNN) Classifier
     ├── Linear & Logistic Regression Classification
     └── Model Performance Metrics (Confusion Matrix, Precision, Recall, Accuracy)
```

---

## 2. Complete Slip-wise Question Matrix (25 Slips)

| Slip | Question 1: AI Search / Logic (15 Marks) | Question 2 Option A: ML (15 Marks) | Question 2 Option B: ML (15 Marks) |
| :---: | :--- | :--- | :--- |
| **01** | Breadth-First Search (BFS) on Graph | Decision Tree Classifier on Iris Dataset | Naive Bayes Classifier on Iris Dataset |
| **02** | Depth-First Search (DFS) on Graph | KNN Classifier with Euclidean Distance | KNN Classifier with Manhattan Distance |
| **03** | 8-Queens Problem using Backtracking | Logistic Regression Classification | Linear Regression Fitting |
| **04** | Propositional Logic Inference & Truth Table | Support Vector Classifier (Linear Kernel) | Support Vector Classifier (RBF Kernel) |
| **05** | A* Search Algorithm with Heuristics | Decision Tree with Information Gain | Decision Tree with Gini Impurity |
| **06** | Best-First Search (Greedy Heuristic) | Gaussian Naive Bayes Classifier | Bernoulli Naive Bayes Classifier |
| **07** | Tic-Tac-Toe Minimax Agent | K-Means Clustering on Synthetic Data | Hierarchical Clustering Dendrogram |
| **08** | Forward Chaining Rule Engine | Random Forest Classifier | AdaBoost Classifier |
| **09** | Uniform Cost Search (Dijkstra variant) | Linear Regression on Boston Housing | Ridge Regularized Regression |
| **10** | Iterative Deepening DFS (IDDFS) | Confusion Matrix & Metrics Calculation | ROC & AUC Score Evaluation |
| **11** | Cryptarithmetic Problem (SEND+MORE=MONEY) | Decision Tree Pruning & Max Depth | Decision Tree Feature Importance |
| **12** | Backward Chaining Inference Engine | KNN Classification with k-fold CV | KNN Optimal k Parameter Curve |
| **13** | A* Search on 8-Puzzle Grid | Logistic Regression Binary Classification | Softmax Multi-Class Logistic Regression |
| **14** | Water Jug Problem using State Space | Naive Bayes Text Classification | CountVectorizer with Naive Bayes |
| **15** | Minimax Algorithm with Alpha-Beta Pruning | Support Vector Machine Hyperplane | SVC Soft Margin C-Parameter Tuning |
| **16** | First-Order Logic Unification Algorithm | Decision Tree Classifier on Wine Data | Random Forest on Wine Data |
| **17** | Missionaries and Cannibals Problem | K-Means with Silhouette Analysis | Elbow Method Inertia Curve |
| **18** | Bidirectional Search Algorithm | Simple Linear Regression Line Plot | Multiple Linear Regression Model |
| **19** | N-Queens (4-Queens & 8-Queens) Solver | Logistic Regression with Decision Boundary | KNN Decision Boundary Plot |
| **20** | Propositional Resolution Refutation | Gaussian Naive Bayes on Breast Cancer | Decision Tree on Breast Cancer Data |
| **21** | Greedy Best-First Search Navigation | Polynomial Feature Regression | Ridge Regression with Cross Validation |
| **22** | Depth-Limited Search (DLS) | KNN Classification with Standardized Inputs | KNN on Raw vs Scaled Comparison |
| **23** | Graph Coloring using CSP Backtracking | Decision Tree Regression | Linear Regression vs Decision Tree |
| **24** | Semantic Net / Frame Representation | Logistic Regression Confusion Matrix | Cross-Validated Accuracy Score |
| **25** | Hill Climbing Search Algorithm | Naive Bayes Model Evaluation | Comprehensive Model Comparison (DT vs NB vs KNN) |

---

## 3. Quick Execution Guide

```bash
# Run Question 1
python3 Slip_XX_Q1.py

# Run Question 2 Option A
python3 Slip_XX_Q2_OptionA.py

# Run Question 2 Option B
python3 Slip_XX_Q2_OptionB.py
```
"""
    with open(os.path.join(BASE_DIR, "Section IV - Foundation of Artificial Intelligence and Machine Learning", "AI_ML_topics.md"), "w", encoding="utf-8") as f:
        f.write(content.strip() + "\n")
    print("✓ Created AI_ML_topics.md")

if __name__ == "__main__":
    generate_os_topics()
    generate_java_web_topics()
    generate_ds_topics()
    generate_ai_topics()
    print("\nAll 4 topics files generated successfully!")
