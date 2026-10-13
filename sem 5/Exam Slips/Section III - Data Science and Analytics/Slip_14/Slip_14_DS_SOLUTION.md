# Slip 14

## Question 1: Product Clustering using Dendrogram [10 Marks]

Create a dataframe containing information about different products such as Price, Rating, and Number of Sales. Generate a Dendrogram to group similar products based on their characteristics.

```bash
python3 Slip_14_Q1.py
```

---

## Question 2 (Option A): Polynomial Regression for Car Price Prediction [20 Marks]

Using the Car Price Prediction dataset, apply Polynomial Regression to predict the Selling Price based on Vehicle Age, Present Price, and Kilometers Driven. Evaluate the model using the R² Score and visualize the actual data points along with the fitted polynomial curve.

```bash
python3 Slip_14_Q2_OptionA.py
```

---

## Question 2 (Option B): Mobile Phones Data Integration & Encoding [20 Marks]

Create two DataFrames containing information about different mobile phones:
- DataFrame 1: Brand, Model, Price, RAM
- DataFrame 2: Model, Storage, Battery_Capacity, Operating_System

Perform the following data transformation techniques:
a) Data Integration by combining the two DataFrames using Model
b) Label Encoding on the Brand attribute of the merged DataFrame
c) One-Hot Encoding on the Operating_System attribute of the merged DataFrame
Display the original DataFrames, merged DataFrame, and transformed DataFrame.

```bash
python3 Slip_14_Q2_OptionB.py
```

---

## Question 3: Viva Questions & Answers [5 Marks]

**Q1. What is a Dendrogram?**  
**Ans:** A tree-like diagram that illustrates the arrangement of clusters produced by hierarchical clustering.

**Q2. What is Polynomial Regression?**  
**Ans:** A form of regression analysis in which the relationship between independent variables and dependent variable is modeled as an nth degree polynomial.

**Q3. What is Data Integration?**  
**Ans:** Combining data from different sources into a unified view, commonly done using `pd.merge()` on a shared key.

**Q4. Difference between Label Encoding and One-Hot Encoding?**  
**Ans:** Label Encoding converts categorical labels into unique numbers (0, 1, 2...). One-Hot Encoding creates new binary columns (0 or 1) for each unique category.
