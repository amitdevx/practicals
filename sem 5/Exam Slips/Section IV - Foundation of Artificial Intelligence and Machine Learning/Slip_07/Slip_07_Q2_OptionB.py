import math

board = [' ' for _ in range(9)]

def print_board():
    for row in [board[i*3:(i+1)*3] for i in range(3)]:
        print('| ' + ' | '.join(row) + ' |')

def is_winner(b, l):
    return ((b[0] == l and b[1] == l and b[2] == l) or
            (b[3] == l and b[4] == l and b[5] == l) or
            (b[6] == l and b[7] == l and b[8] == l) or
            (b[0] == l and b[3] == l and b[6] == l) or
            (b[1] == l and b[4] == l and b[7] == l) or
            (b[2] == l and b[5] == l and b[8] == l) or
            (b[0] == l and b[4] == l and b[8] == l) or
            (b[2] == l and b[4] == l and b[6] == l))

def get_empty_cells(b):
    return [i for i, x in enumerate(b) if x == ' ']

def minimax(b, depth, is_max):
    if is_winner(b, 'O'): return 1
    if is_winner(b, 'X'): return -1
    if not get_empty_cells(b): return 0

    if is_max:
        best = -math.inf
        for i in get_empty_cells(b):
            b[i] = 'O'
            best = max(best, minimax(b, depth + 1, not is_max))
            b[i] = ' '
        return best
    else:
        best = math.inf
        for i in get_empty_cells(b):
            b[i] = 'X'
            best = min(best, minimax(b, depth + 1, not is_max))
            b[i] = ' '
        return best

def best_move():
    best_score = -math.inf
    move = -1
    for i in get_empty_cells(board):
        board[i] = 'O'
        score = minimax(board, 0, False)
        board[i] = ' '
        if score > best_score:
            best_score = score
            move = i
    return move

def play():
    print("\nTic-Tac-Toe Minimax\n")
    print_board()
    moves = [4, 0, 8] # Simulated human moves
    for m in moves:
        if board[m] == ' ':
            board[m] = 'X'
            print(f"\nHuman plays X at {m}")
            if is_winner(board, 'X'):
                print("Human wins!")
                return
            if not get_empty_cells(board):
                print("Draw!")
                return
            
            comp_move = best_move()
            board[comp_move] = 'O'
            print(f"Computer plays O at {comp_move}")
            print_board()
            if is_winner(board, 'O'):
                print("Computer wins!")
                return
            if not get_empty_cells(board):
                print("Draw!")
                return

if __name__ == '__main__':
    play()
