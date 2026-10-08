import pandas as pd
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, confusion_matrix

data = {
    'StudyHours': [2, 3, 4, 5, 6, 7, 8, 9, 1, 10],
    'Attendance': [80, 85, 90, 88, 92, 95, 96, 98, 75, 99],
    'Category': ['Low', 'Low', 'Medium', 'Medium', 'Medium', 'High', 'High', 'High', 'Low', 'High']
}
df = pd.DataFrame(data)

X = df[['StudyHours', 'Attendance']]
y = df['Category']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

knn = KNeighborsClassifier(n_neighbors=3)
knn.fit(X_train, y_train)
y_pred = knn.predict(X_test)

print("Accuracy:", accuracy_score(y_test, y_pred))
print("Confusion Matrix:\n", confusion_matrix(y_test, y_pred))
