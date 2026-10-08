import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn.preprocessing import StandardScaler
import os

print("\nK-Means Clustering on Country Data\n")
if not os.path.exists('country_data.csv'):
    print("country_data.csv not found. Creating a dummy dataset for demonstration.")
    data = {
        'country_nm': ['C1','C2','C3','C4','C5'],
        'child_mortality': [90.2, 26.6, 2.8, 8.3, 19.3],
        'exports': [10.0, 28.9, 17.5, 39.7, 59.0],
        'health': [7.5, 6.5, 7.7, 11.6, 6.8],
        'imports': [44.9, 34.6, 29.7, 50.4, 60.9],
        'income': [1610, 9930, 85300, 32800, 19100],
        'inflation': [9.44, 4.49, 3.69, 6.4, 1.44],
        'life_expectancy': [56.2, 76.3, 81.3, 81.9, 76.5],
        'total_fer': [5.82, 2.05, 1.36, 1.92, 1.87],
        'gdp': [553, 4690, 105000, 35000, 11400]
    }
    df = pd.DataFrame(data)
    df.to_csv('country_data.csv', index=False)

# Load data
df = pd.read_csv('country_data.csv')
features = ['child_mortality', 'exports', 'health', 'imports', 'income', 'inflation', 'life_expectancy', 'total_fer', 'gdp']
X = df[features]

# Normalize
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# K-Means with k=3
kmeans3 = KMeans(n_clusters=3, random_state=42, n_init=10)
df['Cluster'] = kmeans3.fit_predict(X_scaled)
print("Clusters assigned with k=3:")
print(df[['country_nm', 'Cluster']])

# Elbow Method
wcss = []
K_range = range(1, min(11, len(df)+1))  # max 10, or number of samples
for k in K_range:
    kmeans = KMeans(n_clusters=k, random_state=42, n_init=10)
    kmeans.fit(X_scaled)
    wcss.append(kmeans.inertia_)

plt.plot(K_range, wcss, marker='o')
plt.title('Elbow Method for Optimal k')
plt.xlabel('Number of clusters')
plt.ylabel('WCSS')
plt.savefig('elbow_curve.png')
print("Elbow curve saved as 'elbow_curve.png'.")
