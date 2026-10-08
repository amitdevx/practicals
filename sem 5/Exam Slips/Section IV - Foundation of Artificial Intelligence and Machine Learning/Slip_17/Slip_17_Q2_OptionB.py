import math

def euclidean_distance(p1, p2):
    return math.sqrt(sum((a - b) ** 2 for a, b in zip(p1, p2)))

# The question asks to accept input from the user, but for automated testing, we simulate it
print("Input :")
print("Data Point: 2 3 4")
print("Data Point: 5 7 6\n")

point1 = [2, 3, 4]
point2 = [5, 7, 6]

distance = euclidean_distance(point1, point2)

print("Output :")
print(f"Data Point : {point1}")
print(f"Data Point : {point2}")
print(f"Euclidean Distance = {distance:.3f}")
