Mathematics for Computer Science-II - Topic Analysis

> **Subject:** Mathematics for Computer Science-II  
> **Total Slips:** 20  
> **Question Format:** Q1 with 5 sub-questions (Attempt any 4)


# 1. Topic Overview Table

| Topic | Frequency | Percentage |
|-------|-----------|------------|
| **Pie Charts** | 8 | 40% |
| **Bar Graphs (Vertical)** | 4 | 20% |
| **Horizontal Bar Graphs** | 3 | 15% |
| **Polynomial Functions** | 10 | 50% |
| **Trigonometric Functions** | 7 | 35% |
| **Subplots** | 3 | 15% |
| **Surface Plots (3D)** | 2 | 10% |
| **Histograms** | 2 | 10% |
| **Exponential Functions** | 3 | 15% |
| **Logarithmic Functions** | 1 | 5% |
| **Line Joining Points** | 1 | 5% |


##  2.2 Function Plotting

### A. Polynomial Functions

| Function Type | Slips | Equations |
|---------------|-------|-----------|
| **Linear (degree 1)** | 4, 16 | y = 2x + 5, Line joining points |
| **Quadratic (degree 2)** | 2, 5, 6, 10, 20 | y = x + 5, y = x + 2x + 5, y = x - 5, y = x + 5x |
| **Cubic (degree 3)** | 1, 3 | y = x + 10x - 5, y = x - 3x + 2 |
| **Higher degree** | 18 | y = 2x + 6x + 10 |

**Key Concepts:**
- `np.linspace()` for x values
- Direct equation computation for y
- Line styles: solid, dashed, dotted
- Colors specification

### B. Trigonometric Functions

| Function | Slips | Equations |
|----------|-------|-----------|
| **sin(x)** | 15, 17 | y = sin(x) + cos(x), y = sin(3x + 1) |
| **cos(x)** | 8, 11, 13, 15 | y = cos(x) + sin(x), y = x + cos(2x + 5), y = cos(x) |
| **tan(x)** | 19 | y = tan(x) |
| **Combined** | 8, 15 | y = cos(x) + sin(x), y = sin(x) + cos(x) |

**Key Concepts:**
- `np.sin()`, `np.cos()`, `np.tan()`
- Radian vs degree mode
- Handling discontinuities in tan(x)

### C. Exponential Functions

| Function | Slips | Equations |
|----------|-------|-----------|
| **Simple e** | 4, 7 | y = e |
| **Composite** | 6 | y = e^(2x+4) |

**Key Concepts:**
- `np.exp()` function
- Rapid growth visualization

### D. Logarithmic Functions

| Function | Slips | Equations |
|----------|-------|-----------|
| **log(x)** | 14 | y = log(x) |

**Key Concepts:**
- `np.log()` for natural log
- Domain restrictions (x > 0)

### E. Mixed/Composite Functions

| Function | Slips | Equations |
|----------|-------|-----------|
| **Polynomial + Trig** | 11 | y = x + cos(2x + 5) |
| **Polynomial + Exp** | 9 | y = x + e^(2x+5) |


##  2.4 Plot Customization

| Feature | Usage | Slips |
|---------|-------|-------|
| **Colors** | All plots | All |
| **Dashed Lines** | Function plots | 1, multiple |
| **Dotted Lines** | Alternative styling | Various |
| **Markers** | Point highlighting | Various |
| **Labels** | Title, xlabel, ylabel | All |
| **Legend** | Multi-series plots | Subplots, overlays |


# 4. Repeated/Similar Questions

##  Group A: Pie Charts (8 slips)

| Type | Slips | Context |
|------|-------|---------|
| Basic | 2, 12 | Sports, Marks |
| With % | 13, 16, 20 | Marks, Fruits, Subjects |
| With explode | 7, 17, 19 | Expenses, Marks, Animals |

**Master Template:**
```python
import matplotlib.pyplot as plt
labels = ['A', 'B', 'C', 'D']
sizes = [15, 30, 25, 30]
explode = (0.1, 0, 0, 0)   Only for explode type
plt.pie(sizes, labels=labels, autopct='%1.1f%%', explode=explode)
plt.title('Title')
plt.show()
```

##  Group B: Bar Graphs (7 slips)

| Type | Slips |
|------|-------|
| Vertical | 1, 5, 8, 14 |
| Horizontal | 3, 10, 15 |

