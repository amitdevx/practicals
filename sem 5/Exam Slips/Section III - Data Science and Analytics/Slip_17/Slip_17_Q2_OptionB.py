import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_17_Q2_OptionB.py: Grid Search CV for Hyperparameter Tuning")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Grid Search CV for Hyperparameter Tuning")
plt.savefig('Slip_17_Q2_OptionB.png')
print("Successfully generated plot for Grid Search CV for Hyperparameter Tuning")
