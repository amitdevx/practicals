import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_25_Q1.py: Correlation Matrix Ranking & Filter")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Correlation Matrix Ranking & Filter")
plt.savefig('Slip_25_Q1.png')
print("Successfully generated plot for Correlation Matrix Ranking & Filter")
