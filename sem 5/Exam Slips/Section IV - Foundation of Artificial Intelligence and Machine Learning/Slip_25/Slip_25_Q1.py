def ao_star_evaluate():
    # Leaf nodes heuristic = 0
    H = I = J = F = G = 0
    
    # OR nodes
    D = min(2 + H, 3 + I)
    E = 1 + J
    C = min(2 + F, 5 + G)
    
    # AND node B
    B = (1 + D) + (4 + E)
    
    # OR node A (root)
    A = min(2 + B, 3 + C)
    return A

print("=== AO* Search Algorithm (AND-OR Graphs) ===")
print("Evaluating AND-OR graph from root: A")
cost = ao_star_evaluate()
print(f"AO* Solution Path Cost: {cost}")
