import pandas as pd
import numpy as np
from scipy.cluster.hierarchy import dendrogram, linkage
import matplotlib.pyplot as plt

data = {
    'Product': ['P1', 'P2', 'P3', 'P4', 'P5'],
    'Price': [250, 270, 800, 850, 290],
    'Rating': [4.1, 4.2, 4.8, 4.9, 4.0],
    'Sales': [1200, 1300, 3500, 3600, 1150]
}
df = pd.DataFrame(data)
features = df[['Price', 'Rating', 'Sales']]

# Generate Dendrogram
Z = linkage(features, method='ward')
plt.figure(figsize=(8, 5))
dendrogram(Z, labels=df['Product'].values)
plt.title('Hierarchical Clustering Dendrogram of Products')
plt.xlabel('Product')
plt.ylabel('Distance')
plt.tight_layout()
plt.savefig('ds_slip_03_q1_dendrogram.png')
print("[+] Dendrogram saved as ds_slip_03_q1_dendrogram.png")
