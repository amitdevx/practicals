import pandas as pd
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import seaborn as sns

# Create dataframe
data = {
    'Vehicle': ['V1', 'V2', 'V3', 'V4', 'V5'],
    'Fuel_Efficiency': [15, 16, 14, 50, 15],  # 50 is an outlier
    'Engine_Power': [100, 110, 105, 102, 500], # 500 is an outlier
    'Vehicle_Weight': [1200, 1300, 1250, 1220, 1240],
    'Engine_Size': [1.5, 1.6, 1.4, 1.5, 1.5],
    'Acceleration': [10.5, 11.0, 10.2, 10.8, 10.6]
}
df = pd.DataFrame(data)

print("Vehicle Dataset:")
print(df)

# Create Box Plots to identify outliers
plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
sns.boxplot(y=df['Fuel_Efficiency'], color='skyblue')
plt.title('Boxplot of Fuel Efficiency')

plt.subplot(1, 2, 2)
sns.boxplot(y=df['Engine_Power'], color='lightgreen')
plt.title('Boxplot of Engine Power')

plt.tight_layout()
plt.savefig('ds_slip_03_q1_boxplots.png')
print("Boxplots saved as ds_slip_03_q1_boxplots.png")
