import numpy as np
from sklearn.svm import SVC

X = np.array([[1, 2], [2, 3], [5, 5]])
y = np.array([0, 0, 1])

# Non-Linear SVM using RBF Kernel
model = SVC(kernel='rbf', gamma='scale')
model.fit(X, y)

test_input = np.array([[4, 4]])
prediction = model.predict(test_input)

print("Input Data (X):", X.tolist())
print("Class Labels (y):", y.tolist())
print("Test Input:", test_input.tolist())
print("Predicted Class:", prediction[0])
