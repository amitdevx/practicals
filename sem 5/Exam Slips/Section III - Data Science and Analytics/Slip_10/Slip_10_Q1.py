import matplotlib.pyplot as plt

categories = ['HR', 'Finance', 'IT', 'Sales', 'Marketing']
counts = [45, 60, 140, 95, 50]

plt.figure(figsize=(8, 4.5))
plt.bar(categories, counts, color=['#3498db', '#e67e22', '#2ecc71', '#9b59b6', '#f1c40f'])
plt.title('Department Employee Distribution (Slip 10)')
plt.xlabel('Department')
plt.ylabel('Employees')
plt.tight_layout()
plt.savefig('ds_slip_10_q1.png')
print("[+] Bar chart saved.")
