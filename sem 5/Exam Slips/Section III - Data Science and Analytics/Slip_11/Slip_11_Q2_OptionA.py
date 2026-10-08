import pandas as pd
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, f1_score, confusion_matrix

data = {
    'RAM': [4, 6, 8, 12, 4, 8, 12, 16, 6, 8],
    'Storage': [64, 128, 256, 512, 64, 128, 256, 512, 128, 256],
    'Battery': [3000, 4000, 4500, 5000, 3500, 4200, 4800, 5500, 4000, 4500],
    'Price_Category': ['Low', 'Medium', 'High', 'Premium', 'Low', 'Medium', 'High', 'Premium', 'Medium', 'High']
}
df = pd.DataFrame(data)
X = df[['RAM', 'Storage', 'Battery']]
y = df['Price_Category']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)
model = LogisticRegression(max_iter=500)
model.fit(X_train, y_train)
y_pred = model.predict(X_test)

print("Accuracy:", accuracy_score(y_test, y_pred))
print("F1 Score (macro):", f1_score(y_test, y_pred, average='macro'))
print("Confusion Matrix:\n", confusion_matrix(y_test, y_pred))
