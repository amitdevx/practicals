# AI & ML Search Algorithms and Models in Python

def get_bfs_c():
    return '''from collections import deque

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

print("=== BFS Graph Traversal ===")
print("BFS Order starting from V1:", " -> ".join(bfs(graph, 'V1')))
'''

def get_dfs_c():
    return '''def dfs(graph, start, visited=None, traversal=None):
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
'''

def get_astar_c():
    return '''import heapq

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
'''

def get_water_jug_c():
    return '''from collections import deque

def solve_water_jug(capA, capB, target):
    visited = set()
    queue = deque([(0, 0, [])]) # (jugA, jugB, path)

    while queue:
        a, b, path = queue.popleft()
        if a == target or b == target:
            return path + [(a, b)]

        if (a, b) in visited:
            continue
        visited.add((a, b))

        # Possible operations:
        moves = [
            (capA, b, "Fill Jug A"),
            (a, capB, "Fill Jug B"),
            (0, b, "Empty Jug A"),
            (a, 0, "Empty Jug B"),
            (a - min(a, capB - b), b + min(a, capB - b), "Pour A into B"),
            (a + min(b, capA - a), b - min(b, capA - a), "Pour B into A")
        ]

        for na, nb, action in moves:
            if (na, nb) not in visited:
                queue.append((na, nb, path + [(a, b)]))
    return None

capA, capB, target = 4, 3, 2
solution = solve_water_jug(capA, capB, target)
print(f"=== Water Jug Problem ({capA}L, {capB}L -> Target {target}L) ===")
for step, (a, b) in enumerate(solution):
    print(f"Step {step}: Jug A = {a}L, Jug B = {b}L")
'''

def get_map_coloring_c():
    return '''def is_safe(node, color, assignment, graph):
    for neighbor in graph[node]:
        if neighbor in assignment and assignment[neighbor] == color:
            return False
    return True

def solve_csp(nodes, colors, assignment, graph):
    if len(assignment) == len(nodes):
        return assignment

    unassigned = [n for n in nodes if n not in assignment][0]
    for color in colors:
        if is_safe(unassigned, color, assignment, graph):
            assignment[unassigned] = color
            result = solve_csp(nodes, colors, assignment, graph)
            if result:
                return result
            del assignment[unassigned]
    return None

graph = {
    'WA': ['NT', 'SA'],
    'NT': ['WA', 'SA', 'Q'],
    'SA': ['WA', 'NT', 'Q', 'NSW', 'V'],
    'Q': ['NT', 'SA', 'NSW'],
    'NSW': ['Q', 'SA', 'V'],
    'V': ['SA', 'NSW'],
    'T': []
}
nodes = list(graph.keys())
colors = ['Red', 'Green', 'Blue']

coloring = solve_csp(nodes, colors, {}, graph)
print("=== Map Coloring CSP Solution ===")
for region, color in coloring.items():
    print(f"{region}: {color}")
'''

def get_minimax_c():
    return '''import math

def minimax(depth, node_index, is_max, scores, height):
    if depth == height:
        return scores[node_index]

    if is_max:
        return max(minimax(depth + 1, node_index * 2, False, scores, height),
                   minimax(depth + 1, node_index * 2 + 1, False, scores, height))
    else:
        return min(minimax(depth + 1, node_index * 2, True, scores, height),
                   minimax(depth + 1, node_index * 2 + 1, True, scores, height))

# Game tree leaf scores
scores = [3, 5, 2, 9, 12, 5, 23, 23]
height = int(math.log2(len(scores)))

optimal_val = minimax(0, 0, True, scores, height)
print("=== Minimax Algorithm for Two-Player Game ===")
print("Terminal Node Scores:", scores)
print("Optimal Value at Root (MAX):", optimal_val)
'''

def get_hill_climbing_c():
    return '''def objective(x):
    # F(x) = -x^2 + 4x
    return -x**2 + 4*x

def hill_climbing(start_x, step_size=0.1, max_iter=100):
    current_x = start_x
    current_val = objective(current_x)

    for i in range(max_iter):
        next_left = current_x - step_size
        next_right = current_x + step_size
        val_left = objective(next_left)
        val_right = objective(next_right)

        if val_right > current_val and val_right >= val_left:
            current_x, current_val = next_right, val_right
        elif val_left > current_val:
            current_x, current_val = next_left, val_left
        else:
            break # Local maximum reached
    return current_x, current_val

opt_x, opt_val = hill_climbing(start_x=0.0)
print("=== Hill Climbing Algorithm ===")
print("Objective Function: F(x) = -x^2 + 4x")
print(f"Maximum found at x = {opt_x:.4f} with value F(x) = {opt_val:.4f}")
'''

def get_forward_chaining_c():
    return '''# Forward Chaining Inference Engine
facts = {'A', 'B'}
rules = [
    ({'A', 'B'}, 'C'),
    ({'C', 'D'}, 'E'),
    ({'C'}, 'F'),
    ({'F'}, 'Goal_Reached')
]

def forward_chaining(facts, rules, goal):
    inferred = set(facts)
    new_inferred = True

    while new_inferred:
        new_inferred = False
        for premises, conclusion in rules:
            if premises.issubset(inferred) and conclusion not in inferred:
                inferred.add(conclusion)
                print(f"[Rule Fired] {premises} -> {conclusion}")
                new_inferred = True
                if conclusion == goal:
                    return True
    return False

print("=== Forward Chaining Inference ===")
print("Initial Facts:", facts)
success = forward_chaining(facts, rules, 'Goal_Reached')
print("Goal Achieved:", success)
'''
