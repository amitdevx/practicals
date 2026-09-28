import numpy as np
import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, r2_score

# YouTube Dataset: Views, Likes, Comments -> Revenue/Engagement
np.random.seed(42)
n = 100
views = np.random.randint(1000, 500000, n)
likes = (views * np.random.uniform(0.04, 0.08)).astype(int)
comments = (views * np.random.uniform(0.005, 0.015)).astype(int)
revenue = views * 0.002 + likes * 0.01 + np.random.normal(0, 20, n)

df = pd.DataFrame({'Views': views, 'Likes': likes, 'Comments': comments, 'Revenue': revenue})

X = df[['Views', 'Likes', 'Comments']]
y = df['Revenue']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

model = LinearRegression()
model.fit(X_train, y_train)

y_pred = model.predict(X_test)
print("=== YouTube Multiple Linear Regression ===")
print("R2 Score:", r2_score(y_test, y_pred))
print("MSE:", mean_squared_error(y_test, y_pred))
