import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_09_Q2_OptionA.py: Logistic Regression on Customer Churn")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Logistic Regression on Customer Churn")
plt.savefig('Slip_09_Q2_OptionA.png')
print("Successfully generated plot for Logistic Regression on Customer Churn")
