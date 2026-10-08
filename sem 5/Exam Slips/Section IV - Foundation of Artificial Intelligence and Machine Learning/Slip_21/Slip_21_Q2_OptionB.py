def is_safe(node, color, graph, colors):
    for neighbor in graph.get(node, []):
        if colors.get(neighbor) == color:
            return False
    return True

def graph_coloring(graph, m, colors, nodes, idx):
    if idx == len(nodes):
        return True
    
    node = nodes[idx]
    for c in range(1, m + 1):
        if is_safe(node, c, graph, colors):
            colors[node] = c
            if graph_coloring(graph, m, colors, nodes, idx + 1):
                return True
            colors[node] = 0
    return False

graph = {'A': ['B', 'C'], 'B': ['A', 'C'], 'C': ['A', 'B']}
colors = {node: 0 for node in graph}
print("\nMap Colouring (CSP)\n")
if graph_coloring(graph, 3, colors, list(graph.keys()), 0):
    print("Colors assigned:", colors)
else:
    print("No solution")
