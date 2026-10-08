import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, confusion_matrix

# Create a sample Heart Disease dataset
data = {
    'Age': [52, 53, 70, 61, 62, 58, 58, 55, 46, 54],
    'Sex': [1, 1, 1, 1, 0, 0, 1, 1, 1, 1],
    'Cholesterol': [212, 203, 322, 214, 294, 248, 318, 289, 249, 239],
    'MaxHR': [168, 155, 109, 140, 162, 122, 140, 145, 144, 160],
    'HeartDisease': [0, 1, 1, 0, 1, 0, 1, 0, 0, 1]
}
df = pd.DataFrame(data)
df.to_csv('heart_disease.csv', index=False)

# Preprocess the data
X = df.drop('HeartDisease', axis=1)
y = df['HeartDisease']

# Split data
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

# Apply Random Forest algorithm
rf = RandomForestClassifier(n_estimators=50, random_state=42)
rf.fit(X_train, y_train)

# Predictions
y_pred = rf.predict(X_test)

# Evaluate using accuracy and confusion matrix
print("Accuracy:", accuracy_score(y_test, y_pred))
print("Confusion Matrix:\n", confusion_matrix(y_test, y_pred))
