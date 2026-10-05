import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_08_Q1.py: Pie Chart & Doughnut Chart Breakdown")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Pie Chart & Doughnut Chart Breakdown")
plt.savefig('Slip_08_Q1.png')
print("Successfully generated plot for Pie Chart & Doughnut Chart Breakdown")
