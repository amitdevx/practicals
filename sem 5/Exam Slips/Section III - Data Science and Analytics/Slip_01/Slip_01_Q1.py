import pandas as pd
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from scipy.cluster.hierarchy import dendrogram, linkage

# Create a dataframe containing information about different products
data = {
    'Product': ['P1', 'P2', 'P3', 'P4', 'P5', 'P6', 'P7', 'P8', 'P9', 'P10'],
    'Price': [25, 30, 15, 80, 22, 120, 28, 31, 19, 26],
    'Rating': [4.2, 4.5, 3.8, 4.9, 4.0, 4.8, 4.3, 4.1, 3.9, 4.4],
    'Number_of_Sales': [120, 150, 80, 300, 110, 450, 130, 140, 95, 125]
}

df = pd.DataFrame(data)
df.set_index('Product', inplace=True)
print("Products DataFrame:\n", df)

# Generate a Dendrogram to group similar products based on characteristics
linked = linkage(df, method='ward')

plt.figure(figsize=(10, 6))
dendrogram(linked, labels=df.index.tolist(), orientation='top', distance_sort='descending')
plt.title('Dendrogram of Products')
plt.xlabel('Products')
plt.ylabel('Distance')
plt.savefig('dendrogram.png')
print("Dendrogram saved as dendrogram.png")
