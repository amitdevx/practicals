import math

def alphabeta(depth, node_idx, is_max, scores, alpha, beta, height):
    if depth == height:
        return scores[node_idx]

    if is_max:
        best = -math.inf
        for i in range(2):
            val = alphabeta(depth + 1, node_idx * 2 + i, False, scores, alpha, beta, height)
            best = max(best, val)
            alpha = max(alpha, best)
            if beta <= alpha:
                print(f"[Pruning] Pruned at depth {depth}, node {node_idx*2+i}")
                break
        return best
    else:
        best = math.inf
        for i in range(2):
            val = alphabeta(depth + 1, node_idx * 2 + i, True, scores, alpha, beta, height)
            best = min(best, val)
            beta = min(beta, best)
            if beta <= alpha:
                print(f"[Pruning] Pruned at depth {depth}, node {node_idx*2+i}")
                break
        return best

scores = [3, 5, 6, 9, 1, 2, 0, -1]
height = int(math.log2(len(scores)))

print("=== Alpha-Beta Pruning Simulation ===")
optimal = alphabeta(0, 0, True, scores, -math.inf, math.inf, height)
print("Optimal Game Value at Root:", optimal)
