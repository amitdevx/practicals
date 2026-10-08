import math

# A simple game tree representation
tree = {
    'A': ['B', 'C'],
    'B': ['D', 'E'],
    'C': ['F', 'G'],
    'D': ['H', 'I'],
    'E': ['J', 'K'],
    'F': ['L', 'M'],
    'G': ['N', 'O']
}
leaves = {
    'H': 3, 'I': 5, 'J': 6, 'K': 9, 'L': 1, 'M': 2, 'N': 0, 'O': -1
}

# Minimax
minimax_nodes = 0
def minimax(node, is_max):
    global minimax_nodes
    minimax_nodes += 1
    if node in leaves:
        return leaves[node]
    
    if is_max:
        best = -math.inf
        for child in tree[node]:
            val = minimax(child, False)
            best = max(best, val)
        return best
    else:
        best = math.inf
        for child in tree[node]:
            val = minimax(child, True)
            best = min(best, val)
        return best

# Alpha-Beta Pruning
alphabeta_nodes = 0
def alphabeta(node, alpha, beta, is_max):
    global alphabeta_nodes
    alphabeta_nodes += 1
    if node in leaves:
        return leaves[node]
    
    if is_max:
        best = -math.inf
        for child in tree[node]:
            val = alphabeta(child, alpha, beta, False)
            best = max(best, val)
            alpha = max(alpha, best)
            if beta <= alpha:
                break
        return best
    else:
        best = math.inf
        for child in tree[node]:
            val = alphabeta(child, alpha, beta, True)
            best = min(best, val)
            beta = min(beta, best)
            if beta <= alpha:
                break
        return best

print("\nComparing Minimax and Alpha-Beta Pruning\n")
val_mm = minimax('A', True)
val_ab = alphabeta('A', -math.inf, math.inf, True)

print(f"Game Tree Value (Minimax): {val_mm}")
print(f"Nodes Evaluated by Minimax: {minimax_nodes}")
print(f"Game Tree Value (Alpha-Beta): {val_ab}")
print(f"Nodes Evaluated by Alpha-Beta: {alphabeta_nodes}")

if alphabeta_nodes < minimax_nodes:
    print("\nConclusion: Alpha-Beta pruning successfully evaluated fewer nodes!")
else:
    print("\nConclusion: No pruning occurred in this tree structure.")
