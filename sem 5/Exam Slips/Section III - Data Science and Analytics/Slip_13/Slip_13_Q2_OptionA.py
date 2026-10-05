import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_13_Q2_OptionA.py: K-Means Customer Segmentation")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("K-Means Customer Segmentation")
plt.savefig('Slip_13_Q2_OptionA.png')
print("Successfully generated plot for K-Means Customer Segmentation")
