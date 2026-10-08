from sklearn.datasets import make_classification
from sklearn.naive_bayes import BernoulliNB
import numpy as np

# Create dataset X of 300 sample points
X, y = make_classification(n_samples=300, n_features=2, n_informative=2, 
                           n_redundant=0, n_classes=2, random_state=42)

# Train Bernoulli NB Classifier
clf = BernoulliNB()
clf.fit(X, y)

# Testing (Prediction)
X_test = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
y_pred = clf.predict(X_test)

print("Test Inputs:", X_test.tolist())
print("Predicted Output:", y_pred.tolist())
