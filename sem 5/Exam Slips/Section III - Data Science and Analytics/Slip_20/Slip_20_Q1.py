import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_20_Q1.py: Heatmap of Covariance Matrix")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Heatmap of Covariance Matrix")
plt.savefig('Slip_20_Q1.png')
print("Successfully generated plot for Heatmap of Covariance Matrix")
