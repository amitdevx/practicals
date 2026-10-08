import pandas as pd
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

data = {
    'Car_Model': ['M1', 'M2', 'M3', 'M4', 'M5'],
    'Engine_Size': [1.2, 1.5, 2.0, 1.8, 2.5],
    'Fuel_Efficiency': [20.5, 18.2, 14.0, 15.5, 12.0]
}
df = pd.DataFrame(data)

plt.figure(figsize=(8,6))
colors = ['red', 'blue', 'green', 'orange', 'purple']
plt.scatter(df['Engine_Size'], df['Fuel_Efficiency'], c=colors)
plt.title('Engine Size vs Fuel Efficiency')
plt.xlabel('Engine Size (Litres)')
plt.ylabel('Fuel Efficiency (km/L)')
plt.savefig('scatter_plot.png')
print("Saved as scatter_plot.png")
