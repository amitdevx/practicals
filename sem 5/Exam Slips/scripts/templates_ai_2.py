# Additional AI & ML Templates for CS-321 Foundation of AI & ML

def get_alpha_beta_c():
    return '''import math

def alphabeta(depth, node_idx, is_max, scores, alpha, beta, height):
    if depth == height:
        return scores[node_idx]

    if is_max:
        best = -math.inf
        for i in range(2):
            val = alphabeta(depth + 1, node_idx * 2 + i, False, scores, alpha, beta, height)
            best = max(best, val)
            alpha = max(alpha, best)
            if beta <= alpha:
                print(f"[Pruning] Pruned at depth {depth}, node {node_idx*2+i}")
                break
        return best
    else:
        best = math.inf
        for i in range(2):
            val = alphabeta(depth + 1, node_idx * 2 + i, True, scores, alpha, beta, height)
            best = min(best, val)
            beta = min(beta, best)
            if beta <= alpha:
                print(f"[Pruning] Pruned at depth {depth}, node {node_idx*2+i}")
                break
        return best

scores = [3, 5, 6, 9, 1, 2, 0, -1]
height = int(math.log2(len(scores)))

print("=== Alpha-Beta Pruning Simulation ===")
optimal = alphabeta(0, 0, True, scores, -math.inf, math.inf, height)
print("Optimal Game Value at Root:", optimal)
'''

def get_dls_c():
    return '''def dls(graph, node, target, limit, depth=0, path=None):
    if path is None: path = []
    path.append(node)

    if node == target:
        return True, path
    if depth >= limit:
        return False, None

    for neighbor in graph.get(node, []):
        if neighbor not in path:
            found, res_path = dls(graph, neighbor, target, limit, depth + 1, list(path))
            if found:
                return True, res_path
    return False, None

graph = {
    '1': ['2', '3'],
    '2': ['4', '5'],
    '3': ['6', '7'],
    '4': ['8'],
    '5': [], '6': [], '7': [], '8': []
}

limit = 2
target = '8'
print(f"=== Depth Limited Search (DLS) (Limit: {limit}, Target: {target}) ===")
found, path = dls(graph, '1', target, limit)
if found:
    print("Target found along path:", " -> ".join(path))
else:
    print(f"Target '{target}' NOT found within depth limit {limit}.")
'''

def get_ids_c():
    return '''def dls_search(graph, node, target, limit, depth=0, path=None):
    if path is None: path = []
    path.append(node)
    if node == target: return True, path
    if depth >= limit: return False, None

    for neighbor in graph.get(node, []):
        if neighbor not in path:
            found, res_path = dls_search(graph, neighbor, target, limit, depth + 1, list(path))
            if found: return True, res_path
    return False, None

def iterative_deepening(graph, start, target, max_depth=10):
    for depth in range(max_depth):
        print(f"Searching with depth limit = {depth}...")
        found, path = dls_search(graph, start, target, depth)
        if found:
            return path
    return None

graph = {
    'A': ['B', 'C'],
    'B': ['D', 'E'],
    'C': ['F', 'G'],
    'D': [], 'E': [], 'F': [], 'G': []
}

target = 'G'
print("=== Iterative Deepening Search (IDS) ===")
path = iterative_deepening(graph, 'A', target, max_depth=5)
print("Goal reached with path:", " -> ".join(path))
'''

def get_tower_of_hanoi_c():
    return '''def tower_of_hanoi(n, source, destination, auxiliary):
    if n == 1:
        print(f"Move disk 1 from rod {source} -> rod {destination}")
        return
    tower_of_hanoi(n - 1, source, auxiliary, destination)
    print(f"Move disk {n} from rod {source} -> rod {destination}")
    tower_of_hanoi(n - 1, auxiliary, destination, source)

n = 3
print(f"=== Tower of Hanoi Problem ({n} Disks) ===")
tower_of_hanoi(n, 'A', 'C', 'B')
'''

def get_n_queens_c():
    return '''def is_safe(board, row, col, n):
    # Check column
    for i in range(row):
        if board[i] == col or abs(board[i] - col) == abs(i - row):
            return False
    return True

def solve_n_queens(n, row=0, board=None, solutions=None):
    if board is None: board = [-1] * n
    if solutions is None: solutions = []

    if row == n:
        solutions.append(list(board))
        return

    for col in range(n):
        if is_safe(board, row, col, n):
            board[row] = col
            solve_n_queens(n, row + 1, board, solutions)
            board[row] = -1
    return solutions

n = 4
sols = solve_n_queens(n)
print(f"=== N-Queens Backtracking Problem (N = {n}) ===")
print(f"Total Solutions Found: {len(sols)}")
for i, sol in enumerate(sols, 1):
    print(f"\\nSolution {i}: (Row positions of queens per column: {sol})")
    for r in range(n):
        line = ["Q" if sol[r] == c else "." for c in range(n)]
        print(" ".join(line))
'''

