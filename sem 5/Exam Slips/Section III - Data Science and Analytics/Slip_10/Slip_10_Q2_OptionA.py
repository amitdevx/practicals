import pandas as pd
from sklearn.ensemble import RandomForestRegressor
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score
import numpy as np

data = {
    'Square_Feet': [1500, 1800, 2400, 3000, 3500, 1200, 2000, 2200, 2800, 3200],
    'Bedrooms': [3, 4, 4, 5, 5, 2, 3, 4, 4, 5],
    'Age_Years': [10, 15, 20, 5, 2, 30, 12, 18, 8, 3],
    'Price': [250000, 300000, 400000, 500000, 600000, 150000, 280000, 350000, 450000, 550000]
}
df = pd.DataFrame(data)
X = df[['Square_Feet', 'Bedrooms', 'Age_Years']]
y = df['Price']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

model = RandomForestRegressor(n_estimators=50, random_state=42)
model.fit(X_train, y_train)
y_pred = model.predict(X_test)

print("MAE:", mean_absolute_error(y_test, y_pred))
print("RMSE:", np.sqrt(mean_squared_error(y_test, y_pred)))
print("R2 Score:", r2_score(y_test, y_pred))
