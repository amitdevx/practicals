import heapq

def get_blank_pos(state):
    return state.index(0)

def moves(state):
    idx = get_blank_pos(state)
    r, c = divmod(idx, 3)
    directions = []
    if r > 0: directions.append(-3) # Up
    if r < 2: directions.append(3)  # Down
    if c > 0: directions.append(-1) # Left
    if c < 2: directions.append(1)  # Right
    
    res = []
    for d in directions:
        new_state = list(state)
        new_state[idx], new_state[idx+d] = new_state[idx+d], new_state[idx]
        res.append(tuple(new_state))
    return res

def manhattan(state, goal):
    dist = 0
    for val in range(1, 9):
        idx_s = state.index(val)
        idx_g = goal.index(val)
        rs, cs = divmod(idx_s, 3)
        rg, cg = divmod(idx_g, 3)
        dist += abs(rs - rg) + abs(cs - cg)
    return dist

def solve_8_puzzle(start, goal):
    pq = [(manhattan(start, goal), 0, start, [])]
    visited = set()
    
    while pq:
        _, g, current, path = heapq.heappop(pq)
        
        if current == goal:
            return path + [current]
            
        if current in visited:
            continue
        visited.add(current)
        
        for neighbor in moves(current):
            if neighbor not in visited:
                heapq.heappush(pq, (g + 1 + manhattan(neighbor, goal), g + 1, neighbor, path + [current]))
    return None

start_state = (1, 2, 3, 4, 0, 5, 6, 7, 8)
goal_state = (1, 2, 3, 4, 5, 6, 7, 8, 0)
path = solve_8_puzzle(start_state, goal_state)
print("\n8-Puzzle A*\n")
print("Moves to solve:", len(path) - 1 if path else "Unsolvable")
