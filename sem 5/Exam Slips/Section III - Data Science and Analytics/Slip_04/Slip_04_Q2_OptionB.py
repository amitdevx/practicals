import pandas as pd
from sklearn.cluster import KMeans
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

# Simulate E-commerce Customer Dataset
data = {
    'CustomerID': [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
    'Age': [25, 34, None, 45, 23, 35, 64, 52, 46, None],
    'Annual_Income': [35, 45, 55, 65, 30, 48, 80, 95, 60, 85],
    'Spending_Score': [40, 50, 60, 70, 30, 55, 80, 90, 65, 85]
}
df = pd.DataFrame(data)

# Preprocessing: Handle missing values
df['Age'] = df['Age'].fillna(df['Age'].mean())

# Select numerical features
X = df[['Annual_Income', 'Spending_Score']]

# Apply K-Means clustering
kmeans = KMeans(n_clusters=3, random_state=42, n_init=10)
df['Cluster'] = kmeans.fit_predict(X)

print("\nCustomer Segmentation using K-Means\n")
print(df[['CustomerID', 'Annual_Income', 'Spending_Score', 'Cluster']])

# Interpret clusters visually
plt.figure(figsize=(8, 6))
colors = ['red', 'green', 'blue']
for i in range(3):
    cluster_data = df[df['Cluster'] == i]
    plt.scatter(cluster_data['Annual_Income'], cluster_data['Spending_Score'], c=colors[i], label=f'Cluster {i}')

plt.scatter(kmeans.cluster_centers_[:, 0], kmeans.cluster_centers_[:, 1], s=200, c='yellow', marker='*', label='Centroids')
plt.title('E-commerce Customer Segments')
plt.xlabel('Annual Income (k$)')
plt.ylabel('Spending Score (1-100)')
plt.legend()
plt.savefig('ecommerce_clusters.png')
print("Plot saved as ecommerce_clusters.png")
