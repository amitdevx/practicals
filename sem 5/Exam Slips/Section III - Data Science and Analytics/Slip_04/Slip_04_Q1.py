import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

# Data given in the question
payment_methods = ["UPI", "Credit Card", "Debit Card", "Cash", "Net Banking"]
customers = [150, 80, 60, 40, 30]

# Create a Pie Chart
plt.figure(figsize=(8, 8))
plt.pie(customers, labels=payment_methods, autopct='%1.1f%%', startangle=140, 
        colors=['#66b3ff', '#ff9999', '#99ff99', '#ffcc99', '#c2c2f0'])
plt.title('Preferred Payment Methods Among Customers')
plt.savefig('payment_methods_pie.png')
print("Pie chart saved as payment_methods_pie.png")