def get_means_end_c():
    return '''# Means-End Analysis (Goal-driven state operator reduction)
class MeansEndSolver:
    def __init__(self, current_state, goal_state, operators):
        self.current = set(current_state)
        self.goal = set(goal_state)
        self.operators = operators

    def solve(self):
        print("Initial State:", self.current)
        print("Goal State:   ", self.goal)
        steps = []

        while self.current != self.goal:
            diff = self.goal - self.current
            if not diff:
                break
            target_fact = next(iter(diff))
            # Find operator that yields target_fact
            chosen_op = None
            for op_name, (preconds, add_effects) in self.operators.items():
                if target_fact in add_effects:
                    chosen_op = (op_name, preconds, add_effects)
                    break

            if chosen_op:
                op_name, preconds, add_effects = chosen_op
                # Satisfy preconditions
                for p in preconds:
                    self.current.add(p)
                for a in add_effects:
                    self.current.add(a)
                steps.append(op_name)
                print(f"[Applied Operator] {op_name} -> Current State: {self.current}")
            else:
                print("[-] No operator available to resolve difference!")
                break
        return steps

operators = {
    'Drive_Car': ({'Has_Car', 'Has_Fuel'}, {'At_Destination'}),
    'Fill_Fuel': ({'Has_Money'}, {'Has_Fuel'}),
    'Earn_Money': (set(), {'Has_Money'}),
    'Buy_Car': ({'Has_Money'}, {'Has_Car'})
}

solver = MeansEndSolver(current_state={'Has_Money'}, goal_state={'At_Destination'}, operators=operators)
steps = solver.solve()
print("Solution Plan:", " -> ".join(steps))
'''

def get_propositional_logic_c():
    return '''# Propositional Logic Truth Table Evaluator
def evaluate_expression():
    print("=== Propositional Logic Truth Table ===")
    print("P\\tQ\\tP AND Q\\tP OR Q\\tP -> Q\\tP <-> Q")
    print("---------------------------------------------------------")

    for P in [True, False]:
        for Q in [True, False]:
            p_and_q = P and Q
            p_or_q = P or Q
            p_implies_q = (not P) or Q
            p_iff_q = P == Q
            print(f"{P}\\t{Q}\\t{p_and_q}\\t{p_or_q}\\t{p_implies_q}\\t{p_iff_q}")

evaluate_expression()
'''

def get_backward_chaining_c():
    return '''# Backward Chaining Inference Engine
rules = {
    'C': ['A', 'B'],
    'D': ['C'],
    'E': ['D', 'F']
}
facts = {'A', 'B', 'F'}

def backward_chain(goal, visited=None):
    if visited is None: visited = set()
    print(f"[Investigating Goal] {goal}")
    if goal in facts:
        return True

    if goal not in rules or goal in visited:
        return False
    visited.add(goal)

    premises = rules[goal]
    for p in premises:
        if not backward_chain(p, visited):
            return False
    return True

target_goal = 'E'
print("=== Backward Chaining Inference ===")
print("Known Facts:", facts)
result = backward_chain(target_goal)
print(f"Goal '{target_goal}' Proven:", result)
'''

def get_expert_system_c():
    return '''# Rule-Based Expert System for Medical Diagnosis
def expert_system_diagnose(symptoms):
    rules = [
        ({'fever', 'cough', 'fatigue'}, "Common Viral Flu"),
        ({'fever', 'shivering', 'headache'}, "Malaria"),
        ({'cough', 'shortness_of_breath', 'chest_pain'}, "Respiratory Infection"),
        ({'sneezing', 'runny_nose', 'sore_throat'}, "Allergic Rhinitis")
    ]

    diagnoses = []
    for symptom_set, disease in rules:
        if symptom_set.issubset(symptoms):
            diagnoses.append(disease)

    return diagnoses if diagnoses else ["General Fatigue / Consultation Required"]

patient_symptoms = {'fever', 'cough', 'fatigue'}
print("=== Rule-Based Expert System ===")
print("Patient Symptoms:", patient_symptoms)
print("Diagnosis:", expert_system_diagnose(patient_symptoms))
'''

def get_svm_pipeline_c():
    return '''import pandas as pd
from sklearn.datasets import load_iris
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.svm import LinearSVC
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report

iris = load_iris()
X, y = iris.data, iris.target

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=42)

# Pipeline containing StandardScaler and LinearSVC (C=1, hinge loss)
svm_pipe = Pipeline([
    ('scaler', StandardScaler()),
    ('svc', LinearSVC(C=1.0, loss='hinge', max_iter=2000, random_state=42))
])

svm_pipe.fit(X_train, y_train)
y_pred = svm_pipe.predict(X_test)

print("=== SVM Pipeline on Iris Dataset ===")
print(classification_report(y_test, y_pred, target_names=iris.target_names))
'''

def get_ann_c():
    return '''import numpy as np
from sklearn.neural_network import MLPClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

X = np.array([
    [0, 0], [0, 1], [1, 0], [1, 1],
    [2, 2], [2, 3], [3, 2], [3, 3]
])
y = np.array([0, 0, 0, 0, 1, 1, 1, 1])

ann = MLPClassifier(hidden_layer_sizes=(4, 2), max_iter=1000, activation='relu', random_state=42)
ann.fit(X, y)

test_data = np.array([[0.5, 0.5], [2.5, 2.5]])
preds = ann.predict(test_data)
print("=== Artificial Neural Network (MLP) ===")
print("Test Input:", test_data.tolist())
print("Predicted Output:", preds.tolist())
'''

def get_voting_classifier_c():
    return '''from sklearn.datasets import load_iris
from sklearn.ensemble import VotingClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

iris = load_iris()
X, y = iris.data, iris.target
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

clf1 = LogisticRegression(max_iter=200)
clf2 = DecisionTreeClassifier(random_state=42)
clf3 = KNeighborsClassifier(n_neighbors=3)

ensemble = VotingClassifier(
    estimators=[('lr', clf1), ('dt', clf2), ('knn', clf3)],
    voting='hard'
)
ensemble.fit(X_train, y_train)

y_pred = ensemble.predict(X_test)
print("=== Voting Classifier Ensemble ===")
print("Ensemble Accuracy:", accuracy_score(y_test, y_pred))
'''
