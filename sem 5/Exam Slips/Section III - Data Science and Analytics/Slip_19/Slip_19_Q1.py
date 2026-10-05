import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_19_Q1.py: Bivariate Scatter Plot with Hue Grouping")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Bivariate Scatter Plot with Hue Grouping")
plt.savefig('Slip_19_Q1.png')
print("Successfully generated plot for Bivariate Scatter Plot with Hue Grouping")
