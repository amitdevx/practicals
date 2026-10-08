# Slip 11 - Foundation of Artificial Intelligence and Machine Learning

## Q1: Compare Minimax and Alpha-Beta Pruning
**Topic:** Game Theory
**Short Algorithm:**
1. Define a game tree with leaf values.
2. Implement Minimax: recursively evaluate max/min choices for all nodes. Keep track of the number of nodes evaluated.
3. Implement Alpha-Beta Pruning: recursively evaluate using `alpha` (best max choice so far) and `beta` (best min choice so far). Prune branches where `beta <= alpha`.
4. Output the root values and nodes evaluated.
**Run Command:** `python3 Slip_11_Q1.py`
**Sample Output:**
```
=== Comparing Minimax and Alpha-Beta Pruning ===
Game Tree Value (Minimax): 5
Nodes Evaluated by Minimax: 15
Game Tree Value (Alpha-Beta): 5
Nodes Evaluated by Alpha-Beta: 11

Conclusion: Alpha-Beta pruning successfully evaluated fewer nodes!
```

## Q2 Option A: Backward Chaining Inference Mechanism
**Topic:** Expert Systems / Inference
**Short Algorithm:**
1. Define rules as a dictionary mapping a conclusion to a list of premises.
2. Define facts as a set of known truths.
3. Write a recursive function for the goal:
   - If the goal is a fact, return True.
   - If the goal has no rules or is already visited (cycle prevention), return False.
   - Recursively evaluate all premises for the goal. If all are True, return True and add to facts.
4. Output the trace of subgoals and final proven result.
**Run Command:** `python3 Slip_11_Q2_OptionA.py`
**Sample Output:**
```
=== Backward Chaining Inference ===
Initial Known Facts: {'F', 'B', 'A'}
Rules:
  If A AND B Then C
  If C Then D
  If D AND F Then E

Starting Backward Chaining...
[Investigating Goal] E
[Investigating Goal] D
[Investigating Goal] C
[Investigating Goal] A
Goal 'A' is a known fact.
[Investigating Goal] B
Goal 'B' is a known fact.
Successfully proved 'C' using its premises.
Successfully proved 'D' using its premises.
[Investigating Goal] F
Goal 'F' is a known fact.
Successfully proved 'E' using its premises.

Final Result: Goal 'E' Proven: True
Updated Known Facts: {'C', 'F', 'B', 'A', 'D', 'E'}
```

## Q2 Option B: Random Forest Classifier
**Topic:** Ensemble Machine Learning
**Short Algorithm:**
1. Load `car_evaluation.csv` using pandas and rename columns.
2. Print frequency counts and missing values.
3. Separate features (X) and target (y = 'class').
4. Label encode all categorical variables.
5. Split data 67% training, 33% testing.
6. Initialize Random Forest Classifier and fit on training data.
7. Evaluate accuracy on testing data.
**Run Command:** `python3 Slip_11_Q2_OptionB.py`
**Sample Output:**
```
=== Frequency Counts ===
...
=== Missing Values ===
...
Accuracy of Random Forest Classifier: 1.0000
```
