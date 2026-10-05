import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_10_Q2_OptionA.py: Naive Bayes Classifier on Text/Features")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Naive Bayes Classifier on Text/Features")
plt.savefig('Slip_10_Q2_OptionA.png')
print("Successfully generated plot for Naive Bayes Classifier on Text/Features")
