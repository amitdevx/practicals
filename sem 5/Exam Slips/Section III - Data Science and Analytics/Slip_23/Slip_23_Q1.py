import pandas as pd
from scipy.cluster.hierarchy import dendrogram, linkage
import matplotlib.pyplot as plt

df = pd.DataFrame({
    'Product': ['P1', 'P2', 'P3', 'P4', 'P5'],
    'Price': [100, 120, 500, 550, 110],
    'Sales': [5000, 4800, 1200, 1100, 5100]
})

Z = linkage(df[['Price', 'Sales']], method='ward')
plt.figure(figsize=(7, 4))
dendrogram(Z, labels=df['Product'].values)
plt.title('Product Clustering Dendrogram (Slip 23)')
plt.tight_layout()
plt.savefig('ds_slip_23_q1.png')
print("[+] Dendrogram saved.")
