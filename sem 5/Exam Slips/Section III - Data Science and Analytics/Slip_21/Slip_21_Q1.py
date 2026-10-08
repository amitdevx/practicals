import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import matplotlib
matplotlib.use('Agg')

# weather.csv creation
df = pd.DataFrame({
    'Temperature': [30, 32, 28, 35],
    'Humidity': [70, 60, 80, 50],
    'Rainfall': [10, 0, 20, 0],
    'Wind Speed': [15, 10, 20, 12]
})
df.to_csv('weather.csv', index=False)

df_read = pd.read_csv('weather.csv')
corr = df_read.corr()

plt.figure()
sns.heatmap(corr, annot=True, cmap='viridis')
plt.title("Weather Correlation Heatmap")
plt.savefig('weather_heatmap.png')
print("Plot saved as weather_heatmap.png")
