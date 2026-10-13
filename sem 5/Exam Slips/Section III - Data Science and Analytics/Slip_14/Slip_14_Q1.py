import pandas as pd
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from scipy.cluster.hierarchy import dendrogram, linkage

# Create a dataframe containing product information
df = pd.DataFrame({
    'Product': ['Laptop', 'Smartphone', 'Tablet', 'Headphones', 'Camera'],
    'Price': [60000, 40000, 25000, 8000, 45000],
    'Rating': [4.5, 4.2, 4.0, 4.3, 4.7],
    'Number_of_Sales': [1200, 3500, 1800, 5000, 900]
})

print("Products DataFrame:")
print(df)

# Generate Dendrogram
Z = linkage(df[['Price', 'Rating', 'Number_of_Sales']], method='ward')

plt.figure(figsize=(8, 5))
dendrogram(Z, labels=df['Product'].values)
plt.title("Dendrogram of Products")
plt.xlabel("Products")
plt.ylabel("Distance")
plt.savefig('dendrogram.png')
print("Dendrogram saved as dendrogram.png")
