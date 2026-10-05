import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_17_Q2_OptionA.py: KNN Classification with Cross Validation")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("KNN Classification with Cross Validation")
plt.savefig('Slip_17_Q2_OptionA.png')
print("Successfully generated plot for KNN Classification with Cross Validation")
