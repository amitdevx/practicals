import pandas as pd
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import seaborn as sns

data = {
    'Day': list(range(1, 31)),
    'Sales': [100, 150, 130, 170, 160, 180, 140, 190, 200, 150, 
              160, 170, 140, 130, 800, 150, 160, 175, 185, 145, 
              155, 165, 170, 150, 140, 160, 180, 190, 150, 160] # 800 is an outlier
}
df = pd.DataFrame(data)

plt.figure(figsize=(8,6))
sns.boxplot(y=df['Sales'], color='orange')
plt.title('Daily Sales Distribution (Outlier Detection)')
plt.ylabel('Sales Volume')
plt.savefig('sales_boxplot.png')
print("Saved sales_boxplot.png")
