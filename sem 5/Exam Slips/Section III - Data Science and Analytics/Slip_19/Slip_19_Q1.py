import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

data = {
    'Fuel_Efficiency': [18.5, 22.0, 15.2, 12.0, 25.4, 8.5, 19.0, 21.5],
    'Engine_Size': [2.0, 1.6, 3.0, 4.0, 1.2, 6.2, 1.8, 1.5],
    'Engine_Power': [150, 120, 220, 310, 85, 450, 140, 110]
}
df = pd.DataFrame(data)

plt.figure(figsize=(8, 5))
sns.scatterplot(x='Engine_Size', y='Fuel_Efficiency', data=df, hue='Engine_Power', palette='viridis', s=100)
plt.title('Vehicle Engine Size vs Fuel Efficiency (Slip 19)')
plt.tight_layout()
plt.savefig('ds_slip_19_q1.png')
print("[+] Scatter plot saved.")
