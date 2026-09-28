import matplotlib.pyplot as plt

payment_methods = ['Credit Card', 'UPI / NetBanking', 'Cash on Delivery', 'Debit Card', 'Digital Wallet']
counts = [350, 820, 210, 180, 140]

plt.figure(figsize=(7, 7))
plt.pie(counts, labels=payment_methods, autopct='%1.1f%%', startangle=140, colors=['#3498db', '#2ecc71', '#e74c3c', '#f1c40f', '#9b59b6'])
plt.title('Customer Preferred Payment Methods', fontsize=14, fontweight='bold')
plt.tight_layout()
plt.savefig('ds_slip_04_q1_piechart.png')
print("[+] Pie chart saved as ds_slip_04_q1_piechart.png")
