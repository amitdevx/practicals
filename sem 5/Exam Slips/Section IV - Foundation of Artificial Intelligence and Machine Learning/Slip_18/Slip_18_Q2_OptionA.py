import numpy as np
from sklearn.neural_network import MLPRegressor
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error

X = np.array([[1], [2], [3], [4], [5]])
y = np.array([2, 4, 6, 8, 10]) # y = 2x

model = MLPRegressor(hidden_layer_sizes=(10,), max_iter=1000, random_state=42)
model.fit(X, y)

test_X = np.array([[6], [7]])
preds = model.predict(test_X)
print("\nANN for Linear Regression\n")
print("Test Input:", test_X.flatten().tolist())
print("Predicted Output:", preds.tolist())
