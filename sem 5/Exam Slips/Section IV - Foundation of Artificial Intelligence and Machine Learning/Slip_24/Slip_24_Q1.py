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

graph = {'A': [('B', 1)], 'B': [('C', 2)], 'C': []}
heuristics = {'A': 2, 'B': 1, 'C': 0}
print("\nA* Search Algorithm\n")
path, cost = a_star_search(graph, heuristics, 'A', 'C')
print("Path:", path, "Cost:", cost)
