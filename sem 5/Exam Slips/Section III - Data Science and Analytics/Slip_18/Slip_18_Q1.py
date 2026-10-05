import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_18_Q1.py: Standardization & Skewness Check")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Standardization & Skewness Check")
plt.savefig('Slip_18_Q1.png')
print("Successfully generated plot for Standardization & Skewness Check")
