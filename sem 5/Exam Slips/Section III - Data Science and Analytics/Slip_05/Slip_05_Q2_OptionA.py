import pandas as pd
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib_venn import venn2

# Simulate data
data = {
    'Customer_ID': range(1, 101),
    'Uses_Netflix': [1]*60 + [0]*40,
    'Uses_Amazon': [1]*30 + [0]*30 + [1]*20 + [0]*20
}
df = pd.DataFrame(data)

# Count overlaps
only_netflix = len(df[(df['Uses_Netflix'] == 1) & (df['Uses_Amazon'] == 0)])
only_amazon = len(df[(df['Uses_Netflix'] == 0) & (df['Uses_Amazon'] == 1)])
both = len(df[(df['Uses_Netflix'] == 1) & (df['Uses_Amazon'] == 1)])

# Plot Venn Diagram
plt.figure(figsize=(12, 5))

plt.subplot(1, 2, 1)
venn2(subsets=(only_netflix, only_amazon, both), set_labels=('Netflix', 'Amazon Prime'))
plt.title('Streaming Service Users (Venn Diagram)')

# Plot Pie Chart
plt.subplot(1, 2, 2)
labels = ['Only Netflix', 'Only Amazon Prime', 'Both']
sizes = [only_netflix, only_amazon, both]
colors = ['#ff9999', '#66b3ff', '#99ff99']
plt.pie(sizes, labels=labels, autopct='%1.1f%%', startangle=140, colors=colors)
plt.title('Streaming Service Users (Pie Chart)')

plt.tight_layout()
plt.savefig('streaming_services.png')
print("Plots saved as streaming_services.png")
