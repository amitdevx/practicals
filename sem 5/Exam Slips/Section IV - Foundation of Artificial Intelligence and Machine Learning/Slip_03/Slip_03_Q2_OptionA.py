import math

def alphabeta(node, depth, is_max, alpha, beta):
    if isinstance(node, int):
        return node
        
    if is_max:
        best = -math.inf
        for child in node:
            val = alphabeta(child, depth + 1, False, alpha, beta)
            best = max(best, val)
            alpha = max(alpha, best)
            if beta <= alpha:
                print(f"[Pruning] Pruned at MAX node")
                break
        return best
    else:
        best = math.inf
        for child in node:
            val = alphabeta(child, depth + 1, True, alpha, beta)
            best = min(best, val)
            beta = min(beta, best)
            if beta <= alpha:
                print(f"[Pruning] Pruned at MIN node")
                break
        return best

# Root is MAX, next level is MIN
# Tree structure from image:
# Root -> A, B, C
# A -> 3, 5
# B -> 2, 9
# C -> 0, 7
tree = [
    [3, 5], # A
    [2, 9], # B
    [0, 7]  # C
]

print("\nAlpha-Beta Pruning Simulation\n")
optimal = alphabeta(tree, 0, True, -math.inf, math.inf)
print("Optimal Game Value at Root:", optimal)
