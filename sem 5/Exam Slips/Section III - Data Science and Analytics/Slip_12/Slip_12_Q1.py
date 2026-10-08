import pandas as pd
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import seaborn as sns

data = {
    'Pclass': [1, 3, 3, 1, 2, 3, 1, 3, 2, 2],
    'Survived': [1, 0, 1, 1, 0, 0, 0, 1, 1, 0]
}
df = pd.DataFrame(data)

plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
sns.histplot(df['Pclass'], bins=3, kde=False)
plt.title('Passenger Class Histogram')
plt.xticks([1, 2, 3])

plt.subplot(1, 2, 2)
survived_counts = df['Survived'].value_counts()
plt.pie(survived_counts, labels=['Died', 'Survived'], autopct='%1.1f%%', colors=['red', 'green'])
plt.title('Survival Distribution')

plt.tight_layout()
plt.savefig('titanic_plots.png')
print("Saved titanic_plots.png")
