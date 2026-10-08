facts = {'A'}
rules = {'A': 'B', 'B': 'C'}

def forward_chaining(facts, rules, target):
    new_facts = set(facts)
    while True:
        added = False
        for premise, conclusion in rules.items():
            if premise in new_facts and conclusion not in new_facts:
                new_facts.add(conclusion)
                added = True
        if target in new_facts:
            return True
        if not added:
            return False

print("\nForward Chaining\n")
print("Can we prove C?", forward_chaining(facts, rules, 'C'))
