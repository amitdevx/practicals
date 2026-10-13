import pandas as pd
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
from sklearn.metrics import r2_score

# Car Price Prediction dataset
df = pd.DataFrame({
    'Vehicle_Age': [1, 2, 3, 5, 7, 8, 10, 12],
    'Present_Price': [9.5, 7.8, 8.5, 9.5, 6.8, 5.3, 8.6, 6.8],
    'Kms_Driven': [7000, 15000, 24000, 49000, 60000, 68000, 89000, 102000],
    'Selling_Price': [7.2, 6.5, 6.1, 5.2, 3.7, 3.1, 2.8, 2.1]
})

print("Car Price Dataset:")
print(df)

X = df[['Vehicle_Age', 'Present_Price', 'Kms_Driven']]
y = df['Selling_Price']

# Polynomial Regression (degree = 2)
poly = PolynomialFeatures(degree=2)
X_poly = poly.fit_transform(X)

model = LinearRegression()
model.fit(X_poly, y)
y_pred = model.predict(X_poly)

print("\nR2 Score:", r2_score(y, y_pred))

# Visualization
plt.figure()
plt.scatter(df['Vehicle_Age'], y, color='blue', label='Actual Points')
sort_idx = np.argsort(df['Vehicle_Age'])
plt.plot(df['Vehicle_Age'].iloc[sort_idx], y_pred[sort_idx], color='red', label='Polynomial Fit')
plt.title("Polynomial Regression: Selling Price vs Vehicle Age")
plt.xlabel("Vehicle Age")
plt.ylabel("Selling Price")
plt.legend()
plt.savefig('poly_car.png')
print("Plot saved as poly_car.png")
