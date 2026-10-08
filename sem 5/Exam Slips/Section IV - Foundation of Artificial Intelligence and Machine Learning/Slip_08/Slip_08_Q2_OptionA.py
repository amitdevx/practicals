import math

class GameNode:
    def __init__(self, value=None, children=None):
        self.value = value
        self.children = children if children else []

def minimax(node, depth, is_maximizing):
    global minimax_evaluations
    minimax_evaluations += 1
    
    if depth == 0 or not node.children:
        return node.value

    if is_maximizing:
        best_val = -math.inf
        for child in node.children:
            val = minimax(child, depth - 1, False)
            best_val = max(best_val, val)
        return best_val
    else:
        best_val = math.inf
        for child in node.children:
            val = minimax(child, depth - 1, True)
            best_val = min(best_val, val)
        return best_val

def alphabeta(node, depth, alpha, beta, is_maximizing):
    global alphabeta_evaluations
    alphabeta_evaluations += 1
    
    if depth == 0 or not node.children:
        return node.value

    if is_maximizing:
        best_val = -math.inf
        for child in node.children:
            val = alphabeta(child, depth - 1, alpha, beta, False)
            best_val = max(best_val, val)
            alpha = max(alpha, best_val)
            if beta <= alpha:
                break
        return best_val
    else:
        best_val = math.inf
        for child in node.children:
            val = alphabeta(child, depth - 1, alpha, beta, True)
            best_val = min(best_val, val)
            beta = min(beta, best_val)
            if beta <= alpha:
                break
        return best_val

if __name__ == '__main__':
    # Tree structure:
    #         MAX
    #       /     \
    #    MIN       MIN
    #   /   \     /   \
    #  3     5   2     9
    #
    # With Alpha-Beta, when evaluating the right MIN node:
    # After seeing '2', MIN knows its value is <= 2.
    # The MAX root already knows it can get at least 3 (from the left MIN node).
    # Since 2 <= 3, MAX won't choose the right MIN node. So pruning occurs.
    
    leaf1 = GameNode(value=3)
    leaf2 = GameNode(value=5)
    leaf3 = GameNode(value=2)
    leaf4 = GameNode(value=9)
    
    min_node1 = GameNode(children=[leaf1, leaf2])
    min_node2 = GameNode(children=[leaf3, leaf4])
    
    root = GameNode(children=[min_node1, min_node2])
    
    minimax_evaluations = 0
    alphabeta_evaluations = 0
    
    val_mm = minimax(root, 2, True)
    val_ab = alphabeta(root, 2, -math.inf, math.inf, True)
    
    print("\nComparison: Minimax vs Alpha-Beta Pruning\n")
    print(f"Minimax Optimal Value: {val_mm}")
    print(f"Nodes Evaluated (Minimax): {minimax_evaluations}")
    print()
    print(f"Alpha-Beta Optimal Value: {val_ab}")
    print(f"Nodes Evaluated (Alpha-Beta): {alphabeta_evaluations}")
