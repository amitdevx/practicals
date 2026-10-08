import pandas as pd

df = pd.DataFrame({
    'Person_ID': [1, 2, 3, 4, 5, 6, 7, 8],
    'Age': [10, 15, 22, 28, 35, 45, 50, 60]
})

print("Original Data:\n", df)
# Equal Frequency Binning
df['Age_Bin'] = pd.qcut(df['Age'], q=3, labels=['Young', 'Middle', 'Senior'])
print("\nDiscretized Data:\n", df)
