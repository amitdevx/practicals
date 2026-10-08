import pandas as pd
from mlxtend.preprocessing import TransactionEncoder
from mlxtend.frequent_patterns import apriori, association_rules

# Given dataset
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

# Preprocess data
te = TransactionEncoder()
te_ary = te.fit(transactions).transform(transactions)
df = pd.DataFrame(te_ary, columns=te.columns_)

for min_supp in [0.2, 0.3]:
    print(f"\n--- Analysis with min_support = {min_supp} ---")
    frequent_itemsets = apriori(df, min_support=min_supp, use_colnames=True)
    print("Frequent Itemsets:\n", frequent_itemsets)
    
    if len(frequent_itemsets) > 0:
        # Generate rules using a suitable confidence metric, e.g., min_threshold=0.5
        rules = association_rules(frequent_itemsets, metric="confidence", min_threshold=0.5)
        print("\nAssociation Rules:\n", rules[['antecedents', 'consequents', 'support', 'confidence']])
    else:
        print("\nNo frequent itemsets found.")
