import numpy as np
import pandas as pd
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

# Online Food Delivery dataset simulation
np.random.seed(42)
n = 150
order_value = np.random.randint(150, 1500, n)
delivery_time = np.random.randint(15, 60, n)
discount = np.random.randint(0, 50, n)
# 1 = Repeat Customer, 0 = Non-repeat
repeat = (order_value * 0.001 - delivery_time * 0.02 + discount * 0.05 > 0.5).astype(int)

df = pd.DataFrame({'Order_Value': order_value, 'Delivery_Time': delivery_time, 'Discount': discount, 'Repeat_Customer': repeat})

X = df[['Order_Value', 'Delivery_Time', 'Discount']]
y = df['Repeat_Customer']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=42)
model = LogisticRegression()
model.fit(X_train, y_train)

preds = model.predict(X_test)
print("=== Online Food Delivery Logistic Regression ===")
print("Model Accuracy:", accuracy_score(y_test, preds))
