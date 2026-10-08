def objective(x):
    # F(x) = -x^2 + 4x
    return -x**2 + 4*x

def hill_climbing(start_x, step_size=0.1, max_iter=100):
    current_x = start_x
    current_val = objective(current_x)

    for i in range(max_iter):
        next_left = current_x - step_size
        next_right = current_x + step_size
        val_left = objective(next_left)
        val_right = objective(next_right)

        if val_right > current_val and val_right >= val_left:
            current_x, current_val = next_right, val_right
        elif val_left > current_val:
            current_x, current_val = next_left, val_left
        else:
            break # Local maximum reached
    return current_x, current_val

opt_x, opt_val = hill_climbing(start_x=0.0)
print("\nHill Climbing Algorithm\n")
print("Objective Function: F(x) = -x^2 + 4x")
print(f"Maximum found at x = {opt_x:.4f} with value F(x) = {opt_val:.4f}")
