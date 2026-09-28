# Semester 5 Exam Slips — Complete Practical Solutions

## Overview

This repository contains the complete, production-ready collection of **110 practical exam slips** for **Semester V (TYBSc Computer Science - NEP 2020 Pattern)**, Savitribai Phule Pune University (SPPU):

1. **Section I: Operating System-I (CS-305-MJ-P)** — 30 Slips
   - Process Scheduling (FCFS, SJF, Priority, Round Robin), Banker's Deadlock Avoidance Algorithm, Page Replacement Algorithms (FIFO, LRU, OPT/MFU/LFU), and Custom Extended Unix Shell Simulation (`count`, `typeline`, `search`, `list`).
   - Format: C Programs (`.c`) + Slip Solution Guides (`.md`) + Stamped Slip PDFs (`.pdf`).

2. **Section II: Core Java and Web Technology-I (CS-306-MJ-P)** — 30 Slips
   - **Part A (Core Java)**: Object-Oriented Programming, Multilevel Inheritance, Abstract Classes & Interfaces, Exception Handling, File I/O Streams, and Swing/AWT GUI with Event Handling.
   - **Part B (Web Technology-I)**: HTML5 Forms & Responsive Layouts, JavaScript Client-Side Validation, Dynamic DOM, and Node.js Server & Modules (`http`, `fs`, `url`, `events`, `Buffer`).
   - Format: Java Source (`.java`) + HTML/JavaScript (`.html`) / Node.js (`.js`) + Solution Guides (`.md`) + Stamped Slip PDFs (`.pdf`).

3. **Section III: Data Science and Analytics (CS-308-MJ-P)** — 25 Slips
   - Data Cleaning & Preprocessing (Pandas, NumPy), Missing Value Imputation, Outlier Handling (IQR/Z-score), Exploratory Data Analysis & Visualization (Matplotlib, Seaborn), Regression Analysis, Classification Models, and Clustering (K-Means, Hierarchical).
   - Format: Python Scripts (`.py`) + Datasets (`.csv`) + Solution Guides (`.md`) + Stamped Slip PDFs (`.pdf`).

4. **Section IV: Foundation of Artificial Intelligence and Machine Learning (CS-321-VSC-P)** — 25 Slips
   - Classical AI Search Strategies (BFS, DFS, A*, Best-First, UCS), Constraint Satisfaction Problems (N-Queens, Cryptarithmetic), Game Playing (Minimax with Alpha-Beta Pruning), Propositional & First-Order Logic, and Supervised Machine Learning Classifiers (Decision Trees, Naive Bayes, KNN, SVM).
   - Format: Python Scripts (`.py`) + Solution Guides (`.md`) + Stamped Slip PDFs (`.pdf`).

---

## Repository Structure

The repository strictly mirrors the Semester IV layout with zero extra nesting:

```text
Exam Slips/
├── Section I - Operating System-I/
│   ├── OS_topics.md                        (Comprehensive topic analysis & matrix)
│   ├── Slip_01/
│   │   ├── Slip_01_OS_SOLUTION.md          (Complete solution guide & viva Q&A)
│   │   ├── Slip_01_OS_SOLUTION.pdf         (Official stamped slip question paper)
│   │   ├── Slip_01_Q1.c                    (Question 1 C program)
│   │   └── Slip_01_Q2.c                    (Question 2 C program)
│   ├── Slip_02/
│   └── ... (Slip_03 to Slip_30)
│
├── Section II - Core Java and Web Technology-I/
│   ├── JAVA_WEB_topics.md                  (Comprehensive topic analysis & matrix)
│   ├── Slip_01/
│   │   ├── Slip_01_JAVA_WEB_SOLUTION.md    (Complete solution guide & viva Q&A)
│   │   ├── Slip_01_JAVA_WEB_SOLUTION.pdf   (Official stamped slip question paper)
│   │   ├── Slip_01_Q1.java                 (Question 1 Core Java program)
│   │   └── Slip_01_Q2.html                 (Question 2 Web Technology HTML/JS)
│   ├── ...
│   ├── Slip_09/
│   │   ├── Slip_09_JAVA_WEB_SOLUTION.md
│   │   ├── Slip_09_JAVA_WEB_SOLUTION.pdf
│   │   ├── Slip_09_Q1.java
│   │   └── Slip_09_Q2.js                   (Question 2 Web Technology Node.js)
│   └── ... (Slip_10 to Slip_30)
│
├── Section III - Data Science and Analytics/
│   ├── DS_topics.md                        (Comprehensive topic analysis & matrix)
│   ├── Slip_01/
│   │   ├── Slip_01_DS_SOLUTION.md          (Complete solution guide & viva Q&A)
│   │   ├── Slip_01_DS_SOLUTION.pdf         (Official stamped slip question paper)
│   │   ├── Slip_01_Q1.py                   (Question 1 Python script)
│   │   ├── Slip_01_Q2_OptionA.py           (Question 2 Option A Python script)
│   │   ├── Slip_01_Q2_OptionB.py           (Question 2 Option B Python script)
│   │   └── Loan_application.csv            (Sample input dataset)
│   ├── Slip_02/
│   └── ... (Slip_03 to Slip_25)
│
├── Section IV - Foundation of Artificial Intelligence and Machine Learning/
│   ├── AI_ML_topics.md                     (Comprehensive topic analysis & matrix)
│   ├── Slip_01/
│   │   ├── Slip_01_AI_SOLUTION.md          (Complete solution guide & viva Q&A)
│   │   ├── Slip_01_AI_SOLUTION.pdf         (Official stamped slip question paper)
│   │   ├── Slip_01_Q1.py                   (Question 1 Python AI search / logic)
│   │   ├── Slip_01_Q2_OptionA.py           (Question 2 Option A ML model)
│   │   └── Slip_01_Q2_OptionB.py           (Question 2 Option B ML model)
│   ├── Slip_02/
│   └── ... (Slip_03 to Slip_25)
│
├── _references/                            (Master university PDF syllabus & reference copies)
└── README.md                               (This master documentation)
```

