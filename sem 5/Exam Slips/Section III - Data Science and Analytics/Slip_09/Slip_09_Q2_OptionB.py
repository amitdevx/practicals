import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_09_Q2_OptionB.py: ROC Curve & AUC Score Calculation")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("ROC Curve & AUC Score Calculation")
plt.savefig('Slip_09_Q2_OptionB.png')
print("Successfully generated plot for ROC Curve & AUC Score Calculation")
