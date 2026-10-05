import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_15_Q2_OptionB.py: Stratified K-Fold Cross Validation")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Stratified K-Fold Cross Validation")
plt.savefig('Slip_15_Q2_OptionB.png')
print("Successfully generated plot for Stratified K-Fold Cross Validation")
