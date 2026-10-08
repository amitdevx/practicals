import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.metrics import r2_score
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

data = {
    'Training_Hours': [5, 10, 15, 20, 25, 30, 35, 40],
    'Performance_Score': [50, 55, 65, 70, 75, 85, 90, 95]
}
df = pd.DataFrame(data)
X = df[['Training_Hours']]
y = df['Performance_Score']

model = LinearRegression()
model.fit(X, y)
y_pred = model.predict(X)

print("R2 Score:", r2_score(y, y_pred))

plt.figure(figsize=(8, 6))
plt.scatter(X, y, color='blue', label='Actual')
plt.plot(X, y_pred, color='red', label='Regression Line')
plt.title('Sports Performance Prediction')
plt.xlabel('Training Hours Per Week')
plt.ylabel('Performance Score')
plt.legend()
plt.savefig('performance_regression.png')
