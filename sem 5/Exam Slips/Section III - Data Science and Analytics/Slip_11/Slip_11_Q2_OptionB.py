import pandas as pd
from sklearn.cluster import KMeans
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

data = {
    'Annual_Income': [15, 16, 17, 18, 19, 60, 62, 64, 65, 90, 95, 100],
    'Spending_Score': [39, 81, 6, 77, 40, 48, 55, 42, 59, 15, 85, 20]
}
df = pd.DataFrame(data)

kmeans = KMeans(n_clusters=3, random_state=42, n_init=10)
df['Cluster'] = kmeans.fit_predict(df[['Annual_Income', 'Spending_Score']])

print("Clusters:\n", df)
plt.scatter(df['Annual_Income'], df['Spending_Score'], c=df['Cluster'], cmap='viridis')
plt.title('E-Commerce Customer Segments')
plt.xlabel('Annual Income')
plt.ylabel('Spending Score')
plt.savefig('ecommerce_segments.png')
