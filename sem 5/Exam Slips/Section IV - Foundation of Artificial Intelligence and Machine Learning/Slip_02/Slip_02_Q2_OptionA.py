# Slip_02_Q2_OptionA.py
def is_safe(node, color, graph, color_assignment):
    for neighbor in graph[node]:
        if neighbor in color_assignment and color_assignment[neighbor] == color:
            return False
    return True

def graph_coloring(graph, colors, node, color_assignment):
    # node here is an index to keys list
    nodes = list(graph.keys())
    if node == len(nodes):
        return True
    
    current_node = nodes[node]
    for color in colors:
        if is_safe(current_node, color, graph, color_assignment):
            color_assignment[current_node] = color
            if graph_coloring(graph, colors, node + 1, color_assignment):
                return True
            del color_assignment[current_node]

    return False

if __name__ == "__main__":
    graph = {
        'WA': ['NT', 'SA'],
        'NT': ['WA', 'SA', 'Q'],
        'SA': ['WA', 'NT', 'Q', 'NSW', 'V'],
        'Q': ['NT', 'SA', 'NSW'],
        'NSW': ['Q', 'SA', 'V'],
        'V': ['SA', 'NSW'],
        'T': []
    }
    colors = ['Red', 'Green', 'Blue']
    color_assignment = {}
    
    print("\nConstraint Satisfaction Problem (Graph Coloring)\n")
    if graph_coloring(graph, colors, 0, color_assignment):
        print("Solution found:")
        for node, color in color_assignment.items():
            print(f"{node}: {color}")
    else:
        print("No solution exists.")
