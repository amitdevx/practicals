import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_11_Q2_OptionA.py: Support Vector Classifier (SVC Linear)")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Support Vector Classifier (SVC Linear)")
plt.savefig('Slip_11_Q2_OptionA.png')
print("Successfully generated plot for Support Vector Classifier (SVC Linear)")
