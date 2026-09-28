# Backward Chaining Inference Engine
rules = {
    'C': ['A', 'B'],
    'D': ['C'],
    'E': ['D', 'F']
}
facts = {'A', 'B', 'F'}

def backward_chain(goal, visited=None):
    if visited is None: visited = set()
    print(f"[Investigating Goal] {goal}")
    if goal in facts:
        return True

    if goal not in rules or goal in visited:
        return False
    visited.add(goal)

    premises = rules[goal]
    for p in premises:
        if not backward_chain(p, visited):
            return False
    return True

target_goal = 'E'
print("=== Backward Chaining Inference ===")
print("Known Facts:", facts)
result = backward_chain(target_goal)
print(f"Goal '{target_goal}' Proven:", result)
