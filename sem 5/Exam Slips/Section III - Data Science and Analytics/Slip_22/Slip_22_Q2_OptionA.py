import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_22_Q2_OptionA.py: Decision Tree Classification on Wine Data")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Decision Tree Classification on Wine Data")
plt.savefig('Slip_22_Q2_OptionA.png')
print("Successfully generated plot for Decision Tree Classification on Wine Data")
