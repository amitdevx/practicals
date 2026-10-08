from sklearn.svm import SVC
import numpy as np

# Input Data
X = np.array([
    [5.1, 3.5, 1.4, 0.2], [4.9, 3.0, 1.4, 0.2], [4.7, 3.2, 1.3, 0.2], 
    [4.6, 3.1, 1.5, 0.2], [5.0, 3.6, 1.4, 0.2], [7.0, 3.2, 4.7, 1.4], 
    [6.4, 3.2, 4.5, 1.5], [6.9, 3.1, 4.9, 1.5], [6.3, 3.3, 6.0, 2.5], 
    [5.8, 2.7, 5.1, 1.9]
])
y = np.array([0, 0, 0, 0, 0, 1, 1, 1, 2, 2])
X_test = np.array([[5.2, 3.4, 1.5, 0.2], [6.5, 3.0, 4.6, 1.5], [6.2, 3.0, 5.2, 2.0]])

# Train SVM Classifier
clf = SVC()
clf.fit(X, y)

# Predict
predictions = clf.predict(X_test)

print("Test Inputs:", X_test.tolist())
print("SVM Predictions:", predictions.tolist())
