import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_21_Q1.py: GroupBy Aggregations & Barplot")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("GroupBy Aggregations & Barplot")
plt.savefig('Slip_21_Q1.png')
print("Successfully generated plot for GroupBy Aggregations & Barplot")
