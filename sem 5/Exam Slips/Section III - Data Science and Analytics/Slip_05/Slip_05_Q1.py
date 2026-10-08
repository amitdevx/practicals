import pandas as pd
from sklearn.preprocessing import LabelEncoder

# Create customer DataFrame
data = {
    'Customer_ID': [1, 2, 3, 4, 5],
    'Gender': ['Male', 'Female', 'Female', 'Male', 'Female'],
    'City': ['Pune', 'Mumbai', 'Pune', 'Delhi', 'Mumbai'],
    'Membership_Type': ['Gold', 'Silver', 'Bronze', 'Gold', 'Silver']
}
df = pd.DataFrame(data)

print("\nDataFrame Before Encoding\n")
print(df)

# Perform label encoding on categorical attributes
label_encoder = LabelEncoder()
df['Gender'] = label_encoder.fit_transform(df['Gender'])
df['City'] = label_encoder.fit_transform(df['City'])
df['Membership_Type'] = label_encoder.fit_transform(df['Membership_Type'])

print("\nDataFrame After Encoding\n")
print(df)
