import pandas as pd
from sklearn.cluster import KMeans

data = {
    'Feature_1': [10, 12, 15, 60, 65, 70, 25, 30],
    'Feature_2': [20, 22, 28, 80, 85, 90, 40, 45]
}
df = pd.DataFrame(data)

kmeans = KMeans(n_clusters=3, random_state=42, n_init='auto')
df['Cluster'] = kmeans.fit_predict(df)

print("=== Alternative Solution: K-Means Clustering (Slip 11) ===")
print(df)
