import pandas as pd
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, confusion_matrix

data = {
    'Age': [25, 34, 45, 52, 23, 40, 60, 48, 33, 55],
    'Income': [40, 60, 80, 100, 35, 75, 120, 90, 50, 110],
    'Segment': [0, 0, 1, 1, 0, 1, 2, 1, 0, 2]
}
df = pd.DataFrame(data)
X = df[['Age', 'Income']]
y = df['Segment']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

knn = KNeighborsClassifier(n_neighbors=3)
knn.fit(X_train, y_train)
y_pred = knn.predict(X_test)

print("Accuracy:", accuracy_score(y_test, y_pred))
print("Confusion Matrix:\n", confusion_matrix(y_test, y_pred))
