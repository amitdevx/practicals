# Forward Chaining Inference Engine
facts = {'A', 'B'}
rules = [
    ({'A', 'B'}, 'C'),
    ({'C', 'D'}, 'E'),
    ({'C'}, 'F'),
    ({'F'}, 'Goal_Reached')
]

def forward_chaining(facts, rules, goal):
    inferred = set(facts)
    new_inferred = True

    while new_inferred:
        new_inferred = False
        for premises, conclusion in rules:
            if premises.issubset(inferred) and conclusion not in inferred:
                inferred.add(conclusion)
                print(f"[Rule Fired] {premises} -> {conclusion}")
                new_inferred = True
                if conclusion == goal:
                    return True
    return False

print("=== Forward Chaining Inference ===")
print("Initial Facts:", facts)
success = forward_chaining(facts, rules, 'Goal_Reached')
print("Goal Achieved:", success)
