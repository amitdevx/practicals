import pandas as pd
import numpy as np

# Create Loan_Application dataset
data = {
    'Application_ID': [f'APP{i:03d}' for i in range(1, 11)],
    'Age': [25, 32, 45, 52, 28, 36, 41, 29, 60, 33],
    'Income': [35000, 55000, 90000, 120000, 42000, 68000, 85000, 38000, 110000, 58000],
    'Credit_Score': [650, 720, 780, 810, 600, 740, 770, 630, 800, 710],
    'Loan_Amount': [200000, 400000, 800000, 1500000, 250000, 500000, 750000, 300000, 1200000, 450000],
    'Approval_Status': ['Approved', 'Approved', 'Approved', 'Approved', 'Rejected', 'Approved', 'Approved', 'Rejected', 'Approved', 'Approved']
}

df = pd.DataFrame(data)
df.to_csv('Loan_application.csv', index=False)
print("--- Loan Application Dataset ---")
print(df.head())
print("\nSummary Statistics:")
print(df.describe())
