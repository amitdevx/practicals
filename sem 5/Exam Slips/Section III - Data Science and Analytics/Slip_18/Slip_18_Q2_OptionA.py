import pandas as pd
import matplotlib.pyplot as plt
import squarify
import matplotlib
matplotlib.use('Agg')

df = pd.DataFrame({
    'City': ['Tokyo', 'Delhi', 'Shanghai', 'Sao Paulo'],
    'Country': ['Japan', 'India', 'China', 'Brazil'],
    'Latitude': [35.68, 28.61, 31.23, -23.55],
    'Longitude': [139.69, 77.20, 121.47, -46.63],
    'Population': [37400068, 29399141, 26317104, 21846507]
})

# Geospatial Scatter Map
plt.figure(figsize=(10, 5))
plt.scatter(df['Longitude'], df['Latitude'], s=df['Population']/100000, alpha=0.5, c='blue')
for i, row in df.iterrows():
    plt.text(row['Longitude'], row['Latitude'], row['City'])
plt.title('Geospatial Visualization of Cities by Population')
plt.xlabel('Longitude')
plt.ylabel('Latitude')
plt.grid()
plt.savefig('geospatial.png')

# Treemap
plt.figure()
squarify.plot(sizes=df['Population'], label=df['City'], alpha=0.8)
plt.title('Treemap of Population Distribution')
plt.axis('off')
plt.savefig('world_treemap.png')
print("Plots saved.")
