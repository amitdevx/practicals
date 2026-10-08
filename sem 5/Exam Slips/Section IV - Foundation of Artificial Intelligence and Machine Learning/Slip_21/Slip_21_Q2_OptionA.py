from sklearn.naive_bayes import GaussianNB
import numpy as np

X = np.array([[1, 2], [1, 3], [4, 5], [5, 5]])
y = np.array([0, 0, 1, 1])

clf = GaussianNB()
clf.fit(X, y)
pred = clf.predict([[2, 2], [4, 4]])
print("\nGaussian Naive Bayes Classifier\n")
print("Predictions:", pred)
