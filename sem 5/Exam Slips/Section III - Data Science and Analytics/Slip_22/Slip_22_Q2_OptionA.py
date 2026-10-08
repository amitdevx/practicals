import pandas as pd
import matplotlib.pyplot as plt
from matplotlib_venn import venn2
import matplotlib
matplotlib.use('Agg')

df = pd.DataFrame({
    'Customer_ID': [1, 2, 3, 4, 5],
    'Netflix': [1, 1, 0, 1, 0],
    'Amazon_Prime': [0, 1, 1, 1, 0]
})

netflix_users = set(df[df['Netflix'] == 1]['Customer_ID'])
amazon_users = set(df[df['Amazon_Prime'] == 1]['Customer_ID'])

# Venn Diagram
plt.figure()
venn2([netflix_users, amazon_users], set_labels=('Netflix', 'Amazon Prime'))
plt.title("Customers using Netflix and Amazon Prime")
plt.savefig('streaming_venn.png')

# Pie Chart
only_netflix = len(netflix_users - amazon_users)
only_amazon = len(amazon_users - netflix_users)
both = len(netflix_users.intersection(amazon_users))

labels = ['Only Netflix', 'Only Amazon Prime', 'Both']
sizes = [only_netflix, only_amazon, both]

plt.figure()
plt.pie(sizes, labels=labels, autopct='%1.1f%%', colors=['red', 'blue', 'purple'])
plt.title("Streaming Service Usage")
plt.savefig('streaming_pie.png')
print("Plots saved.")
