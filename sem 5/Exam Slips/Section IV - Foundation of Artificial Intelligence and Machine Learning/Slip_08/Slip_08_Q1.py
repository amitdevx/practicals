import heapq

# 4-Puzzle (2x2 grid)
# Goal state:
# 1 2
# 3 0
# represented as (1, 2, 3, 0)

GOAL_STATE = (1, 2, 3, 0)

def manhattan_distance(state):
    dist = 0
    for i, val in enumerate(state):
        if val == 0:
            continue
        goal_idx = GOAL_STATE.index(val)
        curr_row, curr_col = i // 2, i % 2
        goal_row, goal_col = goal_idx // 2, goal_idx % 2
        dist += abs(curr_row - goal_row) + abs(curr_col - goal_col)
    return dist

def get_neighbors(state):
    neighbors = []
    idx = state.index(0)
    row, col = idx // 2, idx % 2
    
    moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    for dr, dc in moves:
        new_r, new_c = row + dr, col + dc
        if 0 <= new_r < 2 and 0 <= new_c < 2:
            new_idx = new_r * 2 + new_c
            new_state = list(state)
            new_state[idx], new_state[new_idx] = new_state[new_idx], new_state[idx]
            neighbors.append(tuple(new_state))
    return neighbors

def a_star_4_puzzle(start_state):
    pq = []
    heapq.heappush(pq, (manhattan_distance(start_state), 0, start_state, []))
    visited = set()

    while pq:
        f, g, current, path = heapq.heappop(pq)

        if current == GOAL_STATE:
            return path + [current]

        if current in visited:
            continue
        visited.add(current)

        for neighbor in get_neighbors(current):
            if neighbor not in visited:
                h = manhattan_distance(neighbor)
                heapq.heappush(pq, (g + 1 + h, g + 1, neighbor, path + [current]))
                
    return None

if __name__ == '__main__':
    start = (3, 1, 2, 0)
    print(f"Start State: {start[:2]}\n             {start[2:]}")
    print(f"Goal State:  {GOAL_STATE[:2]}\n             {GOAL_STATE[2:]}\n")
    
    path = a_star_4_puzzle(start)
    
    if path:
        print(f"Found solution in {len(path)-1} steps:")
        for step, state in enumerate(path):
            print(f"Step {step}: {state[:2]}")
            print(f"        {state[2:]}")
    else:
        print("No solution found.")
