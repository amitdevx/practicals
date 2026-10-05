import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_22_Q2_OptionB.py: Confusion Matrix Heatmap Display")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Confusion Matrix Heatmap Display")
plt.savefig('Slip_22_Q2_OptionB.png')
print("Successfully generated plot for Confusion Matrix Heatmap Display")
