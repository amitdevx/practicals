from collections import deque

def bfs_monkey_banana():
    # State: (monkey_pos, box_pos, on_box, has_banana)
    initial_state = ('door', 'window', False, False)
    
    queue = deque([(initial_state, [])])
    visited = set([initial_state])
    
    while queue:
        (m_pos, b_pos, on_box, has_banana), path = queue.popleft()
        
        if has_banana:
            return path
            
        next_states = []
        
        # 1. Grasp
        if m_pos == 'center' and on_box and not has_banana:
            next_states.append(( (m_pos, b_pos, on_box, True), "Grasp banana" ))
        
        # 2. Climb up
        if m_pos == b_pos and not on_box:
            next_states.append(( (m_pos, b_pos, True, has_banana), "Climb box" ))
            
        # 3. Climb down
        if on_box:
            next_states.append(( (m_pos, b_pos, False, has_banana), "Climb down" ))
            
        # 4. Push box
        if m_pos == b_pos and not on_box:
            for new_pos in ['door', 'window', 'center']:
                if new_pos != m_pos:
                    next_states.append(( (new_pos, new_pos, False, has_banana), f"Push box to {new_pos}" ))
                    
        # 5. Move
        if not on_box:
            for new_pos in ['door', 'window', 'center']:
                if new_pos != m_pos:
                    next_states.append(( (new_pos, b_pos, False, has_banana), f"Move to {new_pos}" ))
                    
        for state, action in next_states:
            if state not in visited:
                visited.add(state)
                queue.append((state, path + [action]))
                
    return None

print("\nMonkey Banana Problem (BFS)\n")
solution = bfs_monkey_banana()
if solution:
    print("Solution found:")
    for i, action in enumerate(solution, 1):
        print(f"Step {i}: {action}")
else:
    print("No solution found.")
