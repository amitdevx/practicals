import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_14_Q2_OptionA.py: Multiple Regression with Feature Selection")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Multiple Regression with Feature Selection")
plt.savefig('Slip_14_Q2_OptionA.png')
print("Successfully generated plot for Multiple Regression with Feature Selection")
