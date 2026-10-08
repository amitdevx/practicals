import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error, r2_score
import matplotlib
matplotlib.use('Agg')

df = pd.DataFrame({
    'Rainfall': [100, 200, 300, None, 500, 600],
    'Yield': [50, 70, 90, 110, 130, 150]
})

# Handle missing
df['Rainfall'] = df['Rainfall'].fillna(df['Rainfall'].mean())

X = df[['Rainfall']]
y = df['Yield']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

model = LinearRegression()
model.fit(X_train, y_train)
y_pred = model.predict(X_test)

print("MAE:", mean_absolute_error(y_test, y_pred))
print("R2 Score:", r2_score(y_test, y_pred))

plt.figure()
plt.scatter(X, y, color='blue', label='Actual')
plt.plot(X, model.predict(X), color='red', label='Regression Line')
plt.title("Crop Yield vs Rainfall")
plt.xlabel("Rainfall")
plt.ylabel("Yield")
plt.legend()
plt.savefig('crop_yield.png')
print("Plot saved as crop_yield.png")
