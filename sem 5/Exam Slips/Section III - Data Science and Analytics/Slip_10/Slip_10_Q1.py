import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

transport = ['Train', 'Bicycle', 'Bike', 'Car', 'Bus']
employees = [220, 60, 70, 80, 40]

plt.figure(figsize=(8,8))
plt.pie(employees, labels=transport, autopct='%1.1f%%', colors=['#ff9999', '#66b3ff', '#99ff99', '#ffcc99', '#c2c2f0'])
plt.title('Preferred Mode of Transportation Among Employees')
plt.savefig('transport_pie.png')
print("Saved transport_pie.png")
