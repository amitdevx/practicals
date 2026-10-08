import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, confusion_matrix

df = pd.DataFrame({
    'Study_Hours': [2, 3, 5, 8, 9, 1, 4, 7],
    'Attendance': [60, 70, 80, 95, 98, 50, 75, 90],
    'Category': ['Fail', 'Pass', 'Pass', 'Pass', 'Pass', 'Fail', 'Pass', 'Pass']
})

X = df[['Study_Hours', 'Attendance']]
y = df['Category']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

knn = KNeighborsClassifier(n_neighbors=3)
knn.fit(X_train, y_train)
y_pred = knn.predict(X_test)

print("Accuracy:", accuracy_score(y_test, y_pred))
print("Precision:", precision_score(y_test, y_pred, pos_label='Pass'))
print("Recall:", recall_score(y_test, y_pred, pos_label='Pass'))
print("F1-Score:", f1_score(y_test, y_pred, pos_label='Pass'))
print("Confusion Matrix:\n", confusion_matrix(y_test, y_pred))
