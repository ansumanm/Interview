import backtracker

def no_conflicts(board, up_to_column):
    # See if any queens in columns to the left of up_to_column interfere with
    # the queen in up_to_column. Return False as soon as you find one that does.
    for col in range(up_to_column):
        if (board[col] == board[up_to_column]                           # same row
            or board[col] == board[up_to_column] + up_to_column - col   # diagonal
            or board[col] == board[up_to_column] + col - up_to_column): # diagonal
            return False
    return True

print(backtracker.solve(range(8), no_conflicts, 8))
