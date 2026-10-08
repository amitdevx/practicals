import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

courses = ["BCA", "BBA", "B.Com", "B.Sc", "BA"]
students = [60, 45, 75, 50, 35]

plt.figure(figsize=(8,6))
plt.bar(courses, students, color=['blue', 'green', 'red', 'purple', 'orange'])
plt.title('Number of Students Enrolled in Different Courses')
plt.xlabel('Courses')
plt.ylabel('Number of Students')
plt.savefig('courses_bar.png')
print("Plot saved as courses_bar.png")
