import pandas as pd
import matplotlib.pyplot as plt

sales_data = {
    'Month': ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun'],
    'Sales_Units': [1200, 1350, 1100, 1600, 1850, 2100]
}
df = pd.DataFrame(sales_data)

plt.figure(figsize=(8, 4.5))
plt.plot(df['Month'], df['Sales_Units'], marker='o', color='#2980b9', linewidth=2.5, markersize=7)
plt.title('Monthly Sales Trend', fontsize=14, fontweight='bold')
plt.xlabel('Month', fontsize=12)
plt.ylabel('Sales (Units)', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.6)
plt.tight_layout()
plt.savefig('ds_slip_05_q1_linechart.png')
print("[+] Line chart saved as ds_slip_05_q1_linechart.png")
