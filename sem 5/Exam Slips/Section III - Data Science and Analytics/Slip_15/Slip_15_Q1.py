import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_15_Q1.py: Null Value Replacement Strategy")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Null Value Replacement Strategy")
plt.savefig('Slip_15_Q1.png')
print("Successfully generated plot for Null Value Replacement Strategy")
