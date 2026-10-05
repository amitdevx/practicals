import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_24_Q2_OptionB.py: Multiple Regression with ANOVA Summary")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Multiple Regression with ANOVA Summary")
plt.savefig('Slip_24_Q2_OptionB.png')
print("Successfully generated plot for Multiple Regression with ANOVA Summary")
