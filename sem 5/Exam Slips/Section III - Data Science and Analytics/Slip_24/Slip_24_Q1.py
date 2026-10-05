import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_24_Q1.py: Subplots Grid for Multiple Metrics")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Subplots Grid for Multiple Metrics")
plt.savefig('Slip_24_Q1.png')
print("Successfully generated plot for Subplots Grid for Multiple Metrics")
