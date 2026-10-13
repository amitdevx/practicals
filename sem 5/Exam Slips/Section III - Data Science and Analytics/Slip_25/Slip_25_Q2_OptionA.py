import pandas as pd
from sklearn.preprocessing import LabelEncoder

pd.set_option('display.max_columns', None)

# Original DataFrames
df1 = pd.DataFrame({
    'Brand': ['Samsung', 'Apple', 'Xiaomi', 'Samsung'],
    'Model': ['Galaxy S21', 'iPhone 13', 'Redmi Note', 'Galaxy A52'],
    'Price': [65000, 75000, 15000, 25000],
    'RAM': [8, 4, 6, 6]
})

df2 = pd.DataFrame({
    'Model': ['Galaxy S21', 'iPhone 13', 'Redmi Note', 'Galaxy A52'],
    'Storage': [128, 128, 64, 128],
    'Battery_Capacity': [4000, 3240, 5000, 4500],
    'Operating_System': ['Android', 'iOS', 'Android', 'Android']
})

print("DataFrame 1:")
print(df1)

print("\nDataFrame 2:")
print(df2)

# a) Data Integration by combining the two DataFrames using Model
merged_df = pd.merge(df1, df2, on='Model')
print("\na) Merged DataFrame (Data Integration using Model):")
print(merged_df)

# b) Label Encoding on the Brand attribute of the merged DataFrame
transformed_df = merged_df.copy()
le = LabelEncoder()
transformed_df['Brand'] = le.fit_transform(transformed_df['Brand'])
print("\nb) Merged DataFrame after Label Encoding on Brand:")
print(transformed_df)

# c) One-Hot Encoding on the Operating_System attribute of the merged DataFrame
transformed_df = pd.get_dummies(transformed_df, columns=['Operating_System'], dtype=int)
print("\nc) Transformed DataFrame after One-Hot Encoding on Operating_System:")
print(transformed_df)

# Final display of required DataFrames
print("\n--- Summary Display ---")
print("Original DataFrame 1:\n", df1)
print("\nOriginal DataFrame 2:\n", df2)
print("\nMerged DataFrame:\n", merged_df)
print("\nTransformed DataFrame:\n", transformed_df)
