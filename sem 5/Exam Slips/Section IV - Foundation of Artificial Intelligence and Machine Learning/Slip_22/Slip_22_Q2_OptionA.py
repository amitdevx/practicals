def is_safe(board, row, col, n):
    for i in range(row):
        if board[i] == col or abs(board[i] - col) == abs(i - row):
            return False
    return True

def solve_n_queens(board, row, n, solutions):
    if row == n:
        solutions.append(board[:])
        return
    for col in range(n):
        if is_safe(board, row, col, n):
            board[row] = col
            solve_n_queens(board, row + 1, n, solutions)

solutions = []
solve_n_queens([-1]*4, 0, 4, solutions)
print("\nN-Queens (Backtracking)\n")
print("Found", len(solutions), "solutions for 4-Queens.")
print(solutions)
