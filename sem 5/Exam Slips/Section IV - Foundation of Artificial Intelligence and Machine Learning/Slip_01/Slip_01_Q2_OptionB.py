def is_safe(node, color, assignment, graph):
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
