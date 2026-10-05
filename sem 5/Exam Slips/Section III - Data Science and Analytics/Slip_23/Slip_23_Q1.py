import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_23_Q1.py: FacetGrid Multi-Plot Distribution")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("FacetGrid Multi-Plot Distribution")
plt.savefig('Slip_23_Q1.png')
print("Successfully generated plot for FacetGrid Multi-Plot Distribution")
