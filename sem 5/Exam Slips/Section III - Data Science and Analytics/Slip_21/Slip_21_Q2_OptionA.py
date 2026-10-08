import pandas as pd
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
import matplotlib
matplotlib.use('Agg')

df = pd.DataFrame({
    'Attendance': [80, 85, 90, 40, 45, 50, 60, 65, 70],
    'Marks': [75, 80, 85, 30, 35, 40, 50, 55, 60]
})

X = df[['Attendance', 'Marks']]

kmeans = KMeans(n_clusters=3, random_state=42)
df['Cluster'] = kmeans.fit_predict(X)
centroids = kmeans.cluster_centers_

plt.figure()
plt.scatter(df['Attendance'], df['Marks'], c=df['Cluster'], cmap='rainbow')
plt.scatter(centroids[:, 0], centroids[:, 1], color='black', marker='X', s=200, label='Centroids')
plt.xlabel('Attendance')
plt.ylabel('Marks')
plt.title('K-Means Clustering of Students')
plt.legend()
plt.savefig('kmeans_student.png')
print("Plot saved as kmeans_student.png")
