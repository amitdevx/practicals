import sys
from pathlib import Path
sys.path.append('/home/amitdevx')
import maths_notebook_utils as mnu

BASE_DIR = Path('/home/amitdevx/jupyter_notebook/sem4/Exam Slips/Section IV: Mathematics for Computer Science-II')

solutions = {
    8: {
        "1.1": """import matplotlib.pyplot as plt

cities = ['Satara', 'Dhule', 'Nashik', 'Nagpur', 'Pune']
temperatures_c = [20, 32, 25, 40, 30]

plt.figure(figsize=(8, 5))
bars = plt.bar(cities, temperatures_c, color='orange', edgecolor='black')
plt.title('City-wise Temperatures')
plt.xlabel('City')
plt.ylabel('Temperature (°C)')
plt.grid(axis='y', linestyle='--', alpha=0.3)

for bar, temp in zip(bars, temperatures_c):
    plt.text(bar.get_x() + bar.get_width() / 2, temp + 0.5, f"{temp}°C", ha='center', va='bottom')

plt.tight_layout()
plt.show()
""",
        "1.2": """import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(-np.pi, np.pi, 400)
y = np.cos(x) + np.sin(x)

plt.figure(figsize=(8, 4))
plt.plot(x, y, color='maroon', linestyle='--', linewidth=2, label=r'$y=\cos(x)+\sin(x)$')
plt.title('Plot of $y = \cos(x) + \sin(x)$ on [-π, π]')
plt.xlabel('x (radians)')
plt.ylabel('y')
plt.axhline(0, color='black', linewidth=0.8)
plt.axvline(0, color='black', linewidth=0.8)
plt.grid(True, linestyle=':')
plt.legend()
plt.show()
""",
        "1.3": """import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401

x = np.linspace(0, 2 * np.pi, 60)
y = np.linspace(0, 2 * np.pi, 60)
X, Y = np.meshgrid(x, y)
Z = np.sin(np.sqrt(X ** 2 + Y ** 2))

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(X, Y, Z, color='brown', linewidth=0.8)
ax.set_title(r'Wireframe of $f(x, y) = \sin(\sqrt{x^2 + y^2})$')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('f(x, y)')
plt.show()
""",
        "1.4": """import sympy as sp

L = sp.Point(2, 6)
M = sp.Point(-2, 9)
N = sp.Point(-3, -5)

print(f"Points: L={L}, M={M}, N={N}")
print(f"Collinear: {sp.Point.is_collinear(L, M, N)}")

print(f"Distance LM: {L.distance(M):.4f}")
print(f"Distance MN: {M.distance(N):.4f}")
print(f"Distance LN: {L.distance(N):.4f}")

line_LM = sp.Line(L, M)
print(f"Slope of line LM: {line_LM.slope}")
print(f"Equation of line LM: {sp.Eq(line_LM.equation().lhs, line_LM.equation().rhs)}")
""",
        "1.5": """import sympy as sp

polygon = sp.RegularPolygon(sp.Point(0, 0), 6, 6)
print(f"Area: {sp.nsimplify(polygon.area)}")
print(f"Perimeter: {sp.nsimplify(polygon.perimeter)}")
print("Original vertices:")
for idx, vertex in enumerate(polygon.vertices, start=1):
    print(f"  V{idx}: {vertex}")

translated_vertices = [vertex.translate(8, 0) for vertex in polygon.vertices]
print("Vertices after translation by 8 units along +x:")
for idx, vertex in enumerate(translated_vertices, start=1):
    print(f"  V{idx}: {vertex}")
""",
        "2.1": """import numpy as np
import matplotlib.pyplot as plt

points = np.array([[-2, 5], [-2, 9], [3, 5], [4, 2]], dtype=float)

def close_loop(pts: np.ndarray) -> np.ndarray:
    return np.vstack([pts, pts[0]])

fig, ax = plt.subplots(figsize=(7, 7))
loop = close_loop(points)
ax.plot(loop[:, 0], loop[:, 1], 'o-', label='Original ABCD', linewidth=2)

translated = points + np.array([2, -5])
loop = close_loop(translated)
ax.plot(loop[:, 0], loop[:, 1], 's-', label='Translation ( +2 , -5 )')

theta = np.deg2rad(60)
rot_matrix = np.array([[np.cos(theta), -np.sin(theta)],
                       [np.sin(theta),  np.cos(theta)]])
rotated = points @ rot_matrix.T
loop = close_loop(rotated)
ax.plot(loop[:, 0], loop[:, 1], 'd-', label='Rotation 60° about origin')

shear_matrix = np.array([[1, 5], [0, 1]], dtype=float)
sheared = points @ shear_matrix.T
loop = close_loop(sheared)
ax.plot(loop[:, 0], loop[:, 1], '^-', label='Shear along x (factor 5)')

ax.set_aspect('equal')
ax.set_title('Transformations of Polygon ABCD')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.grid(True, linestyle=':')
ax.legend(loc='best')
plt.show()
""",
        "2.2": """import numpy as np
import matplotlib.pyplot as plt

radius = 9.0
n_points = 100
delta = 2 * np.pi / n_points
points = []
x, y = radius, 0.0

c, s = np.cos(delta), np.sin(delta)
for _ in range(n_points):
    points.append((x, y))
    x, y = x * c - y * s, x * s + y * c

points = np.array(points)
plt.figure(figsize=(6, 6))
plt.plot(points[:, 0], points[:, 1], 'b-', label=r'$x^2 + y^2 = 81$')
plt.scatter(points[0, 0], points[0, 1], color='red', zorder=5, label='Start point')
plt.title('Iterative generation of circle with radius 9')
plt.xlabel('x')
plt.ylabel('y')
plt.axis('equal')
plt.grid(True, linestyle=':')
plt.legend()
plt.show()
""",
    },
    14: {
        "1.1": """import matplotlib.pyplot as plt

subjects = ['Mathematics', 'English', 'Biology', 'Physics', 'Chemistry']
marks = [68, 45, 79, 56, 70]

plt.figure(figsize=(8, 5))
bars = plt.bar(subjects, marks, color='brown', edgecolor='black')
plt.title('Marks obtained per subject')
plt.xlabel('Subject')
plt.ylabel('Marks')
for bar, mark in zip(bars, marks):
    plt.text(bar.get_x() + bar.get_width() / 2, mark + 1, str(mark), ha='center')
plt.ylim(0, 90)
plt.grid(axis='y', linestyle=':', alpha=0.4)
plt.show()
""",
        "1.2": """import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0.1, 10, 400)
y = np.log(x)

plt.figure(figsize=(8, 4))
plt.plot(x, y, 'r--', linewidth=2, label=r'$y = \\log(x)$')
plt.title(r'Plot of $y = \\log(x)$ on (0, 10]')
plt.xlabel('x')
plt.ylabel('y')
plt.grid(True, linestyle=':')
plt.legend()
plt.show()
""",
        "1.3": """import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401

x = np.linspace(-10, 10, 60)
y = np.linspace(-10, 10, 60)
X, Y = np.meshgrid(x, y)
Z = X ** 3 + Y ** 3

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, Z, color='green', alpha=0.9, edgecolor='none')
ax.set_title(r'Surface of $f(x, y) = x^3 + y^3$')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('f(x, y)')
plt.show()
""",
        "1.4": """import sympy as sp

P = sp.Point(7, 2)
Q = sp.Point(1, 8)
line = sp.Line(P, Q)

print(f"Distance PQ: {P.distance(Q)}")
print(f"Slope of PQ: {line.slope}")
print(f"Equation of PQ: {line.equation()}")
""",
        "1.5": """import sympy as sp

A = sp.Point(2, 2)
B = sp.Point(4, 2)
C = sp.Point(3, 6)
triangle = sp.Triangle(A, B, C)

print(f"Centroid of ΔABC: {triangle.centroid}")
translated = [vertex.translate(2, 0) for vertex in triangle.vertices]
print("Vertices after translation by (2, 0):")
for idx, vertex in enumerate(translated, start=1):
    print(f"  V{idx}: {vertex}")
""",
        "2.1": """import numpy as np
import matplotlib.pyplot as plt

polygon = np.array([[1, 3], [2, 4], [4, 2], [3, 1]], dtype=float)

def close_loop(pts):
    return np.vstack([pts, pts[0]])

fig, ax = plt.subplots(figsize=(7, 7))
ax.axhline(0, color='black', linewidth=0.8)
ax.axvline(0, color='black', linewidth=0.8)
ax.plot(*close_loop(polygon).T, 'k-o', label='Original polygon', linewidth=2)

rot_pi_over_2 = np.array([[0, -1], [1, 0]], dtype=float)
rot_pi = -np.eye(2)

poly_pi_over_2 = polygon @ rot_pi_over_2.T
ax.plot(*close_loop(poly_pi_over_2).T, 'b-s', label='Rotation π/2')

poly_pi = polygon @ rot_pi.T
ax.plot(*close_loop(poly_pi).T, 'r-^', label='Rotation π')

ax.set_aspect('equal')
ax.set_title('Rotations of given polygon')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.grid(True, linestyle=':')
ax.legend(loc='best')
plt.show()
""",
        "2.2": """import numpy as np
import matplotlib.pyplot as plt

a = 1  # because y^2 = 4ax and here 4a = 4
x_min, x_max = 4, 16
n_points = 50
t_min = -np.sqrt(x_min / a)
t_max = np.sqrt(x_max / a)
step = (t_max - t_min) / (n_points - 1)

points = []
t = t_min
for _ in range(n_points):
    x = a * t ** 2
    y = 2 * a * t
    if x_min <= x <= x_max:
        points.append((x, y))
    t += step

points = np.array(points)
plt.figure(figsize=(8, 4))
plt.plot(points[:, 0], points[:, 1], 'm.', label='Upper branch')
plt.plot(points[:, 0], -points[:, 1], 'c.', label='Lower branch')
plt.title(r'Iterative points on $y^2 = 4x$, 4 ≤ x ≤ 16')
plt.xlabel('x')
plt.ylabel('y')
plt.grid(True, linestyle=':')
plt.legend()
plt.show()
""",
    },
    13: {
        "1.1": """import matplotlib.pyplot as plt

subjects = ['Mathematics', 'English', 'Biology', 'Physics', 'Chemistry']
marks = [85, 15, 50, 67, 77]

plt.figure(figsize=(7, 7))
plt.pie(marks, labels=subjects, autopct='%1.1f%%', startangle=90)
plt.title('Subject-wise percentage distribution')
plt.show()
""",
        "1.2": """import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(-np.pi, np.pi, 400)
y = np.cos(x ** 2)

plt.figure(figsize=(8, 4))
plt.plot(x, y, 'r--', linewidth=2, label=r'$y = \\cos(x^2)$')
plt.title(r'Plot of $y = \\cos(x^2)$ on [-π, π]')
plt.xlabel('x (radians)')
plt.ylabel('y')
plt.grid(True, linestyle=':')
plt.legend()
plt.show()
""",
        "1.3": """import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401

x = np.linspace(-10, 10, 60)
y = np.linspace(-10, 10, 60)
X, Y = np.meshgrid(x, y)
Z = X ** 2 - Y ** 2

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(X, Y, Z, color='brown', linewidth=0.8)
ax.set_title(r'Wireframe of $f(x, y) = x^2 - y^2$')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('f(x, y)')
plt.show()
""",
        "1.4": """import sympy as sp

points = [sp.Point(0, 0), sp.Point(1, 1), sp.Point(-1, 1), sp.Point(-1, -1), sp.Point(1, -1)]
polygon = sp.Polygon(*points)
print(f"Centroid of polygon: {polygon.centroid}")

rotated_vertices = [point.rotate(sp.pi, sp.Point(0, 0)) for point in points]
print("Vertices after rotation by π:")
for idx, point in enumerate(rotated_vertices, start=1):
    print(f"  V{idx}: {point}")
""",
        "1.5": """import sympy as sp

A = sp.Point(1, 3)
B = sp.Point(3, 3)
C = sp.Point(4, 5)
triangle = sp.Triangle(A, B, C)

print("Angles of ΔABC:")
for vertex, angle in triangle.angles.items():
    print(f"  At {vertex}: {sp.nsimplify(angle)} radians")

print(f"Area: {triangle.area}")
print(f"Perimeter: {triangle.perimeter}")
""",
        "2.1": """import numpy as np
import matplotlib.pyplot as plt

polygon = np.array([[0, 3], [-3, 3], [-3, 0], [0, 0]], dtype=float)

def close_loop(pts):
    return np.vstack([pts, pts[0]])

fig, ax = plt.subplots(figsize=(7, 7))
ax.plot(*close_loop(polygon).T, 'k-o', label='Original ABCD', linewidth=2)

reflection = polygon[:, ::-1]
ax.plot(*close_loop(reflection).T, 'b-s', label='Reflection about y = x')

scaled = polygon * 4
ax.plot(*close_loop(scaled).T, 'r-^', label='Uniform scaling (factor 4)')

ax.set_aspect('equal')
ax.set_title('Transformations of Polygon ABCD')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.grid(True, linestyle=':')
ax.legend(loc='best')
plt.show()
""",
        "2.2": """import numpy as np
import matplotlib.pyplot as plt

radius = 5.0
n_points = 50
delta = 2 * np.pi / n_points
x, y = radius, 0.0
points = []
c, s = np.cos(delta), np.sin(delta)

for _ in range(n_points):
    points.append((x, y))
    x, y = x * c - y * s, x * s + y * c

points = np.array(points)
plt.figure(figsize=(6, 6))
plt.plot(points[:, 0], points[:, 1], 'c-', label=r'$x^2 + y^2 = 25$')
plt.scatter(points[0, 0], points[0, 1], color='black', label='Start point')
plt.title('Iterative circle with radius 5')
plt.xlabel('x')
plt.ylabel('y')
plt.axis('equal')
plt.grid(True, linestyle=':')
plt.legend()
plt.show()
""",
    },
    12: {
        "1.1": """import matplotlib.pyplot as plt

subjects = ['Mathematics', 'English', 'Biology', 'Physics', 'Chemistry']
marks = [84, 48, 60, 35, 72]

plt.figure(figsize=(7, 7))
plt.pie(marks, labels=subjects, autopct='%1.1f%%', startangle=90, explode=[0.02]*len(subjects))
plt.title('Marks distribution by subject')
plt.show()
""",
        "1.2": """import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(-np.pi, np.pi, 400)
y = np.cos(2 * x)

plt.figure(figsize=(8, 4))
plt.plot(x, y, 'r--', linewidth=2, label=r'$y = \\cos(2x)$')
plt.title(r'Plot of $y = \\cos(2x)$ on [-π, π]')
plt.xlabel('x (radians)')
plt.ylabel('y')
plt.grid(True, linestyle=':')
plt.legend()
plt.show()
""",
        "1.3": """import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401

x = np.linspace(-10, 10, 60)
y = np.linspace(-10, 10, 60)
X, Y = np.meshgrid(x, y)
Z = np.sin(X ** 2 + Y ** 2)

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, Z, cmap='viridis', edgecolor='none')
ax.set_title(r'Surface plot of $f(x, y) = \\sin(x^2 + y^2)$')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('f(x, y)')
plt.show()
""",
        "1.4": """import sympy as sp

P = sp.Point(0, 0)
Q = sp.Point(1, 1)
R = sp.Point(-7, 5)

print(f"Distance PQ: {P.distance(Q)}")
print(f"Distance PR: {P.distance(R)}")
print(f"Midpoint of QR: {Q.midpoint(R)}")
""",
        "1.5": """import sympy as sp

A = sp.Point(1, 1)
B = sp.Point(-1, 1)
C = sp.Point(-1, -1)
D = sp.Point(1, -1)
polygon = sp.Polygon(A, B, C, D)

print("Angles at each vertex:")
for vertex, angle in polygon.angles.items():
    print(f"  At {vertex}: {sp.nsimplify(angle)} radians")

theta = sp.pi / 3
rotated_vertices = [vertex.rotate(theta, sp.Point(0, 0)) for vertex in polygon.vertices]
print(f"Vertices after rotation by π/3: {rotated_vertices}")
""",
        "2.1": """import numpy as np
import matplotlib.pyplot as plt

triangle = np.array([[1, 3], [3, 3], [4, 5]], dtype=float)

def close_loop(pts):
    return np.vstack([pts, pts[0]])

fig, ax = plt.subplots(figsize=(7, 7))
ax.plot(*close_loop(triangle).T, 'k-o', label='Original ΔPQR', linewidth=2)

reflection_y_eq_x = triangle[:, ::-1]
ax.plot(*close_loop(reflection_y_eq_x).T, 'b-s', label='Reflection about y = x')

reflection_y_eq_neg_x = np.column_stack((-triangle[:, 1], -triangle[:, 0]))
ax.plot(*close_loop(reflection_y_eq_neg_x).T, 'r-^', label='Reflection about y = -x')

ax.set_aspect('equal')
ax.set_title('Reflections of Triangle PQR')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.grid(True, linestyle=':')
ax.legend(loc='best')
plt.show()
""",
        "2.2": """import numpy as np
import matplotlib.pyplot as plt

radius = 4.0
n_points = 50
delta = 2 * np.pi / n_points
x, y = radius, 0.0
points = []
c, s = np.cos(delta), np.sin(delta)

for _ in range(n_points):
    points.append((x, y))
    x, y = x * c - y * s, x * s + y * c

points = np.array(points)
plt.figure(figsize=(6, 6))
plt.plot(points[:, 0], points[:, 1], 'g-', label=r'$x^2 + y^2 = 16$')
plt.scatter(points[0, 0], points[0, 1], color='black', label='Start point')
plt.title('Iterative circle with radius 4')
plt.xlabel('x')
plt.ylabel('y')
plt.axis('equal')
plt.grid(True, linestyle=':')
plt.legend()
plt.show()
""",
    },
    11: {
        "1.1": """import matplotlib.pyplot as plt

marks = [71, 29, 35, 21, 66, 32, 24, 27, 38, 44, 51, 42, 49, 86, 94, 46, 57, 47, 41, 50, 46]
bins = [20, 40, 60, 80, 100]

plt.figure(figsize=(8, 5))
plt.hist(marks, bins=bins, color='brown', edgecolor='black')
plt.title('Histogram of Marks (intervals of 20)')
plt.xlabel('Marks range')
plt.ylabel('Number of students')
plt.grid(axis='y', linestyle=':', alpha=0.5)
plt.show()
""",
        "1.2": """import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, 2, 300)
y = x ** 2 + np.cos(2 * x + 5)

plt.figure(figsize=(8, 4))
plt.plot(x, y, color='red', linestyle='-', marker='>', markevery=15, linewidth=2, label=r'$y = x^2 + \\cos(2x + 5)$')
plt.title(r'Plot of $y = x^2 + \\cos(2x + 5)$ on [0, 2]')
plt.xlabel('x')
plt.ylabel('y')
plt.grid(True, linestyle=':')
plt.legend()
plt.show()
""",
        "1.3": """import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401

x = np.linspace(0, 2 * np.pi, 60)
y = np.linspace(0, 2 * np.pi, 60)
X, Y = np.meshgrid(x, y)
Z = np.sin(np.sqrt(X ** 2 + Y ** 2))

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, Z, color='brown', alpha=0.9, edgecolor='none')
ax.set_title(r'Surface of $f(x, y) = \\sin(\\sqrt{x^2 + y^2})$')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('f(x, y)')
plt.show()
""",
        "1.4": """import sympy as sp

x, y = sp.symbols('x y')
line1 = sp.Line(sp.Eq(3 * x + 5 * y, 4))
line2 = sp.Line(sp.Eq(x - 5 * y, 8))
intersection = line1.intersection(line2)[0]
angle_rad = line1.angle_between(line2)
angle_deg = sp.deg(angle_rad)

print(f"Intersection point: {intersection}")
print(f"Angle between lines: {sp.nsimplify(angle_rad)} radians ({float(angle_deg):.2f}°)")
""",
        "1.5": """import sympy as sp

polygon = sp.Polygon(sp.Point(0, 0), sp.Point(5, 0), sp.Point(5, 2), sp.Point(0, 2))
point = sp.Point(5, 1)
is_inside = polygon.encloses_point(point)
on_boundary = polygon.distance(point) == 0

print(f"Polygon vertices: {polygon.vertices}")
print(f"Point {point} inside polygon: {is_inside or on_boundary}")
print(f"Point lies on boundary: {on_boundary}")

translated_vertices = [vertex.translate(3, 3) for vertex in polygon.vertices]
print("Vertices after translation by (3, 3):")
for idx, vertex in enumerate(translated_vertices, start=1):
    print(f"  V{idx}: {vertex}")
""",
        "2.1": """import numpy as np
import matplotlib.pyplot as plt

triangle = np.array([[10, 5], [-7, 4], [8, -3]], dtype=float)

def close_loop(pts):
    return np.vstack([pts, pts[0]])

fig, ax = plt.subplots(figsize=(7, 7))
ax.plot(*close_loop(triangle).T, 'k-o', label='Original ΔABC', linewidth=2)

reflection_matrix = np.array([[-1, 0], [0, 1]], dtype=float)
reflected = triangle @ reflection_matrix.T
ax.plot(*close_loop(reflected).T, 'b-s', label='Reflection about y-axis')

rotation_matrix = np.array([[0, -1], [1, 0]], dtype=float)  # 90° rotation
rotated = reflected @ rotation_matrix.T
ax.plot(*close_loop(rotated).T, 'g-^', label='Rotate 90°')

scaled = rotated * 7
ax.plot(*close_loop(scaled).T, 'r-d', label='Uniform scale by 7')

ax.set_aspect('equal')
ax.set_title('Combined transformations of ΔABC')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.grid(True, linestyle=':')
ax.legend(loc='best')
plt.show()
""",
        "2.2": """import numpy as np
import matplotlib.pyplot as plt

a = 10  # because y^2 = 4ax => 4a = 40
x_max = 50
n_points = 50
t_min = -np.sqrt(x_max / a)
t_max = np.sqrt(x_max / a)
step = (t_max - t_min) / (n_points - 1)

points = []
t = t_min
for _ in range(n_points):
    x = a * t ** 2
    y = 2 * a * t
    if 0 <= x <= x_max:
        points.append((x, y))
    t += step

points = np.array(points)

plt.figure(figsize=(8, 4))
plt.plot(points[:, 0], points[:, 1], 'm.', label='Upper branch')
plt.plot(points[:, 0], -points[:, 1], 'c.', label='Lower branch')
plt.title(r'Iterative points on $y^2 = 40x$')
plt.xlabel('x')
plt.ylabel('y')
plt.grid(True, linestyle=':')
plt.legend()
plt.show()
""",
    },
    10: {
        "1.1": """import matplotlib.pyplot as plt

years = ['2020', '2021', '2022', '2023', '2024']
matches = [50, 40, 30, 67, 45]

plt.figure(figsize=(8, 5))
bars = plt.barh(years, matches, color='blue', edgecolor='black')
plt.title('Number of Matches Played per Year')
plt.xlabel('Number of Matches')
plt.ylabel('Year')
for bar, count in zip(bars, matches):
    plt.text(count + 1, bar.get_y() + bar.get_height() / 2, str(count), va='center')
plt.tight_layout()
plt.show()
""",
        "1.2": """import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(-10, 20, 300)
y = x ** 2 - 5

plt.figure(figsize=(8, 4))
plt.plot(x, y, color='red', linestyle='-', marker='>', markevery=15, linewidth=2, label=r'$y = x^2 - 5$')
plt.title(r'Plot of $y = x^2 - 5$ on [-10, 20]')
plt.xlabel('x')
plt.ylabel('y')
plt.grid(True, linestyle=':')
plt.legend()
plt.show()
""",
        "1.3": """import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401

x = np.linspace(0, 2 * np.pi, 60)
y = np.linspace(0, 2 * np.pi, 60)
X, Y = np.meshgrid(x, y)
inside = np.clip(X ** 2 - Y ** 2, a_min=0, a_max=None)
Z = np.cos(np.sqrt(inside))

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
ax.plot_wireframe(X, Y, Z, color='green', linewidth=0.8)
ax.set_title(r'Wireframe of $f(x, y) = \\cos(\\sqrt{x^2 - y^2})$')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('f(x, y)')
plt.show()
""",
        "1.4": """import sympy as sp

polygon = sp.RegularPolygon(sp.Point(0, 0), 5, 4)
print(f"Area: {sp.nsimplify(polygon.area)}")
print(f"Perimeter: {sp.nsimplify(polygon.perimeter)}")
print("Vertices:")
for idx, vertex in enumerate(polygon.vertices, start=1):
    print(f"  V{idx}: {vertex}")
print("Angles:")
for idx, angle in enumerate(polygon.angles.values(), start=1):
    print(f"  Angle at vertex {idx}: {sp.nsimplify(angle)} radians")
""",
        "1.5": """import sympy as sp

A = sp.Point3D(2, 0, 5)
B = sp.Point3D(1, 5, 8)
theta = sp.pi  # rotation about Y-axis by π

def rotate_about_y(point: sp.Point3D) -> sp.Point3D:
    rotation_matrix = sp.Matrix([[sp.cos(theta), 0, sp.sin(theta)],
                                 [0, 1, 0],
                                 [-sp.sin(theta), 0, sp.cos(theta)]])
    rotated = rotation_matrix @ sp.Matrix(point)
    return sp.Point3D(*rotated)

A_rot = rotate_about_y(A)
B_rot = rotate_about_y(B)

print(f"Original points: A={A}, B={B}")
print(f"Rotated points about Y-axis by π: A'={A_rot}, B'={B_rot}")
""",
        "2.1": """import numpy as np
import matplotlib.pyplot as plt

triangle = np.array([[0, 0], [8, -9], [7, 4]], dtype=float)

def close_loop(pts):
    return np.vstack([pts, pts[0]])

fig, ax = plt.subplots(figsize=(7, 7))
ax.plot(*close_loop(triangle).T, 'k-o', label='Original ΔOAB', linewidth=2)

scale_matrix = np.array([[5, 0], [0, -6]], dtype=float)
scaled = triangle @ scale_matrix.T
ax.plot(*close_loop(scaled).T, 'r-s', label='Scaling (5, -6)')

reflection_matrix = np.array([[1, 0], [0, -1]], dtype=float)
reflected = triangle @ reflection_matrix.T
ax.plot(*close_loop(reflected).T, 'b-^', label='Reflection about x-axis')

theta = np.deg2rad(60)
rotation_matrix = np.array([[np.cos(theta), -np.sin(theta)],
                            [np.sin(theta),  np.cos(theta)]])
rotated = triangle @ rotation_matrix.T
ax.plot(*close_loop(rotated).T, 'g-d', label='Rotation 60°')

ax.set_aspect('equal')
ax.set_title('Transformations of Triangle OAB')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.grid(True, linestyle=':')
ax.legend(loc='best')
plt.show()
""",
        "2.2": """import numpy as np
import matplotlib.pyplot as plt

radius = 12.0
n_points = 100
delta = 2 * np.pi / n_points
x, y = radius, 0.0
points = []
c, s = np.cos(delta), np.sin(delta)

for _ in range(n_points):
    points.append((x, y))
    x, y = x * c - y * s, x * s + y * c

points = np.array(points)
plt.figure(figsize=(6, 6))
plt.plot(points[:, 0], points[:, 1], 'm-', label=r'$x^2 + y^2 = 144$')
plt.scatter(points[0, 0], points[0, 1], color='black', label='Start point')
plt.title('Iterative circle with radius 12')
plt.xlabel('x')
plt.ylabel('y')
plt.axis('equal')
plt.grid(True, linestyle=':')
plt.legend()
plt.show()
""",
    },
    9: {
        "1.1": """import numpy as np
import matplotlib.pyplot as plt

x1 = np.linspace(-10, 10, 400)
y1 = np.sin(x1 ** 2)
x2 = np.linspace(0, np.pi, 400)
y2 = np.cos(x2 ** 2)

fig, axes = plt.subplots(2, 1, figsize=(8, 8), sharex=False)
axes[0].plot(x1, y1, color='teal', linewidth=2)
axes[0].set_title(r'$f(x) = \\sin(x^2)$ on [-10, 10]')
axes[0].set_ylabel('f(x)')
axes[0].grid(True, linestyle=':')

axes[1].plot(x2, y2, color='darkorange', linewidth=2)
axes[1].set_title(r'$g(x) = \\cos(x^2)$ on [0, \\pi]')
axes[1].set_xlabel('x (radians)')
axes[1].set_ylabel('g(x)')
axes[1].grid(True, linestyle=':')

plt.tight_layout()
plt.show()
""",
        "1.2": """import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(-10, 10, 400)
y = x ** 2 + np.exp(2 * x + 5)

plt.figure(figsize=(8, 4))
plt.plot(x, y, 'r-.', linewidth=2, label=r'$y = x^2 + e^{2x+5}$')
plt.title(r'Plot of $y = x^2 + e^{2x+5}$ on [-10, 10]')
plt.xlabel('x')
plt.ylabel('y')
plt.grid(True, linestyle=':')
plt.legend()
plt.show()
""",
        "1.3": """import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401

x = np.linspace(-20, 20, 60)
y = np.linspace(-20, 20, 60)
X, Y = np.meshgrid(x, y)
Z = X ** 3 + Y ** 3

fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, Z, color='pink', alpha=0.9, edgecolor='none')
ax.set_title(r'Surface plot of $f(x, y) = x^3 + y^3$')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('f(x, y)')
plt.show()
""",
        "1.4": """import sympy as sp

square = sp.Polygon(sp.Point(0, 0), sp.Point(1, 0), sp.Point(1, 1), sp.Point(0, 1))
print(f"Area: {square.area}")
print(f"Perimeter: {square.perimeter}")
print(f"Centroid: {square.centroid}")
print("Angles of the square:")
for vertex, angle in square.angles.items():
    print(f"  At {vertex}: {sp.nsimplify(angle)} radians")
""",
        "1.5": """import sympy as sp

A = sp.Point3D(2, 3, 5)
B = sp.Point3D(-4, 7, 9)
line = sp.Line3D(A, B)

def reflect_through_xz(pt: sp.Point3D) -> sp.Point3D:
    return sp.Point3D(pt.x, -pt.y, pt.z)

A_ref = reflect_through_xz(A)
B_ref = reflect_through_xz(B)
reflected_line = sp.Line3D(A_ref, B_ref)

print(f"Original line segment: {line}")
print(f"Reflected line segment (through XZ-plane): {reflected_line}")
print(f"Reflected endpoints: A'={A_ref}, B'={B_ref}")
""",
        "2.1": """import numpy as np
import matplotlib.pyplot as plt

poly = np.array([[4, 4], [-4, 4], [-4, -4], [4, -4]], dtype=float)

def close_loop(pts: np.ndarray) -> np.ndarray:
    return np.vstack([pts, pts[0]])

def plot_poly(ax, pts, label, style):
    loop = close_loop(pts)
    ax.plot(loop[:, 0], loop[:, 1], style, linewidth=2, label=label)

fig, ax = plt.subplots(figsize=(7, 7))
plot_poly(ax, poly, 'Original ABCD', 'k-o')

shear_matrix = np.array([[1, 0], [-3, 1]], dtype=float)
sheared = poly @ shear_matrix.T
plot_poly(ax, sheared, 'Shear in y (factor -3)', 'b-s')

reflection_matrix = np.array([[1, 0], [0, -1]], dtype=float)
reflected = sheared @ reflection_matrix.T
plot_poly(ax, reflected, 'After reflection in x-axis', 'g-^')

translated = reflected + np.array([5, 8])
plot_poly(ax, translated, 'After translation (+5, +8)', 'r-d')

ax.set_aspect('equal')
ax.set_title('Combined Transformations on Polygon ABCD')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.grid(True, linestyle=':')
ax.legend(loc='best')
plt.show()
""",
        "2.2": """import numpy as np
import matplotlib.pyplot as plt

a = 9  # because y^2 = 4ax => 4a = 36
x_max = 30
n_points = 75
t_min = -np.sqrt(x_max / a)
t_max = np.sqrt(x_max / a)
step = (t_max - t_min) / (n_points - 1)

points = []
t = t_min
for _ in range(n_points):
    x = a * t ** 2
    y = 2 * a * t
    if 0 <= x <= x_max:
        points.append((x, y))
    t += step

points = np.array(points)

plt.figure(figsize=(8, 4))
plt.plot(points[:, 0], points[:, 1], 'm.', label='Upper branch')
plt.plot(points[:, 0], -points[:, 1], 'c.', label='Lower branch (symmetry)')
plt.title(r'Iterative points on $y^2 = 36x$')
plt.xlabel('x')
plt.ylabel('y')
plt.grid(True, linestyle=':')
plt.legend()
plt.show()
""",
    },
}

for slip_num, question_map in solutions.items():
    notebook_path = BASE_DIR / f'Slip_{slip_num:02d}_MATHS_Solution.ipynb'
    nb = mnu.load_notebook(notebook_path)
    pairs = {entry['id']: entry for entry in mnu.get_questions_and_codes(nb)}

    for qid, code in question_map.items():
        if qid not in pairs:
            raise KeyError(f"Question {qid} not found in slip {slip_num}")
        mnu.update_code_cell(nb, pairs[qid]['code_cell_index'], code.strip() + '\n')

    mnu.save_notebook(nb, notebook_path)
    print(f"Updated Slip {slip_num:02d}")
