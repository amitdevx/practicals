import heapq

def a_star_search(graph, heuristics, start, goal):
    # priority queue stores (f_score, current_cost, current_node, path)
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
    'S': [('A', 1), ('G', 10)],
    'A': [('B', 2), ('C', 1)],
    'B': [('D', 5)],
    'C': [('D', 3), ('G', 4)],
    'D': [('G', 2)],
    'G': []
}
heuristics = {'S': 5, 'A': 3, 'B': 4, 'C': 2, 'D': 6, 'G': 0}

path, cost = a_star_search(graph, heuristics, 'S', 'G')
print("=== A* Search Algorithm ===")
print("Optimal Path:", " -> ".join(path))
print("Total Path Cost:", cost)
