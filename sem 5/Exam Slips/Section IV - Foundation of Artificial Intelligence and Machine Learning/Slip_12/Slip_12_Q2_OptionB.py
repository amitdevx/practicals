import numpy as np
from sklearn.neural_network import MLPRegressor
from sklearn.metrics import mean_squared_error

# Generate some linear data: y = 2x + 1
X = np.array([[1], [2], [3], [4], [5], [6], [7], [8]])
y = np.array([3, 5, 7, 9, 11, 13, 15, 17])

# ANN for Linear Regression
ann_regressor = MLPRegressor(hidden_layer_sizes=(10,), max_iter=2000, solver='lbfgs', random_state=42)
ann_regressor.fit(X, y)

y_pred = ann_regressor.predict(X)
mse = mean_squared_error(y, y_pred)

print("\nANN for Linear Regression\n")
print("Input X:\n", X.flatten())
print("Actual y:\n", y)
print("Predicted y:\n", np.round(y_pred, 2))
print(f"Mean Squared Error: {mse:.4f}")
