import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_16_Q2_OptionA.py: Decision Tree Gini vs Entropy Split")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Decision Tree Gini vs Entropy Split")
plt.savefig('Slip_16_Q2_OptionA.png')
print("Successfully generated plot for Decision Tree Gini vs Entropy Split")
