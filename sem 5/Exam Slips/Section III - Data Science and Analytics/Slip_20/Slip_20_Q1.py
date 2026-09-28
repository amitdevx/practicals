import pandas as pd

df = pd.DataFrame({
    'ID': [101, 102, 103, 104, 105],
    'Attribute_A': [45, 52, 68, 74, 39],
    'Attribute_B': [12.5, 14.0, 18.2, 21.0, 11.5]
})

print("--- DataFrame Inspection (Slip 20) ---")
print(df)
print("\nStatistical Summary:")
print(df.describe())
