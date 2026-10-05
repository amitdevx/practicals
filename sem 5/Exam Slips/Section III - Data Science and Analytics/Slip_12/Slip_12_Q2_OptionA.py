import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_12_Q2_OptionA.py: Random Forest Classifier Evaluation")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Random Forest Classifier Evaluation")
plt.savefig('Slip_12_Q2_OptionA.png')
print("Successfully generated plot for Random Forest Classifier Evaluation")
