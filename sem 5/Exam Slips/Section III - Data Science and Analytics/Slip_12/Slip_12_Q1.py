import pandas as pd
import matplotlib.pyplot as plt

# Synthetic Titanic sample
df = pd.DataFrame({
    'Pclass': [1, 2, 3, 1, 3, 3, 2, 1, 3, 2],
    'Survived': [1, 1, 0, 1, 0, 0, 0, 1, 0, 1]
})

plt.figure(figsize=(10, 4))
plt.subplot(1, 2, 1)
df['Pclass'].value_counts().sort_index().plot(kind='bar', color='teal')
plt.title('Passenger Class Distribution')

plt.subplot(1, 2, 2)
df['Survived'].value_counts().plot(kind='pie', autopct='%1.1f%%', labels=['Died', 'Survived'], colors=['#e74c3c', '#2ecc71'])
plt.title('Survival Ratio')
plt.tight_layout()
plt.savefig('ds_slip_12_q1.png')
print("[+] Titanic charts saved.")
