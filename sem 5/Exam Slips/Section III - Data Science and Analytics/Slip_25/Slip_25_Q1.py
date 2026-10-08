import matplotlib.pyplot as plt
import matplotlib
matplotlib.use('Agg')

courses = ["BCA", "BBA", "B.Com", "B.Sc", "BA"]
students = [60, 45, 75, 50, 35]

plt.figure()
plt.bar(courses, students, color=['red', 'blue', 'green', 'orange', 'purple'])
plt.title("Number of Students Enrolled per Course")
plt.xlabel("Courses")
plt.ylabel("Number of Students")
plt.savefig('course_bar.png')
print("Plot saved as course_bar.png")
