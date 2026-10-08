# Slip 08 - Foundation of Artificial Intelligence and Machine Learning

## Q1: 4-Puzzle Problem using A* Search Algorithm
**Topic:** A* Search Algorithm
**Algorithm:**
1. Define the start state and the target goal state (e.g., 2x2 grid `[1, 2, 3, 0]`).
2. Use a priority queue to store `(f, g, state, path)` where `g` is cost so far, `h` is Manhattan distance heuristic, and `f = g + h`.
3. Add the initial state to the queue.
4. While the queue is not empty, extract the state with the minimum `f` score.
5. If it is the goal state, return the path.
6. For each valid move (swapping `0` with a neighboring tile), if the resulting state is not visited, calculate its `f` score and add to the queue.
7. Mark the current state as visited to avoid cycles.

**Run Command:**
```bash
python3 Slip_08_Q1.py
```
**Sample Output:**
```
Start State: (3, 1)
             (2, 0)
Goal State:  (1, 2)
             (3, 0)

Found solution in 4 steps:
Step 0: (3, 1)
        (2, 0)
Step 1: (3, 1)
        (0, 2)
Step 2: (0, 1)
        (3, 2)
Step 3: (1, 0)
        (3, 2)
Step 4: (1, 2)
        (3, 0)
```

## Q2 Option A: Compare Minimax and Alpha-Beta Pruning
**Topic:** Game Playing Algorithms (Minimax, Alpha-Beta)
**Algorithm:**
1. Define a tree structure using a Node class, with static values at the leaf nodes.
2. Implement the Minimax algorithm which recursively computes the optimal move by maximizing for one player and minimizing for the other. Count the number of node evaluations.
3. Implement the Alpha-Beta pruning algorithm which works similarly but passes `alpha` and `beta` values to prune branches that cannot influence the final decision. Count the node evaluations.
4. Run both algorithms on the same tree and compare the number of nodes evaluated. Alpha-Beta should visit fewer nodes while yielding the same optimal result.

**Run Command:**
```bash
python3 Slip_08_Q2_OptionA.py
```
**Sample Output:**
```
=== Comparison: Minimax vs Alpha-Beta Pruning ===
Minimax Optimal Value: 3
Nodes Evaluated (Minimax): 7

Alpha-Beta Optimal Value: 3
Nodes Evaluated (Alpha-Beta): 6
```

## Q2 Option B: Rule-Based Expert System
**Topic:** Expert Systems
**Algorithm:**
1. Define a knowledge base (set of rules) where specific conditions (e.g., symptom sets) map to conclusions (diagnoses).
2. Accept a set of input facts from the user (patient symptoms).
3. Use a forward chaining approach by iterating through the rules and checking if the conditions are a subset of the provided facts.
4. If a match is found, append the corresponding conclusion to the results.
5. Display the final set of inferences to the user, or provide a default fallback if no rules trigger.

**Run Command:**
```bash
python3 Slip_08_Q2_OptionB.py
```
**Sample Output:**
```
=== Rule-Based Expert System ===
Patient Symptoms: {'fatigue', 'fever', 'cough'}
Diagnosis: ['Common Viral Flu']
```
