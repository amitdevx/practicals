import numpy as np
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score

X = np.array([ [1, 2], [2, 3], [3, 1], [4, 2], [5, 5], [6, 6], [7, 4], [8, 5] ])
Y = np.array([0, 0, 0, 0, 1, 1, 1, 1])

# Linear SVM
linear_svm = SVC(kernel='linear')
linear_svm.fit(X, Y)
linear_pred = linear_svm.predict(X)
linear_acc = accuracy_score(Y, linear_pred)

# RBF SVM
rbf_svm = SVC(kernel='rbf')
rbf_svm.fit(X, Y)
rbf_pred = rbf_svm.predict(X)
rbf_acc = accuracy_score(Y, rbf_pred)

print("\nSVM Comparison\n")
print(f"Linear SVM Accuracy: {linear_acc * 100:.2f}%")
print(f"RBF SVM Accuracy: {rbf_acc * 100:.2f}%")
print("Linear SVM Predictions:", linear_pred)
print("RBF SVM Predictions:   ", rbf_pred)
print("Actual Labels:         ", Y)
