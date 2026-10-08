from sklearn.cluster import KMeans
import numpy as np

X = np.array([[1, 2], [1, 4], [1, 0], [10, 2], [10, 4], [10, 0]])
kmeans = KMeans(n_clusters=2, random_state=0, n_init=10).fit(X)
print("\nK-Means Clustering\n")
print("Cluster Centers:", kmeans.cluster_centers_)
print("Labels:", kmeans.labels_)
