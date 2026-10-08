import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

departments = ['HR', 'Finance', 'IT', 'Sales', 'Marketing']
employees = [15, 25, 60, 40, 30]

plt.figure(figsize=(8,6))
plt.bar(departments, employees, color='teal')
plt.title('Number of Employees in Different Departments')
plt.xlabel('Department')
plt.ylabel('Number of Employees')
plt.savefig('departments_bar.png')
print("Saved departments_bar.png")
