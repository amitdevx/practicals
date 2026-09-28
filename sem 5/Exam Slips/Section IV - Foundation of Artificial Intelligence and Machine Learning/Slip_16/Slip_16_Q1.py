def dls(graph, node, target, limit, depth=0, path=None):
    if path is None: path = []
    path.append(node)

    if node == target:
        return True, path
    if depth >= limit:
        return False, None

    for neighbor in graph.get(node, []):
        if neighbor not in path:
            found, res_path = dls(graph, neighbor, target, limit, depth + 1, list(path))
            if found:
                return True, res_path
    return False, None

graph = {
    '1': ['2', '3'],
    '2': ['4', '5'],
    '3': ['6', '7'],
    '4': ['8'],
    '5': [], '6': [], '7': [], '8': []
}

limit = 2
target = '8'
print(f"=== Depth Limited Search (DLS) (Limit: {limit}, Target: {target}) ===")
found, path = dls(graph, '1', target, limit)
if found:
    print("Target found along path:", " -> ".join(path))
else:
    print(f"Target '{target}' NOT found within depth limit {limit}.")
