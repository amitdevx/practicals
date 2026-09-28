import pandas as pd
from itertools import combinations

# Apriori Market Basket Analysis on Video Dataset
dataset = {
    'TID': [1, 2, 3, 4, 5],
    'Items': [
        ['Python Tutorial', 'Data Science', 'Machine Learning'],
        ['Data Science', 'Machine Learning'],
        ['Python Tutorial', 'Web Development'],
        ['Python Tutorial', 'Data Science', 'Deep Learning'],
        ['Machine Learning', 'Deep Learning']
    ]
}

df = pd.DataFrame(dataset)
print("--- Learning Video Transactions ---")
print(df)

min_support = 0.4
total_tx = len(df)

# Frequency count of single items
item_counts = {}
for items in df['Items']:
    for item in items:
        item_counts[item] = item_counts.get(item, 0) + 1

frequent_1 = {k: v/total_tx for k, v in item_counts.items() if (v/total_tx) >= min_support}
print(f"\nFrequent 1-Itemsets (min_support >= {min_support}):")
for k, v in frequent_1.items():
    print(f"{{{k}}}: Support = {v:.2f}")
