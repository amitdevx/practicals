import pandas as pd
from sklearn.preprocessing import MinMaxScaler, StandardScaler, normalize

df = pd.DataFrame({
    'Temperature': [30, 32, 25, 28],
    'Humidity': [70, 60, 80, 75],
    'WindSpeed': [15, 20, 10, 12],
    'Pressure': [1010, 1012, 1008, 1009],
    'Rainfall': [0, 5, 20, 10]
})
print("Original Data:\n", df)

# Min-Max Scaling
min_max = MinMaxScaler()
df_minmax = pd.DataFrame(min_max.fit_transform(df), columns=df.columns)
print("\nMin-Max Scaled Data:\n", df_minmax)

# Standardization
std_scaler = StandardScaler()
df_std = pd.DataFrame(std_scaler.fit_transform(df), columns=df.columns)
print("\nStandardized Data:\n", df_std)

# Normalization
df_norm = pd.DataFrame(normalize(df), columns=df.columns)
print("\nNormalized Data:\n", df_norm)
