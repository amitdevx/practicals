from collections import deque

def bfs(graph, start):
    visited = set()
    queue = deque([start])
    visited.add(start)
    traversal = []

    while queue:
        vertex = queue.popleft()
        traversal.append(vertex)
        for neighbor in sorted(graph.get(vertex, [])):
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)
    return traversal

graph = {
    'V1': ['V2', 'V3', 'V5'],
    'V2': ['V1', 'V4'],
    'V3': ['V1', 'V4'],
    'V4': ['V2', 'V3', 'V5'],
    'V5': ['V1', 'V4']
}

print("\nBFS Graph Traversal\n")
print("BFS Order starting from V1:", " -> ".join(bfs(graph, 'V1')))
