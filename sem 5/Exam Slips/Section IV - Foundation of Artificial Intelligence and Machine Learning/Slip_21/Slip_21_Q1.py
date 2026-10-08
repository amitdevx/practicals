def dls(graph, node, goal, depth):
    if depth == 0 and node == goal: return True
    if depth > 0:
        for neighbor in graph.get(node, []):
            if dls(graph, neighbor, goal, depth - 1): return True
    return False

def ids(graph, start, goal, max_depth):
    for depth in range(max_depth):
        if dls(graph, start, goal, depth):
            return depth
    return -1

graph = {'A': ['B', 'C'], 'B': ['D', 'E'], 'C': ['F'], 'D': [], 'E': [], 'F': []}
depth_found = ids(graph, 'A', 'E', 5)
print("\nIterative Deepening Search\n")
print("Found 'E' at depth:" if depth_found != -1 else "Not found", depth_found)
