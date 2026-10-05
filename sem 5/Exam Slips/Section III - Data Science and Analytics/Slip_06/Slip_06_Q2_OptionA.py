import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

# Salary Prediction Dataset
data = {
    'Years_Experience': [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
    'Education_Level': [1, 1, 2, 2, 3, 2, 3, 3, 4, 4], # 1:Bachelors, 2:Masters etc.
    'Salary': [45000, 50000, 60000, 65000, 75000, 70000, 85000, 90000, 105000, 110000]
}
df = pd.DataFrame(data)

X = df[['Years_Experience', 'Education_Level']]
y = df['Salary']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

model = LinearRegression()
model.fit(X_train, y_train)

y_pred = model.predict(X_test)
print("=== Multiple Linear Regression for Salary Prediction ===")
print("R2 Score:", r2_score(y_test, y_pred))
print("Mean Squared Error:", mean_squared_error(y_test, y_pred))
