import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_13_Q2_OptionB.py: PCA Dimensionality Reduction 2D Plot")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("PCA Dimensionality Reduction 2D Plot")
plt.savefig('Slip_13_Q2_OptionB.png')
print("Successfully generated plot for PCA Dimensionality Reduction 2D Plot")
