import pandas as pd
from sklearn.preprocessing import LabelEncoder

df1 = pd.DataFrame({
    'Brand': ['Samsung', 'Apple', 'Xiaomi'],
    'Model': ['M1', 'M2', 'M3'],
    'Price': [200, 800, 150],
    'RAM': [4, 8, 6]
})

df2 = pd.DataFrame({
    'Model': ['M1', 'M2', 'M3'],
    'Storage': [64, 256, 128],
    'Battery_Capacity': [4000, 3000, 5000],
    'Operating_System': ['Android', 'iOS', 'Android']
})

print("DataFrame 1:\n", df1)
print("\nDataFrame 2:\n", df2)

merged_df = pd.merge(df1, df2, on='Model')
print("\nMerged DataFrame:\n", merged_df)

transformed_df = merged_df.copy()
le = LabelEncoder()
transformed_df['Brand'] = le.fit_transform(transformed_df['Brand'])
transformed_df = pd.get_dummies(transformed_df, columns=['Operating_System'])

print("\nTransformed DataFrame:\n", transformed_df)
