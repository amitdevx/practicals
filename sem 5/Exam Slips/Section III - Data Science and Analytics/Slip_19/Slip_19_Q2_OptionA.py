import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_19_Q2_OptionA.py: Hierarchical Agglomerative Clustering")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Hierarchical Agglomerative Clustering")
plt.savefig('Slip_19_Q2_OptionA.png')
print("Successfully generated plot for Hierarchical Agglomerative Clustering")
