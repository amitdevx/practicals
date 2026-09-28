def is_safe(board, row, col, n):
    # Check column
    for i in range(row):
        if board[i] == col or abs(board[i] - col) == abs(i - row):
            return False
    return True

def solve_n_queens(n, row=0, board=None, solutions=None):
    if board is None: board = [-1] * n
    if solutions is None: solutions = []

    if row == n:
        solutions.append(list(board))
        return

    for col in range(n):
        if is_safe(board, row, col, n):
            board[row] = col
            solve_n_queens(n, row + 1, board, solutions)
            board[row] = -1
    return solutions

n = 4
sols = solve_n_queens(n)
print(f"=== N-Queens Backtracking Problem (N = {n}) ===")
print(f"Total Solutions Found: {len(sols)}")
for i, sol in enumerate(sols, 1):
    print(f"\nSolution {i}: (Row positions of queens per column: {sol})")
    for r in range(n):
        line = ["Q" if sol[r] == c else "." for c in range(n)]
        print(" ".join(line))
