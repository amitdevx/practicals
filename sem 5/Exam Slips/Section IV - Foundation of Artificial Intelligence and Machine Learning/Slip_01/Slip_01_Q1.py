from collections import deque

def get_successors(state):
    monkey_pos, on_box, box_pos, has_banana = state
    successors = []
    
    # 1. Grasp banana
    if on_box and box_pos == 'middle' and not has_banana:
        successors.append(('grasp', (monkey_pos, on_box, box_pos, True)))
        
    # 2. Climb on box
    if not on_box and monkey_pos == box_pos:
        successors.append(('climb_on', (monkey_pos, True, box_pos, has_banana)))
        
    # 3. Climb off box
    if on_box:
        successors.append(('climb_off', (monkey_pos, False, box_pos, has_banana)))
        
    # 4. Push box
    if not on_box and monkey_pos == box_pos:
        for pos in ['door', 'window', 'middle']:
            if pos != box_pos:
                successors.append((f'push_to_{pos}', (pos, False, pos, has_banana)))
                
    # 5. Move
    if not on_box:
        for pos in ['door', 'window', 'middle']:
            if pos != monkey_pos:
                successors.append((f'move_to_{pos}', (pos, False, box_pos, has_banana)))
                
    return successors

def bfs_monkey_banana(start_state):
    queue = deque([(start_state, [])])
    visited = {start_state}
    
    while queue:
        current_state, path = queue.popleft()
        
        # Goal test
        if current_state[3]: # has_banana is True
            return path
            
        for action, next_state in get_successors(current_state):
            if next_state not in visited:
                visited.add(next_state)
                queue.append((next_state, path + [action]))
                
    return None

if __name__ == "__main__":
    # State: (monkey_pos, on_box, box_pos, has_banana)
    start_state = ('door', False, 'window', False)
    
    print("Initial State: Monkey at door, Box at window, Banana at middle")
    print("Finding solution using BFS...")
    
    solution = bfs_monkey_banana(start_state)
    
    if solution:
        print("\nSolution steps found:")
        for i, step in enumerate(solution, 1):
            print(f"{i}. {step}")
    else:
        print("\nNo solution found.")
