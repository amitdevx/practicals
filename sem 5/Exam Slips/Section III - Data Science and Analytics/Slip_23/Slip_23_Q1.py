import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.cluster.hierarchy import dendrogram, linkage
import matplotlib
matplotlib.use('Agg')

df = pd.DataFrame({
    'Product_name': ['A', 'B', 'C', 'D', 'E'],
    'Price': [100, 150, 120, 300, 320],
    'Rating': [4.5, 4.0, 4.2, 4.8, 4.9],
    'Number_of_Sales': [500, 400, 450, 150, 100]
})
print(df)
Z = linkage(df[['Price', 'Rating', 'Number_of_Sales']], method='ward')
plt.figure()
dendrogram(Z, labels=df['Product_name'].values)
plt.title("Dendrogram of Products")
plt.xlabel("Products")
plt.ylabel("Distance")
plt.savefig('dendrogram.png')
print("Dendrogram saved as dendrogram.png")
