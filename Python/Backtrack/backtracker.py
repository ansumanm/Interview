"""
A generic backtracking function
"""

def solve(values, safe_up_to, size):
    """Finds a solution to a backtracking problem.

    values     -- a sequence of values to try, in order. For a map coloring
                  problem, this may be a list of colors, such as ['red',
                  'green', 'yellow', 'purple']
    safe_up_to -- a function with two arguments, solution and position, that
                  returns whether the values assigned to slots 0..pos in
                  the solution list, satisfy the problem constraints.
    size       -- the total number of “slots” you are trying to fill

    Return the solution as a list of values.
    """
    solution = [None] * size

    def extend_solution(position):
        for value in values:
            solution[position] = value
            if safe_up_to(solution, position):
                if position >= size-1 or extend_solution(position+1):
                    return solution
        return None

    return extend_solution(0)

def solve_iterative(highest_value, safe_up_to, num_slots):
    """Finds a solution to a backtracking problem.

    highest_value -- the largest value to try. Values for the slots will be in
                     the range 0..highest_value, inclusive.
    safe_up_to    -- a function with two arguments, solution and position, that
                     returns whether the values assigned to slots 0..position
                     in the solution list, satisfy the problem constraints.
    num_slots     -- the total number of “slots” you are trying to fill

    Return the solution as a list of values.
    """
    solution = [None] * num_slots

    def solve_from(position):
        while True:
            if safe_up_to(solution, position):
                if position >= num_slots-1:
                    # We filled the last slot and everything is okay
                    return solution
                position += 1
                solution[position] = 0
            else:
                # Backtrack. We might have to undo several slots, so....
                while (solution[position] == highest_value-1):
                    solution[position] = None
                    position -= 1
                if position < 0:
                    break
                solution[position] += 1

        # We backtracked beyond the starting point, meaning we could not find
        # a valid value for the first slot, so no solution
        return None

    # With the iterative solution, I think you have to begin by priming the
    # solution list with the first value in the first slot.
    solution[0] = 0
    return solve_from(0)
