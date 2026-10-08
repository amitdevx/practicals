import pandas as pd
import numpy as np
from sklearn.linear_model import LinearRegression
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

# Create YouTube Video dataset
data = {
    'Subscribers': [1000, 2500, 5000, 8000, 12000, 15000, 20000, 25000, 30000, 40000],
    'Video_Views': [5000, 12000, 26000, 41000, 62000, 76000, 105000, 128000, 152000, 205000]
}
df = pd.DataFrame(data)

# Reshape data
X = df[['Subscribers']] # Predictor
y = df['Video_Views'] # Target

# Apply Linear Regression
model = LinearRegression()
model.fit(X, y)
y_pred = model.predict(X)

print("Intercept:", model.intercept_)
print("Coefficient:", model.coef_[0])

# Visualize the relationship
plt.figure(figsize=(8, 6))
plt.scatter(X, y, color='blue', label='Actual Data')
plt.plot(X, y_pred, color='red', label='Regression Line')
plt.title('YouTube Subscribers vs Video Views')
plt.xlabel('Subscribers')
plt.ylabel('Video Views')
plt.legend()
plt.savefig('youtube_regression.png')
print("Plot saved as youtube_regression.png")
