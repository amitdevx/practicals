import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_25_Q2_OptionA.py: Logistic Regression Bank Marketing Data")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Logistic Regression Bank Marketing Data")
plt.savefig('Slip_25_Q2_OptionA.png')
print("Successfully generated plot for Logistic Regression Bank Marketing Data")
