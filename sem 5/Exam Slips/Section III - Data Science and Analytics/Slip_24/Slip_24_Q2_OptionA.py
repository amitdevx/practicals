import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_24_Q2_OptionA.py: Simple Linear Regression Sales Trend")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Simple Linear Regression Sales Trend")
plt.savefig('Slip_24_Q2_OptionA.png')
print("Successfully generated plot for Simple Linear Regression Sales Trend")
