from sklearn.datasets import load_iris
from sklearn.ensemble import VotingClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

iris = load_iris()
X, y = iris.data, iris.target
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

clf1 = LogisticRegression(max_iter=200)
clf2 = DecisionTreeClassifier(random_state=42)

ensemble = VotingClassifier(
    estimators=[('lr', clf1), ('dt', clf2)],
    voting='hard'
)
ensemble.fit(X_train, y_train)

y_pred = ensemble.predict(X_test)
print("\nVoting Classifier Ensemble\n")
print("Ensemble Accuracy:", accuracy_score(y_test, y_pred))