---

## How to Compile & Run

### Section I: Operating System-I
```bash
cd "Section I - Operating System-I/Slip_01"

# Compile and run Question 1 (e.g., Banker's Algorithm / Scheduling)
gcc -Wall -Wextra -o Slip_01_Q1 Slip_01_Q1.c
./Slip_01_Q1

# Compile and run Question 2 (Custom Command Shell)
gcc -Wall -Wextra -o Slip_01_Q2 Slip_01_Q2.c
./Slip_01_Q2
```

### Section II: Core Java and Web Technology-I
```bash
cd "Section II - Core Java and Web Technology-I/Slip_01"

# Question 1: Core Java
javac Slip_01_Q1.java
java Slip_01_Q1

# Question 2: Web Technology
# For Slips 01 - 08 (HTML / Client-side JS):
xdg-open Slip_01_Q2.html    # or open directly in any browser

# For Slips 09 - 30 (Node.js Server):
cd "../Slip_09"
node Slip_09_Q2.js
```

### Section III: Data Science and Analytics
```bash
cd "Section III - Data Science and Analytics/Slip_01"

# Execute Question 1
python3 Slip_01_Q1.py

# Execute Question 2 (Option A or Option B)
python3 Slip_01_Q2_OptionA.py
python3 Slip_01_Q2_OptionB.py
```

### Section IV: Foundation of Artificial Intelligence and Machine Learning
```bash
cd "Section IV - Foundation of Artificial Intelligence and Machine Learning/Slip_01"

# Execute Question 1 (AI Search / Logic)
python3 Slip_01_Q1.py

# Execute Question 2 (Machine Learning Model)
python3 Slip_01_Q2_OptionA.py
python3 Slip_01_Q2_OptionB.py
```

---

## Practical Statistics

| Section | Subject Code | Subject Name | Slips | Languages / Formats | Marks per Slip |
| :---: | :---: | :--- | :---: | :--- | :---: |
| **I** | CS-305-MJ-P | Operating System-I | 30 | C, Shell, PDF, Markdown | 30 + 5 Viva |
| **II** | CS-306-MJ-P | Core Java and Web Technology-I | 30 | Java, HTML/JS, Node.js, PDF, Markdown | 30 + 5 Viva |
| **III** | CS-308-MJ-P | Data Science and Analytics | 25 | Python (pandas, sklearn), PDF, Markdown | 30 + 5 Viva |
| **IV** | CS-321-VSC-P | Foundation of AI and Machine Learning | 25 | Python (search, sklearn), PDF, Markdown | 30 + 5 Viva |
| **TOTAL** | | **All 4 Subjects** | **110** | **Complete Multi-Language Suite** | **110 Slips** |

---

## Examination Tips & Guidelines

1. **Sequential & Topic-Wise Preparation**: Consult `OS_topics.md`, `JAVA_WEB_topics.md`, `DS_topics.md`, and `AI_ML_topics.md` in each section root to target specific algorithms and patterns.
2. **Viva Questions**: Every solution guide (`Slip_XX_{SUBJECT}_SOLUTION.md`) includes **Question 3: Oral / Viva Questions & Answers [5 Marks]** covering standard oral examination questions asked by SPPU examiners.
3. **Clean Code**: All C programs use standard POSIX headers, Java programs use clean class encapsulation, Node.js programs handle server lifecycle gracefully, and Python scripts include clean synthetic fallback datasets so they run standalone anywhere.
