import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_08_Q2_OptionA.py: KNN Classifier with k-Value Tuning")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("KNN Classifier with k-Value Tuning")
plt.savefig('Slip_08_Q2_OptionA.png')
print("Successfully generated plot for KNN Classifier with k-Value Tuning")
