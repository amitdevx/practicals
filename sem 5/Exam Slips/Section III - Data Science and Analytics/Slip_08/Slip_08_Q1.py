import pandas as pd
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

data = {
    'Latitude': [34.05, 36.77, 40.71, 37.77, 34.05],
    'Longitude': [-118.24, -119.41, -74.00, -122.41, -118.24],
    'Depth': [10, 15, 5, 8, 12],
    'Magnitude': [2.5, 4.0, 1.5, 5.5, 3.2]
}
df = pd.DataFrame(data)

plt.figure(figsize=(8,6))
plt.scatter(df['Longitude'], df['Latitude'], s=df['Magnitude']*50, c=df['Magnitude'], cmap='viridis', alpha=0.7)
plt.colorbar(label='Magnitude')
plt.title('Earthquake Locations and Magnitudes')
plt.xlabel('Longitude')
plt.ylabel('Latitude')
plt.grid(True)
plt.savefig('earthquakes_map.png')
print("Plot saved as earthquakes_map.png")
