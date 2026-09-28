import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression, LogisticRegression
from sklearn.metrics import accuracy_score, r2_score

np.random.seed(42)
X = np.random.rand(50, 2) * 10
y = (X[:, 0] * 2 + X[:, 1] * 3 + np.random.randn(50)).astype(int)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

model = LinearRegression()
model.fit(X_train, y_train)

preds = model.predict(X_test)
print("=== Model Execution (Slip 07) ===")
print("R2 Score:", r2_score(y_test, preds))
