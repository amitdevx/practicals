# Slip 07 - Foundation of Artificial Intelligence and Machine Learning

## Q1: A* Search Algorithm for Shortest Path
**Problem Statement:** Write a program to implement the A* Search Algorithm to find the shortest path between a source node and a destination node. Source = V1, Destination = V6

**Algorithm:**
1. Initialize a priority queue (min-heap) and insert the start node `V1` with its heuristic cost.
2. Maintain a `visited` dictionary to keep track of the minimum cost to reach each node.
3. While the priority queue is not empty, pop the node with the lowest `f_score = g_score + heuristic`.
4. If the popped node is the destination `V6`, return the path and its total cost.
5. Otherwise, for each neighbor of the current node, calculate the path cost. If this cost is lower than any previously recorded cost for that neighbor, push it to the priority queue with the updated path and cost.

**Run Command:**
```bash
python3 Slip_07_Q1.py
```

**Sample Output:**
```
=== A* Search Algorithm ===
Optimal Path: V1 -> V2 -> V3 -> V5 -> V4 -> V6
Total Path Cost: 9
```

---

## Q2 (Option A): Map Coloring Problem using CSP
**Problem Statement:** Write a program to solve the Map Coloring Problem using the Constraint Satisfaction Problem (CSP) approach.

**Algorithm:**
1. Define a list of variables (regions/nodes), domains (available colors), and constraints (adjacent regions cannot have the same color).
2. Create a backtracking function that takes the current assignment of colors.
3. If all regions are assigned a color safely, return the successful assignment.
4. Otherwise, pick an unassigned region and try coloring it with each available color.
5. If the color is safe (doesn't conflict with colored neighbors), assign it and recursively call the backtracking function.
6. If the recursive call returns a solution, return it. If not, backtrack by removing the assigned color and trying the next color.

**Run Command:**
```bash
python3 Slip_07_Q2_OptionA.py
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

---

## Q2 (Option B): Tic-Tac-Toe Game with Minimax Algorithm
**Problem Statement:** Write a program to develop a Tic-Tac-Toe Game in which the computer uses the Minimax Algorithm to play optimally.

**Algorithm:**
1. Initialize a 3x3 game board.
2. Define a utility function `is_winner` to check for win conditions for either 'X' (Human) or 'O' (Computer).
3. Implement the `minimax` function that simulates all possible moves recursively to find the best outcome for the current player (Computer maximizes, Human minimizes).
4. Create a function `best_move` that iterates over empty cells and calls `minimax` to select the move with the maximum score.
5. Play the game by accepting human moves and computing the optimal computer responses until a win or draw is reached.

**Run Command:**
```bash
python3 Slip_07_Q2_OptionB.py
```

**Sample Output:**
```
=== Tic-Tac-Toe Minimax ===
|   |   |   |
|   |   |   |
|   |   |   |

Human plays X at 4
Computer plays O at 0
| O |   |   |
|   | X |   |
|   |   |   |

Human plays X at 8
Computer plays O at 2
| O |   | O |
|   | X |   |
|   |   | X |
```

---

## Q3: Viva
**Status:** PRESENT
