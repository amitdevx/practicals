import numpy as np
import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import r2_score

data = {
    'Years_Experience': [1.1, 1.3, 1.5, 2.0, 2.2, 2.9, 3.0, 3.2, 3.9, 4.0, 4.5, 5.1],
    'Salary': [39343, 46205, 37731, 43525, 39891, 56642, 60150, 54445, 63218, 55794, 61111, 67938]
}
df = pd.DataFrame(data)

X = df[['Years_Experience']]
y = df['Salary']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=42)

model = LinearRegression()
model.fit(X_train, y_train)

y_pred = model.predict(X_test)
print("=== Salary Prediction (Linear Regression) ===")
print("Slope (Coefficient):", model.coef_[0])
print("Intercept:", model.intercept_)
print("R2 Score:", r2_score(y_test, y_pred))
