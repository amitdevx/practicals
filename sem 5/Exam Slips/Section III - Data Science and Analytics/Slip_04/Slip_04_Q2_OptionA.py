import pandas as pd
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, confusion_matrix

# Create Online Gaming dataset
data = {
    'Daily_Play_Time': [1.5, 2.0, 5.5, 6.0, 1.0, 8.0, 1.2, 7.5, 2.5, 6.5],
    'Achievements': [5, 10, 50, 65, 3, 80, 8, 70, 12, 60],
    'InGame_Purchases': [10, 15, 150, 200, 5, 250, 0, 180, 20, 160],
    'Gaming_Level': [10, 15, 60, 75, 5, 90, 8, 85, 20, 80],
    'Gamer_Type': ['Casual', 'Casual', 'Professional', 'Professional', 'Casual', 'Professional', 'Casual', 'Professional', 'Casual', 'Professional']
}
df = pd.DataFrame(data)

# Preprocess
X = df[['Daily_Play_Time', 'Achievements', 'InGame_Purchases', 'Gaming_Level']]
y = df['Gamer_Type']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

# Apply Logistic Regression
model = LogisticRegression()
model.fit(X_train, y_train)

# Predictions
y_pred = model.predict(X_test)

# Evaluate the model
print("Accuracy:", accuracy_score(y_test, y_pred))
print("Precision:", precision_score(y_test, y_pred, pos_label='Professional'))
print("Recall:", recall_score(y_test, y_pred, pos_label='Professional'))
print("F1-Score:", f1_score(y_test, y_pred, pos_label='Professional'))
print("Confusion Matrix:\n", confusion_matrix(y_test, y_pred))
