def objective_function(x):
    return -x**2 + 4*x

def hill_climbing(start_x, step_size=0.1, max_iters=100):
    current_x = start_x
    for _ in range(max_iters):
        neighbors = [current_x - step_size, current_x + step_size]
        best_neighbor = max(neighbors, key=objective_function)
        if objective_function(best_neighbor) <= objective_function(current_x):
            break
        current_x = best_neighbor
    return current_x

res = hill_climbing(0)
print("\nHill Climbing Algorithm for -x^2 + 4x\n")
print(f"Maximum found at x = {res:.2f}, f(x) = {objective_function(res):.2f}")
