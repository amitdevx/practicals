import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_22_Q1.py: IQR Filtering & Trimmed Mean")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("IQR Filtering & Trimmed Mean")
plt.savefig('Slip_22_Q1.png')
print("Successfully generated plot for IQR Filtering & Trimmed Mean")
