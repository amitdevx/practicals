import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

data = {
    'Price': [250, 300, 150, 800, 220, 1200, 280, 310, 190, 260],
    'Rating': [4.2, 4.5, 3.8, 4.9, 4.0, 4.8, 4.3, 4.1, 3.9, 4.4],
    'Number_of_Sales': [1200, 1500, 800, 3000, 1100, 4500, 1300, 1400, 950, 1250]
}

df = pd.DataFrame(data)
print("--- Products Dataset ---")
print(df)

# Boxplots for outlier detection
plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
sns.boxplot(y=df['Price'], color='skyblue')
plt.title('Boxplot of Price (Outlier Detection)')

plt.subplot(1, 2, 2)
sns.boxplot(y=df['Rating'], color='lightgreen')
plt.title('Boxplot of Rating')
plt.tight_layout()
plt.savefig('ds_slip_01_q1_boxplot.png')
print("[+] Plot saved as ds_slip_01_q1_boxplot.png")
