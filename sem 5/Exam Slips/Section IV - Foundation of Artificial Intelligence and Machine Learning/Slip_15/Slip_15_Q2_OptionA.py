import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn.metrics import silhouette_score
from sklearn.datasets import make_blobs

# Generate synthetic dataset
X, _ = make_blobs(n_samples=300, centers=4, cluster_std=0.60, random_state=0)

wcss = []
silhouette_scores = []
K_range = range(2, 11)

for k in K_range:
    kmeans = KMeans(n_clusters=k, random_state=42, n_init=10)
    labels = kmeans.fit_predict(X)
    wcss.append(kmeans.inertia_)
    silhouette_scores.append(silhouette_score(X, labels))

plt.figure(figsize=(12, 5))

# Plot 1: Elbow Curve (K-Means Inertia)
plt.subplot(1, 2, 1)
plt.plot(K_range, wcss, marker='o', linestyle='--', color='b')
plt.title('Elbow Method (WCSS / Inertia)')
plt.xlabel('Number of clusters (K)')
plt.ylabel('WCSS')

# Plot 2: Silhouette Score
plt.subplot(1, 2, 2)
plt.plot(K_range, silhouette_scores, marker='s', linestyle='-', color='g')
plt.title('Silhouette Coefficient')
plt.xlabel('Number of clusters (K)')
plt.ylabel('Score')

plt.tight_layout()
plt.savefig("clustering_metrics.png")
print("\nClustering Objective Functions\n")
print("Generated 'clustering_metrics.png' showing Elbow curve and Silhouette scores.")
