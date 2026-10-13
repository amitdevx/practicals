# Slip 24

## Question 1: Data Discretization on Book Price [10 Marks]

Write a Python program to create a book_records DataFrame containing the attributes Book_ID and Book_Price for suitable sample records. Perform Data Discretization on the Book_Price attribute using Equal Width Binning. Display the original and discretized data.

```bash
python3 Slip_24_Q1.py
```

---

## Question 2 (Option A): World Cities Geospatial & Treemap [20 Marks]

Consider the World Cities dataset containing attributes city, country, latitude, longitude, and population information. Perform the following visualization tasks:
a. Create a Geospatial Visualization showing the locations of cities on a world map, using marker size to represent population.
b. Create a Treemap to visualize the population distribution of cities.

```bash
python3 Slip_24_Q2_OptionA.py
```

---

## Question 2 (Option B): Polynomial Regression on Car Price [20 Marks]

Consider the Car Price Prediction dataset and apply Polynomial Regression to predict the Selling Price based on Vehicle Age, Present Price, and Kilometers Driven. Perform the necessary data preprocessing, train and test the model, evaluate its performance using the R² Score, and visualize the actual data points along with the fitted polynomial regression curve.

```bash
python3 Slip_24_Q2_OptionB.py
```

---

## Question 3: Viva Questions & Answers [5 Marks]

**Q1. What is Equal Width Binning?**  
**Ans:** Dividing the entire range of values into intervals (bins) of equal size, implemented in pandas via `pd.cut()`.

**Q2. What is a Treemap?**  
**Ans:** A visualization method for displaying hierarchical data using nested rectangles whose areas are proportional to a quantitative variable.
