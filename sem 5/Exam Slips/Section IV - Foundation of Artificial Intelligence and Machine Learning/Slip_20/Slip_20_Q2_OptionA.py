import numpy as np
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
