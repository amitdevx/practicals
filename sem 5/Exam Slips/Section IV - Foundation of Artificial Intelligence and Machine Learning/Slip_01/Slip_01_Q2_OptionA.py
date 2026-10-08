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
    'A': [('B', 1), ('C', 4)],
    'B': [('D', 2), ('E', 5)],
    'C': [('F', 3)],
    'D': [('G', 3)],
    'E': [('G', 1)],
    'F': [('G', 2)],
    'G': []
}
heuristics = {'A': 6, 'B': 5, 'C': 4, 'D': 3, 'E': 2, 'F': 2, 'G': 0}

path, cost = a_star_search(graph, heuristics, 'A', 'G')
print("\nA* Search Algorithm\n")
print("Optimal Path:", " -> ".join(path))
print("Total Path Cost:", cost)
