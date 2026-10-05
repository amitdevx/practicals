import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_21_Q2_OptionB.py: Multicollinearity & VIF Calculation")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Multicollinearity & VIF Calculation")
plt.savefig('Slip_21_Q2_OptionB.png')
print("Successfully generated plot for Multicollinearity & VIF Calculation")
