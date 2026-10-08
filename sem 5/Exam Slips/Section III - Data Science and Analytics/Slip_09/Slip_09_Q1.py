import pandas as pd
from sklearn.preprocessing import MinMaxScaler

data = {
    'Product_ID': [1, 2, 3, 4, 5],
    'Price': [100, 250, 150, 800, 50],
    'Quantity_Sold': [20, 50, 30, 10, 100],
    'Discount': [5, 15, 10, 20, 2],
    'Revenue': [1900, 10625, 4050, 6400, 4900]
}
df = pd.DataFrame(data)

print("Original Data:\n", df)

scaler = MinMaxScaler()
scaled_data = scaler.fit_transform(df[['Price', 'Quantity_Sold', 'Discount', 'Revenue']])
df[['Price', 'Quantity_Sold', 'Discount', 'Revenue']] = scaled_data

print("\nTransformed Data (Min-Max Scaled):\n", df)
