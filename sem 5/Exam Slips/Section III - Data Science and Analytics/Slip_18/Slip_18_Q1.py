import pandas as pd
import numpy as np

df = pd.DataFrame({
    'Emp_ID': [1, 2, 2, 4, 5, 6],
    'Age': [25, 30, 30, np.nan, 28, 60],
    'Dept': ['IT', 'HR', 'HR', 'Finance', 'IT', 'Sales'],
    'Years_Experience': [2, 5, 5, 8, 4, 30],
    'Performance_Rating': [4.5, 4.0, 4.0, 3.8, 4.2, 2.0]
})

print("Original DataFrame:\n", df)

# Handle Missing Values
df['Age'] = df['Age'].fillna(df['Age'].mean())

# Remove Duplicates
df = df.drop_duplicates()

# IQR Outliers for Years_Experience
Q1 = df['Years_Experience'].quantile(0.25)
Q3 = df['Years_Experience'].quantile(0.75)
IQR = Q3 - Q1
lower_bound = Q1 - 1.5 * IQR
upper_bound = Q3 + 1.5 * IQR

outliers = df[(df['Years_Experience'] < lower_bound) | (df['Years_Experience'] > upper_bound)]
print("\nOutliers detected:\n", outliers)
df_clean = df[(df['Years_Experience'] >= lower_bound) & (df['Years_Experience'] <= upper_bound)]
print("\nCleaned DataFrame:\n", df_clean)
