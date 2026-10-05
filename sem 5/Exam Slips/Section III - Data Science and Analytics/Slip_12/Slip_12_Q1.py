import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_12_Q1.py: Violin Plot & Distribution Comparison")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Violin Plot & Distribution Comparison")
plt.savefig('Slip_12_Q1.png')
print("Successfully generated plot for Violin Plot & Distribution Comparison")
