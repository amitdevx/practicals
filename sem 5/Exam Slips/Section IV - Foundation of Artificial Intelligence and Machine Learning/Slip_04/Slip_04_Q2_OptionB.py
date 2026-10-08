from sklearn.datasets import make_blobs
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import accuracy_score
import numpy as np

# 1. Dataset Generation
X, y = make_blobs(n_samples=200, n_features=2, centers=3, cluster_std=1.5, random_state=42)

# 2. Gaussian Naive Bayes Classifier
model = GaussianNB()
model.fit(X, y)

# 3. Testing (Prediction)
X_test = np.array([[-2, 5], [0, 0], [6, -0.3]])
y_pred_test = model.predict(X_test)

print("\nGaussian NB Classifier\n")
print("Input Values:\n", X_test)
print("Predicted Output:", y_pred_test)

# 4. Accuracy Score (Evaluating on training data as no separate test split was requested)
y_pred_train = model.predict(X)
acc = accuracy_score(y, y_pred_train)
print(f"Accuracy Score: {acc:.4f}")
