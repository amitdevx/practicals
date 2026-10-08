import pandas as pd
from mlxtend.preprocessing import TransactionEncoder
from mlxtend.frequent_patterns import apriori, association_rules

transactions = [
    ['Video Lecture', 'Quiz'],
    ['Video Lecture', 'Assignment'],
    ['Quiz', 'Discussion Forum'],
    ['Video Lecture', 'Quiz', 'Assignment'],
    ['Assignment', 'Discussion Forum'],
    ['Video Lecture', 'Certificate'],
    ['Quiz', 'Certificate'],
    ['Video Lecture', 'Quiz'],
    ['Assignment', 'Certificate'],
    ['Video Lecture', 'Quiz', 'Certificate']
]

te = TransactionEncoder()
te_ary = te.fit(transactions).transform(transactions)
df = pd.DataFrame(te_ary, columns=te.columns_)

for min_supp in [0.3, 0.4]:
    print(f"\n--- min_support = {min_supp} ---")
    freq_items = apriori(df, min_support=min_supp, use_colnames=True)
    print("Frequent Itemsets:\n", freq_items)
    if not freq_items.empty:
        rules = association_rules(freq_items, metric="confidence", min_threshold=0.5)
        print("Rules:\n", rules[['antecedents', 'consequents', 'support', 'confidence']])
