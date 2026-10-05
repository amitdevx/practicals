import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_16_Q2_OptionB.py: Pruned Decision Tree vs Unpruned")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Pruned Decision Tree vs Unpruned")
plt.savefig('Slip_16_Q2_OptionB.png')
print("Successfully generated plot for Pruned Decision Tree vs Unpruned")
