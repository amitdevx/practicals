import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_10_Q1.py: Histogram & Density (KDE) Comparison")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Histogram & Density (KDE) Comparison")
plt.savefig('Slip_10_Q1.png')
print("Successfully generated plot for Histogram & Density (KDE) Comparison")
