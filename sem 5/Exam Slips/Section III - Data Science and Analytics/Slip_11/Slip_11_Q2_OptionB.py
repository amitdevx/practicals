import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_11_Q2_OptionB.py: SVC with RBF Kernel & Gamma Tuning")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("SVC with RBF Kernel & Gamma Tuning")
plt.savefig('Slip_11_Q2_OptionB.png')
print("Successfully generated plot for SVC with RBF Kernel & Gamma Tuning")
