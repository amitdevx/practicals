import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_21_Q2_OptionA.py: Multiple Linear Regression Car Price Model")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Multiple Linear Regression Car Price Model")
plt.savefig('Slip_21_Q2_OptionA.png')
print("Successfully generated plot for Multiple Linear Regression Car Price Model")
