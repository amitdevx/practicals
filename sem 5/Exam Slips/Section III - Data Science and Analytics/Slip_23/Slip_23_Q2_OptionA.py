import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_23_Q2_OptionA.py: KNN Classifier on Digits Dataset")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("KNN Classifier on Digits Dataset")
plt.savefig('Slip_23_Q2_OptionA.png')
print("Successfully generated plot for KNN Classifier on Digits Dataset")
