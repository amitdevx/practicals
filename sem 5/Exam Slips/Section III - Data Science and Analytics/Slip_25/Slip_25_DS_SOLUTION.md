# Slip 25

## Question 1: Course Enrollment Bar Chart [10 Marks]

Consider the following dataset representing the number of students enrolled in different courses:
courses = ["BCA", "BBA", "B.Com", "B.Sc", "BA"]
students = [60, 45, 75, 50, 35]
Create a Bar Chart to visualize the number of students enrolled in each course. Use different bar colors, add an appropriate title, and label both axes.

```bash
python3 Slip_25_Q1.py
```

---

## Question 2 (Option A): Mobile Phones Data Integration & Encoding [20 Marks]

Create two DataFrames containing information about different mobile phones:
- DataFrame 1: Brand, Model, Price, RAM
- DataFrame 2: Model, Storage, Battery_Capacity, Operating_System

Perform the following data transformation techniques:
a) Data Integration by combining the two DataFrames using Model
b) Label Encoding on the Brand attribute of the merged DataFrame
c) One-Hot Encoding on the Operating_System attribute of the merged DataFrame
Display the original DataFrames, merged DataFrame, and transformed DataFrame.

```bash
python3 Slip_25_Q2_OptionA.py
```

---

## Question 2 (Option B): Market Basket Analysis on Groceries [20 Marks]

Write a Python program to perform market basket analysis on the Groceries dataset using the Apriori algorithm. Read and explore the dataset, preprocess the data by handling missing values, convert categorical transaction data into a suitable numeric format, and generate frequent itemsets and association rules. Repeat the analysis using minimum support values 0.3 and 0.4.

```bash
python3 Slip_25_Q2_OptionB.py
```

---

## Question 3: Viva Questions & Answers [5 Marks]

**Q1. What is the difference between Label Encoding and One-Hot Encoding?**  
**Ans:** Label Encoding maps each categorical value to a unique integer. One-Hot Encoding creates a new binary (0/1) column for each distinct category.

**Q2. What is Support in Association Rule Mining?**  
**Ans:** Support is the proportion of transactions in the dataset that contain a particular itemset.
