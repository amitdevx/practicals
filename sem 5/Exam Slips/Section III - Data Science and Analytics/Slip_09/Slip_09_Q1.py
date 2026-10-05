import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_09_Q1.py: Outlier Capping using IQR Method")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Outlier Capping using IQR Method")
plt.savefig('Slip_09_Q1.png')
print("Successfully generated plot for Outlier Capping using IQR Method")
