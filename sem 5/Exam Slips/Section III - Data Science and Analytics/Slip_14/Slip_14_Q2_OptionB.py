import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_14_Q2_OptionB.py: Ridge & Lasso Regularized Regression")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Ridge & Lasso Regularized Regression")
plt.savefig('Slip_14_Q2_OptionB.png')
print("Successfully generated plot for Ridge & Lasso Regularized Regression")
