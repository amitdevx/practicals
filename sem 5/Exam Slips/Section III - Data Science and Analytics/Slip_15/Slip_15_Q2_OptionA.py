import pandas as pd
import matplotlib.pyplot as plt
import squarify
import matplotlib
matplotlib.use('Agg')

df = pd.DataFrame({
    'City': ['Pune', 'Mumbai', 'Delhi', 'Bangalore'],
    'Area': [331, 603, 1484, 709],
    'Average_Temperature': [25, 28, 30, 24],
    'Rainfall': [722, 2000, 700, 900],
    'Population_Density': [5600, 20000, 11000, 4300]
})

# Treemap
plt.figure()
squarify.plot(sizes=df['Population_Density'], label=df['City'], alpha=0.8)
plt.title("Treemap of Population Density")
plt.axis('off')
plt.savefig('treemap.png')

# 3D Scatter
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(df['Area'], df['Average_Temperature'], df['Rainfall'], c='r', marker='o')
ax.set_xlabel('Area (sq. km)')
ax.set_ylabel('Avg Temperature (C)')
ax.set_zlabel('Rainfall (mm)')
plt.title("3D Scatter Plot of Cities")
plt.savefig('3d_scatter.png')
print("Plots saved.")
