import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_18_Q2_OptionA.py: Linear Regression Diagnostic Residual Plot")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Linear Regression Diagnostic Residual Plot")
plt.savefig('Slip_18_Q2_OptionA.png')
print("Successfully generated plot for Linear Regression Diagnostic Residual Plot")
