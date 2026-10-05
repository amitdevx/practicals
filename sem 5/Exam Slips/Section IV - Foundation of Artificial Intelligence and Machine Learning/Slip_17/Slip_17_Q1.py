import heapq

def a_star_search(graph, heuristics, start, goal):
    pq = [(heuristics[start], 0, start, [start])]
    visited = {}

    while pq:
        f, g, current, path = heapq.heappop(pq)
        if current == goal:
            return path, g

        if current in visited and visited[current] <= g:
            continue
        visited[current] = g

        for neighbor, weight in graph.get(current, []):
            cost = g + weight
            est_total = cost + heuristics.get(neighbor, 0)
            heapq.heappush(pq, (est_total, cost, neighbor, path + [neighbor]))
    return None, float('inf')

graph = {
    'A': [('B', 2), ('C', 4)],
    'B': [('A', 2), ('D', 3), ('E', 5)],
    'C': [('A', 4), ('F', 1)],
    'D': [('B', 3), ('F', 2)],
    'E': [('B', 5), ('F', 1)],
    'F': [('C', 1), ('D', 2), ('E', 1)]
}
heuristics = {'A': 6, 'B': 5, 'C': 3, 'D': 2, 'E': 1, 'F': 0}

print("=== A* Search Algorithm ===")
path, cost = a_star_search(graph, heuristics, 'A', 'F')
if path:
    print("Optimal Path:", " -> ".join(path))
    print("Total Cost:", cost)
else:
    print("Goal not found.")
