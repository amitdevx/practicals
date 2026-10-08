import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, confusion_matrix

df = pd.DataFrame({
    'Attendance': [80, 90, 75, 85, 95, 60, 55, 98],
    'Marks': [60, 75, 55, 80, 90, 40, 35, 95],
    'Category': ['Pass', 'Pass', 'Pass', 'Pass', 'Pass', 'Fail', 'Fail', 'Pass']
})

X = df[['Attendance', 'Marks']]
y = df['Category']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

model = RandomForestClassifier(random_state=42)
model.fit(X_train, y_train)
y_pred = model.predict(X_test)

print("Accuracy:", accuracy_score(y_test, y_pred))
print("Precision:", precision_score(y_test, y_pred, pos_label='Pass'))
print("Recall:", recall_score(y_test, y_pred, pos_label='Pass'))
print("F1-Score:", f1_score(y_test, y_pred, pos_label='Pass'))
print("Confusion Matrix:\n", confusion_matrix(y_test, y_pred))
