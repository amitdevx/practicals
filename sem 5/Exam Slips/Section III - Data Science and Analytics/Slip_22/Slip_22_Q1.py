import pandas as pd
from sklearn.preprocessing import normalize

df = pd.DataFrame({
    'City': ['Pune', 'Mumbai', 'Delhi'],
    'House_Type': ['Apt', 'Villa', 'Apt'],
    'House_Area': [1000, 2500, 1200],
    'Number_of_Rooms': [3, 5, 3],
    'Monthly_Rent': [20000, 80000, 25000]
})

print("Original Data:\n", df)
num_cols = ['House_Area', 'Number_of_Rooms', 'Monthly_Rent']
df_norm = df.copy()
df_norm[num_cols] = normalize(df[num_cols])
print("\nNormalized Data:\n", df_norm)
