from collections import deque

def solve_water_jug(capA, capB, target):
    visited = set()
    queue = deque([(0, 0, [])]) # (jugA, jugB, path)

    while queue:
        a, b, path = queue.popleft()
        if a == target or b == target:
            return path + [(a, b)]

        if (a, b) in visited:
            continue
        visited.add((a, b))

        # Possible operations:
        moves = [
            (capA, b, "Fill Jug A"),
            (a, capB, "Fill Jug B"),
            (0, b, "Empty Jug A"),
            (a, 0, "Empty Jug B"),
            (a - min(a, capB - b), b + min(a, capB - b), "Pour A into B"),
            (a + min(b, capA - a), b - min(b, capA - a), "Pour B into A")
        ]

        for na, nb, action in moves:
            if (na, nb) not in visited:
                queue.append((na, nb, path + [(a, b)]))
    return None

capA, capB, target = 4, 3, 2
solution = solve_water_jug(capA, capB, target)
print(f"=== Water Jug Problem ({capA}L, {capB}L -> Target {target}L) ===")
for step, (a, b) in enumerate(solution):
    print(f"Step {step}: Jug A = {a}L, Jug B = {b}L")
