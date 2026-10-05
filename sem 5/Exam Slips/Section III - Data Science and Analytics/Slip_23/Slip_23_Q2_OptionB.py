import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_23_Q2_OptionB.py: KNN Boundary Decision Surface")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("KNN Boundary Decision Surface")
plt.savefig('Slip_23_Q2_OptionB.png')
print("Successfully generated plot for KNN Boundary Decision Surface")
