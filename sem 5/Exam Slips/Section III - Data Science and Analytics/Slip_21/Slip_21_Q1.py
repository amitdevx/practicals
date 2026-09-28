import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

df = pd.DataFrame({
    'Temperature': [28, 30, 25, 32, 22, 29, 35],
    'Humidity': [65, 70, 80, 55, 85, 60, 45],
    'Rainfall': [12, 18, 45, 5, 60, 8, 0],
    'WindSpeed': [15, 12, 20, 10, 25, 14, 8]
})

corr = df.corr()
plt.figure(figsize=(6, 5))
sns.heatmap(corr, annot=True, cmap='coolwarm', fmt='.2f')
plt.title('Correlation Heatmap (Slip 21)')
plt.tight_layout()
plt.savefig('ds_slip_21_q1.png')
print("[+] Heatmap saved.")
