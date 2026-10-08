import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
from sklearn.metrics import r2_score
import matplotlib
matplotlib.use('Agg')

# Dummy Car Price dataset
df = pd.DataFrame({
    'Vehicle_Age': [2, 4, 5, 8, 10],
    'Present_Price': [5.5, 6.0, 7.5, 8.0, 10.0],
    'Kms_Driven': [20000, 40000, 50000, 80000, 100000],
    'Selling_Price': [4.5, 4.0, 5.0, 3.5, 3.0]
})

X = df[['Vehicle_Age', 'Present_Price', 'Kms_Driven']]
y = df['Selling_Price']

poly = PolynomialFeatures(degree=2)
X_poly = poly.fit_transform(X)

model = LinearRegression()
model.fit(X_poly, y)
y_pred = model.predict(X_poly)

print("R2 Score:", r2_score(y, y_pred))

# Simple visualization vs Vehicle_Age
plt.figure()
plt.scatter(df['Vehicle_Age'], y, color='blue', label='Actual')
# Sort for smooth curve
sort_idx = np.argsort(df['Vehicle_Age'])
plt.plot(df['Vehicle_Age'].iloc[sort_idx], y_pred[sort_idx], color='red', label='Polynomial Fit')
plt.title("Polynomial Regression: Selling Price vs Vehicle Age")
plt.xlabel("Vehicle Age")
plt.ylabel("Selling Price")
plt.legend()
plt.savefig('poly_car.png')
print("Plot saved as poly_car.png")
