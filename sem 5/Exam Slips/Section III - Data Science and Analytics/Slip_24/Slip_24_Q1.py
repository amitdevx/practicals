import pandas as pd

df = pd.DataFrame({
    'Book_ID': [1, 2, 3, 4, 5],
    'Book_Price': [100, 250, 500, 800, 1000]
})

print("Original Data:\n", df)
# Equal Width Binning
df['Price_Bin'] = pd.cut(df['Book_Price'], bins=3, labels=['Low', 'Medium', 'High'])
print("\nDiscretized Data:\n", df)
