import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import matplotlib
matplotlib.use('Agg')

df = pd.DataFrame({
    'Study Hours': [2, 4, 5, 8],
    'Attendance': [70, 80, 85, 95],
    'Assignment Score': [15, 20, 22, 28],
    'Exam Score': [50, 60, 75, 90]
})

corr = df.corr()
print("Correlation Matrix:\n", corr)

plt.figure()
sns.heatmap(corr, annot=True, cmap='coolwarm')
plt.title("Student Performance Correlation Heatmap")
plt.savefig('heatmap.png')
print("Plot saved as heatmap.png")
