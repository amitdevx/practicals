import pandas as pd
from sklearn.preprocessing import StandardScaler

df = pd.DataFrame({
    'Age': [25, 30, 35, 40, 45],
    'Salary': [50000, 60000, 70000, 80000, 90000],
    'Experience': [2, 5, 8, 12, 15],
    'Working_Hours': [40, 42, 45, 40, 38],
    'Performance_Score': [3.5, 4.0, 4.2, 4.8, 4.5]
})

print("Original Data:\n", df)
scaler = StandardScaler()
df_std = pd.DataFrame(scaler.fit_transform(df), columns=df.columns)
print("\nStandardized Data:\n", df_std)
