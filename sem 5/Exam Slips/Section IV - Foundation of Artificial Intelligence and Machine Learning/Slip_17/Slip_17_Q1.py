import heapq

def best_first_search(graph, heuristics, start, goal):
    pq = [(heuristics[start], start, [start])]
    visited = set()

    while pq:
        _, current, path = heapq.heappop(pq)
        
        if current == goal:
            return path
            
        if current in visited:
            continue
        visited.add(current)
        
        for neighbor in graph.get(current, []):
            if neighbor not in visited:
                heapq.heappush(pq, (heuristics.get(neighbor, 0), neighbor, path + [neighbor]))
    return None

graph = {
    'S': ['A', 'B'],
    'A': ['C', 'D'],
    'B': ['E', 'F'],
    'C': [], 'D': [], 'E': ['G'], 'F': [], 'G': []
}
heuristics = {'S': 10, 'A': 5, 'B': 4, 'C': 4, 'D': 3, 'E': 2, 'F': 6, 'G': 0}

print("\nBest First Search Algorithm\n")
path = best_first_search(graph, heuristics, 'S', 'G')
if path:
    print("Path found:", " -> ".join(path))
else:
    print("Goal not found.")
