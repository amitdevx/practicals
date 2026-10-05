def dls_search(graph, node, target, limit, depth=0, path=None):
    if path is None: path = []
    path.append(node)
    if node == target: return True, path
    if depth >= limit: return False, None

    for neighbor in graph.get(node, []):
        if neighbor not in path:
            found, res_path = dls_search(graph, neighbor, target, limit, depth + 1, list(path))
            if found: return True, res_path
    return False, None

def iterative_deepening(graph, start, target, max_depth=10):
    for depth in range(max_depth):
        print(f"Searching with depth limit = {depth}...")
        found, path = dls_search(graph, start, target, depth)
        if found:
            return path
    return None

graph = {
    'A': ['B', 'C'],
    'B': ['D', 'E'],
    'C': ['F'],
    'D': [], 'E': [], 'F': []
}

target = 'F'
print("=== Iterative Deepening Search (IDS) ===")
path = iterative_deepening(graph, 'A', target, max_depth=5)
if path:
    print("Goal reached with path:", " -> ".join(path))
else:
    print("Goal not found.")
