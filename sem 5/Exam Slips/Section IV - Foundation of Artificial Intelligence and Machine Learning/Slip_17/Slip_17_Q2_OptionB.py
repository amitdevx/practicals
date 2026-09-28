import numpy as np

def euclidean_distance(p1, p2):
    return np.sqrt(np.sum((np.array(p1) - np.array(p2)) ** 2))

point_A = [1.5, 3.2, 4.8]
point_B = [2.1, 4.0, 3.9]
dist = euclidean_distance(point_A, point_B)
print(f"=== Euclidean Distance ===")
print(f"Point A: {point_A}, Point B: {point_B}")
print(f"Distance: {dist:.4f}")
