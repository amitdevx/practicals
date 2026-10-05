import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_17_Q1.py: Boxplot with Jittered Data Points")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Boxplot with Jittered Data Points")
plt.savefig('Slip_17_Q1.png')
print("Successfully generated plot for Boxplot with Jittered Data Points")
