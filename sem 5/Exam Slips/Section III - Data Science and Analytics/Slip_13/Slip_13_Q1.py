import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

df = pd.DataFrame({'Daily_Sales': [2500, 2800, 3100, 2200, 2900, 8500, 2700, 2600, 9200, 2400]})
df.to_csv('sales.csv', index=False)

plt.figure(figsize=(6, 4))
sns.boxplot(y=df['Daily_Sales'], color='salmon')
plt.title('Daily Sales Outlier Detection')
plt.tight_layout()
plt.savefig('ds_slip_13_q1.png')
print("[+] Boxplot saved.")
