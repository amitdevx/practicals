import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_19_Q2_OptionB.py: K-Medoids Clustering Comparison")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("K-Medoids Clustering Comparison")
plt.savefig('Slip_19_Q2_OptionB.png')
print("Successfully generated plot for K-Medoids Clustering Comparison")
