# Backward Chaining Inference Mechanism

# Rules: Dictionary mapping conclusions to lists of premises (AND condition)
rules = {
    'C': ['A', 'B'],
    'D': ['C'],
    'E': ['D', 'F']
}

# Initial Facts
facts = {'A', 'B', 'F'}

def backward_chaining(goal, visited=None):
    if visited is None: 
        visited = set()
        
    print(f"[Investigating Goal] {goal}")
    if goal in facts:
        print(f"Goal '{goal}' is a known fact.")
        return True

    if goal not in rules or goal in visited:
        print(f"Cannot prove '{goal}'")
        return False
        
    visited.add(goal)
    
    # Check all premises for the goal
    premises = rules[goal]
    for p in premises:
        if not backward_chaining(p, visited):
            print(f"Failed to prove premise '{p}' for goal '{goal}'.")
            return False
            
    print(f"Successfully proved '{goal}' using its premises.")
    facts.add(goal) # Add proven fact
    return True

if __name__ == "__main__":
    target_goal = 'E'
    print("\nBackward Chaining Inference\n")
    print("Initial Known Facts:", facts)
    print("Rules:")
    for k, v in rules.items():
        print(f"  If {' AND '.join(v)} Then {k}")
    
    print("\nStarting Backward Chaining...")
    result = backward_chaining(target_goal)
    print(f"\nFinal Result: Goal '{target_goal}' Proven: {result}")
    print("Updated Known Facts:", facts)
