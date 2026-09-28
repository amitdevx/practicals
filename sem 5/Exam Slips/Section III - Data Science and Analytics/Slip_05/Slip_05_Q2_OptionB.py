import pandas as pd
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

data = {
    'Attendance': [85, 70, 95, 60, 75, 90, 50, 65, 88, 78],
    'Marks': [82, 65, 90, 55, 72, 88, 45, 60, 85, 74],
    'Grade': ['A', 'B', 'A', 'C', 'B', 'A', 'C', 'C', 'A', 'B']
}
df = pd.DataFrame(data)

X = df[['Attendance', 'Marks']]
y = df['Grade']

knn = KNeighborsClassifier(n_neighbors=3)
knn.fit(X, y)

test_student = [[80, 75]]
pred = knn.predict(test_student)
print("=== KNN Student Grade Classifier ===")
print(f"Predicted Grade for Attendance=80, Marks=75: {pred[0]}")
