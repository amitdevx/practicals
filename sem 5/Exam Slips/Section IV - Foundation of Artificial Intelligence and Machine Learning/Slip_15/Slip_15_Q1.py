def dfs(graph, start, visited=None, traversal=None):
    if visited is None: visited = set()
    if traversal is None: traversal = []

    visited.add(start)
    traversal.append(start)
    for neighbor in sorted(graph.get(start, [])):
        if neighbor not in visited:
            dfs(graph, neighbor, visited, traversal)
    return traversal

graph = {
    '1': ['2', '3', '4'],
    '2': ['1', '5'],
    '3': ['1', '6'],
    '4': ['1', '7'],
    '5': ['2'],
    '6': ['3'],
    '7': ['4']
}

print("=== DFS Graph Traversal ===")
print("DFS Order starting from 1:", " -> ".join(dfs(graph, '1')))