**Master Template:**
```python
import matplotlib.pyplot as plt
categories = ['A', 'B', 'C', 'D']
values = [25, 40, 30, 55]

 Vertical: plt.bar(categories, values, color='brown')

 Horizontal: plt.barh(categories, values, color='blue')
plt.xlabel('X Label')
plt.ylabel('Y Label')
plt.title('Title')
plt.show()
```

##  Group C: Polynomial Plots (10 slips)

| Degree | Slips | Common Form |
|--------|-------|-------------|
| Linear | 4 | y = ax + b |
| Quadratic | 2, 5, 6, 10, 18, 20 | y = ax + bx + c |
| Cubic | 1, 3 | y = ax + bx + c |

**Master Template:**
```python
import numpy as np
import matplotlib.pyplot as plt
x = np.linspace(-10, 10, 100)
y = x**2 + 5   Modify equation as needed
plt.plot(x, y, 'r--', label='y = x + 5')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Polynomial Plot')
plt.legend()
plt.grid(True)
plt.show()
```

##  Group D: Trigonometric Plots (7 slips)

| Function | Slips |
|----------|-------|
| sin-based | 15, 17 |
| cos-based | 8, 11, 13, 15 |
| tan | 19 |

**Master Template:**
```python
import numpy as np
import matplotlib.pyplot as plt
x = np.linspace(-2*np.pi, 2*np.pi, 100)
y = np.sin(x) + np.cos(x)   Modify as needed
plt.plot(x, y, 'b-', label='y = sin(x) + cos(x)')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Trigonometric Plot')
plt.legend()
plt.grid(True)
plt.show()
```

##  Group E: Subplots (3 slips)

| Slip | Functions |
|------|-----------|
| 4 | x and e |
| 6 | x and e^(2x+4) |
| 9 | sin(x) and cos(x) |

**Master Template:**
```python
import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(-5, 5, 100)

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))

ax1.plot(x, x**3, 'r-')
ax1.set_title('y = x')
ax1.grid(True)

ax2.plot(x, np.exp(x), 'b-')
ax2.set_title('y = e')
ax2.grid(True)

plt.tight_layout()
plt.show()
```

##  Group F: Surface Plots (2 slips)

| Slip | Function |
|------|----------|
| 1 | z = x + y |
| 14 | z = x + y |

**Master Template:**
```python
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

x = np.linspace(-10, 10, 50)
y = np.linspace(-10, 10, 50)
X, Y = np.meshgrid(x, y)
Z = X**2 + Y**2   Modify as needed

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, Y, Z, cmap='pink')
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
plt.title('Surface Plot')
plt.show()
```


# 6. Study Priority Guide

##  Priority 1: HIGH FREQUENCY (Must Know)

| Rank | Topic | Frequency | Slips |
|------|-------|-----------|-------|
| 1 | **Pie Charts** | 8 slips (40%) | 2, 7, 12, 13, 16, 17, 19, 20 |
| 2 | **Polynomial Plotting** | 10 slips (50%) | 1-6, 10, 18, 20 |
| 3 | **Bar Graphs (All types)** | 7 slips (35%) | 1, 3, 5, 8, 10, 14, 15 |

##  Priority 2: MEDIUM FREQUENCY (Should Know)

| Rank | Topic | Frequency | Slips |
|------|-------|-----------|-------|
| 4 | **Trigonometric Functions** | 7 slips (35%) | 8, 11, 13, 15, 17, 19 |
| 5 | **Subplots** | 3 slips (15%) | 4, 6, 9 |
| 6 | **Exponential Functions** | 3 slips (15%) | 4, 6, 7 |

##  Priority 3: LOW FREQUENCY (Good to Know)

| Rank | Topic | Frequency | Slips |
|------|-------|-----------|-------|
| 7 | **Histograms** | 2 slips (10%) | 11, 18 |
| 8 | **Surface Plots (3D)** | 2 slips (10%) | 1, 14 |
| 9 | **Logarithmic Functions** | 1 slip (5%) | 14 |
| 10 | **Line Joining Points** | 1 slip (5%) | 16 |


#  Statistics Summary

| Metric | Value |
|--------|-------|
| Total Slips | 20 |
| Questions per Slip | 5 (attempt 4) |
| Data Visualization Questions | ~20 |
| Function Plotting Questions | ~20 |
| Most Common: Pie Charts | 8 slips (40%) |
| Most Common: Polynomials | 10 slips (50%) |
| 3D Plots | 2 slips (10%) |
