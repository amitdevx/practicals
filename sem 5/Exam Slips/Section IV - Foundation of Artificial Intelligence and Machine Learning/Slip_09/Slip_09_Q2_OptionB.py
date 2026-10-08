import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score

data = {
    'Pregnancies': [6, 1, 8, 1, 0, 5, 3, 10, 2, 8, 4],
    'Glucose': [148, 85, 183, 89, 137, 116, 78, 115, 197, 125, 110],
    'BloodPressure': [72, 66, 64, 66, 40, 74, 50, 0, 70, 96, 92],
    'SkinThickness': [35, 29, 0, 23, 35, 0, 32, 0, 45, 0, 0],
    'Insulin': [0, 0, 0, 94, 168, 0, 88, 0, 543, 0, 0],
    'BMI': [33.6, 26.6, 23.3, 28.1, 43.1, 25.6, 31.0, 35.3, 30.5, 0.0, 37.6],
    'DiabetesPedigreeFunction': [0.627, 0.351, 0.672, 0.167, 2.288, 0.201, 0.248, 0.134, 0.158, 0.232, 0.191],
    'Age': [50, 31, 32, 21, 33, 30, 26, 29, 53, 54, 30],
    'Outcome': [1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0]
}

df = pd.DataFrame(data)

X = df.drop('Outcome', axis=1)
y = df['Outcome']

# Split 70:30
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

# Default Model
dt_default = DecisionTreeClassifier(random_state=42)
dt_default.fit(X_train, y_train)
y_pred_default = dt_default.predict(X_test)
print(f"Accuracy (Default): {accuracy_score(y_test, y_pred_default):.4f}")

# Optimized Models
for depth in [2, 3, 4]:
    dt_optimized = DecisionTreeClassifier(criterion='entropy', max_depth=depth, random_state=42)
    dt_optimized.fit(X_train, y_train)
    y_pred_opt = dt_optimized.predict(X_test)
    print(f"Accuracy (Entropy, max_depth={depth}): {accuracy_score(y_test, y_pred_opt):.4f}")
