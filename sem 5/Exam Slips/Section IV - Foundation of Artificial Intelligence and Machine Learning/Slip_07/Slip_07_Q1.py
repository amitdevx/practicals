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
    'V1': [('V2', 2), ('V3', 4)],
    'V2': [('V3', 1), ('V4', 7)],
    'V3': [('V5', 3)],
    'V4': [('V6', 1)],
    'V5': [('V4', 2), ('V6', 5)],
    'V6': []
}
heuristics = {'V1': 6, 'V2': 5, 'V3': 4, 'V4': 1, 'V5': 2, 'V6': 0}

path, cost = a_star_search(graph, heuristics, 'V1', 'V6')
print("\nA* Search Algorithm\n")
if path:
    print("Optimal Path:", " -> ".join(path))
    print("Total Path Cost:", cost)
else:
    print("No path found.")
