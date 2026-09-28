import pandas as pd
from sklearn.datasets import load_iris
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.svm import LinearSVC
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report

iris = load_iris()
X, y = iris.data, iris.target

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=42)

# Pipeline containing StandardScaler and LinearSVC (C=1, hinge loss)
svm_pipe = Pipeline([
    ('scaler', StandardScaler()),
    ('svc', LinearSVC(C=1.0, loss='hinge', max_iter=2000, random_state=42))
])

svm_pipe.fit(X_train, y_train)
y_pred = svm_pipe.predict(X_test)

print("=== SVM Pipeline on Iris Dataset ===")
print(classification_report(y_test, y_pred, target_names=iris.target_names))
