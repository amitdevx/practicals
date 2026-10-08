import pandas as pd
import matplotlib.pyplot as plt
import matplotlib
matplotlib.use('Agg')

df = pd.DataFrame({
    'Fuel_Efficiency': [15, 18, 20, 16, 50],
    'Engine_Power': [100, 120, 110, 115, 300],
    'Vehicle_Weight': [1.5, 1.6, 1.4, 1.5, 2.0],
    'Engine_Size': [1.2, 1.5, 1.4, 1.2, 3.5],
    'Acceleration': [10, 9, 8, 9.5, 5]
})

plt.figure()
df[['Fuel_Efficiency', 'Engine_Power']].boxplot()
plt.title("Box Plots for Fuel Efficiency and Engine Power")
plt.savefig('vehicle_boxplots.png')
print("Boxplot saved. Identified outliers visually.")
