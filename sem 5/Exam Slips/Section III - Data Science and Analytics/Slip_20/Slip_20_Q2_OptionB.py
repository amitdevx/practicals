import pandas as pd
from mlxtend.preprocessing import TransactionEncoder
from mlxtend.frequent_patterns import apriori, association_rules

data = [
    ['Library', 'Seminar'],
    ['Workshop', 'Project'],
    ['Library', 'Assignment'],
    ['Seminar', 'Workshop'],
    ['Assignment', 'Seminar'],
    ['Workshop', 'Assignment'],
    ['Project', 'Library'],
    ['Library', 'Seminar', 'Project'],
    ['Library', 'Seminar', 'Workshop']
]

te = TransactionEncoder()
te_ary = te.fit(data).transform(data)
df = pd.DataFrame(te_ary, columns=te.columns_)

for min_sup in [0.2, 0.3]:
    print(f"\n--- Analysis with min_support={min_sup} ---")
    freq_items = apriori(df, min_support=min_sup, use_colnames=True)
    print("Frequent Itemsets:\n", freq_items)
    if not freq_items.empty:
        rules = association_rules(freq_items, metric="confidence", min_threshold=0.5)
        print("Association Rules:\n", rules)
