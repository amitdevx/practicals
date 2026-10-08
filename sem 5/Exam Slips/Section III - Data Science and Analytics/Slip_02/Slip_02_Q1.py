import pandas as pd

# Create age_records DataFrame
data = {
    'Person_ID': [101, 102, 103, 104, 105, 106, 107, 108],
    'Age': [15, 22, 35, 42, 58, 65, 78, 85]
}
df = pd.DataFrame(data)

# Perform Data Discretization on Age using Equal Width Binning
# Let's say 4 bins
df['Age_Bin'] = pd.cut(df['Age'], bins=4, labels=['Youth', 'Young Adult', 'Adult', 'Senior'])

print("Original and Discretized Data:")
print(df)
