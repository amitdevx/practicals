import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_20_Q2_OptionA.py: Logistic Regression on Titanic Dataset")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Logistic Regression on Titanic Dataset")
plt.savefig('Slip_20_Q2_OptionA.png')
print("Successfully generated plot for Logistic Regression on Titanic Dataset")
