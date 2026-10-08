import numpy as np
from sklearn.neural_network import MLPClassifier
import warnings

# Input data and targets
X = np.array([
    [3, 1.5], [2, 1], [4, 1.5], [3, 4], 
    [3.5, 0.5], [2, 0.5], [5.5, 1], [1, 1]
])
y = np.array([0, 1, 0, 1, 0, 1, 1, 0])

learning_rates = [0.01, 0.1, 0.5]
epochs_list = [20, 100, 500]

best_score = -1
best_params = {}

print("Evaluating Basic ANN with different hyperparameters:\n")

for lr in learning_rates:
    for epochs in epochs_list:
        model = MLPClassifier(hidden_layer_sizes=(4,), learning_rate_init=lr, max_iter=epochs, random_state=42)
        
        with warnings.catch_warnings():
            warnings.simplefilter("ignore")
            model.fit(X, y)
        
        score = model.score(X, y)
        print(f"LR: {lr:<4}, Epochs: {epochs:<4} -> Accuracy: {score:.2f}")
        
        if score > best_score:
            best_score = score
            best_params = {'lr': lr, 'epochs': epochs}

print("\nIdeal Hyperparameters found:")
print(f"Learning Rate: {best_params['lr']}, Epochs: {best_params['epochs']}")
print(f"Best Accuracy: {best_score:.2f}")
