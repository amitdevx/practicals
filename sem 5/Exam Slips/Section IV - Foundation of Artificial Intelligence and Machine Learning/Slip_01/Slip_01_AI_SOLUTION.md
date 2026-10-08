# Slip 01 - Foundation of Artificial Intelligence and Machine Learning

## Q1: Breadth First Search (BFS) for the Monkey Banana Problem

**Algorithm:**
1. Define the state as a tuple: `(monkey_pos, on_box, box_pos, has_banana)`.
2. Define the start state and the goal state condition (`has_banana == True`).
3. Create a function to generate valid successor states from current state based on actions: `move`, `push`, `climb_on`, `climb_off`, `grasp`.
4. Initialize a queue with the start state and empty path, and a `visited` set.
5. While queue is not empty:
   a. Dequeue current state and path.
   b. If current state satisfies goal, return the path.
   c. For each successor of current state, if not visited, add to visited and enqueue.
6. Print the returned path.

**Command to Run:**
```bash
python3 Slip_01_Q1.py
```

**Sample Output:**
```
Initial State: Monkey at door, Box at window, Banana at middle
Finding solution using BFS...

Solution steps found:
1. move_to_window
2. push_to_middle
3. climb_on
4. grasp
```

---

## Q2 (Option A): A* Search Algorithm

**Algorithm:**
1. Create a priority queue to store `(f_score, cost, current_node, path)`.
2. Push the start node with its heuristic value as `f_score`.
3. Loop until queue is empty:
   - Pop the node with the lowest `f_score`.
   - If it is the goal node, return the path and cost.
   - If it's already visited with a lower cost, continue.
   - Otherwise, mark it as visited and iterate over its neighbors.
   - For each neighbor, calculate new cost and estimated total cost (cost + heuristic).
   - Push the neighbor into the priority queue.

**Command to Run:**
```bash
python3 Slip_01_Q2_OptionA.py
```

**Sample Output:**
```
=== A* Search Algorithm ===
Optimal Path: A -> B -> D -> G
Total Path Cost: 6
```

---

## Q2 (Option B): Map Coloring Problem using CSP

**Algorithm:**
1. Define constraints with an `is_safe` function that checks if adjacent nodes have the same color.
2. In a recursive `solve_csp` function, if all nodes are assigned a color, return the assignment.
3. Select an unassigned node.
4. Try each available color for the node. If `is_safe`, assign it.
5. Recursively call `solve_csp`. If a solution is found, return it.
6. If no color works, backtrack (remove assignment) and return `None`.

**Command to Run:**
```bash
python3 Slip_01_Q2_OptionB.py
```

**Sample Output:**
```
=== Map Coloring CSP Solution ===
WA: Red
NT: Green
SA: Blue
Q: Red
NSW: Green
V: Red
T: Red
```
