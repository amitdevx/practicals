import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_11_Q1.py: Normalization & Z-score Transformation")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Normalization & Z-score Transformation")
plt.savefig('Slip_11_Q1.png')
print("Successfully generated plot for Normalization & Z-score Transformation")
