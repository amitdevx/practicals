from sklearn.datasets import load_iris
from sklearn.naive_bayes import GaussianNB
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

iris = load_iris()
X_tr, X_te, y_tr, y_te = train_test_split(iris.data, iris.target, test_size=0.3, random_state=42)
gnb = GaussianNB()
gnb.fit(X_tr, y_tr)
print("=== Gaussian Naive Bayes ===")
print("Accuracy:", accuracy_score(y_te, gnb.predict(X_te)))
