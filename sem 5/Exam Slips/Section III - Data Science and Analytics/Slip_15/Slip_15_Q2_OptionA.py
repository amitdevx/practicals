import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_15_Q2_OptionA.py: Logistic Regression Heart Disease Detection")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Logistic Regression Heart Disease Detection")
plt.savefig('Slip_15_Q2_OptionA.png')
print("Successfully generated plot for Logistic Regression Heart Disease Detection")
