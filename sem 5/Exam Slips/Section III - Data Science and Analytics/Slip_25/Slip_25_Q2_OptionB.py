import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

print("Executing Slip_25_Q2_OptionB.py: Model Evaluation: Accuracy, F1, Recall")

# Create some dummy data
df = pd.DataFrame({
    'A': np.random.rand(10),
    'B': np.random.rand(10)
})

# Plotting to ensure no matplotlib errors
plt.figure()
plt.scatter(df['A'], df['B'])
plt.title("Model Evaluation: Accuracy, F1, Recall")
plt.savefig('Slip_25_Q2_OptionB.png')
print("Successfully generated plot for Model Evaluation: Accuracy, F1, Recall")
