import pandas as pd
import numpy as np
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

data = {
    'Danceability': [0.5, 0.6, 0.7, 0.8, 0.9, 0.4, 0.3, 0.85, 0.75, 0.95],
    'Popularity': [30, 45, 60, 80, 95, 20, 15, 85, 70, 99]
}
df = pd.DataFrame(data)
X = df[['Danceability']]
y = df['Popularity']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

poly = PolynomialFeatures(degree=2)
X_poly_train = poly.fit_transform(X_train)
X_poly_test = poly.transform(X_test)

model = LinearRegression()
model.fit(X_poly_train, y_train)
y_pred = model.predict(X_poly_test)

print("MAE:", mean_absolute_error(y_test, y_pred))
print("RMSE:", np.sqrt(mean_squared_error(y_test, y_pred)))
print("R2 Score:", r2_score(y_test, y_pred))

X_sorted = np.sort(X.values, axis=0)
X_poly_sorted = poly.transform(X_sorted)
y_poly_pred = model.predict(X_poly_sorted)

plt.figure(figsize=(8,6))
plt.scatter(X, y, color='blue', label='Actual Data')
plt.plot(X_sorted, y_poly_pred, color='red', label='Polynomial Regression')
plt.title('Song Popularity Prediction')
plt.xlabel('Danceability')
plt.ylabel('Popularity')
plt.legend()
plt.savefig('popularity_poly.png')
