import sys
import gurobipy as gp
from gurobipy import GRB

def solve():
    # Read all input at once
    raw_data = sys.stdin.read().strip()
    
    # Split the input into blocks based on the separator
    cases = raw_data.split('---')
    
    total_presses = 0
    
    for case in cases:
        # Skip empty strings that might result from splitting
        if not case.strip():
            continue
            
        # Tokenize the current block
        tokens = case.split()
        ptr = 0
        
        # Read dimensions
        try:
            m = int(tokens[ptr]); ptr += 1
            n = int(tokens[ptr]); ptr += 1
        except IndexError:
            continue # Handle potential trailing whitespace issues

        # Read Matrix A
        A = []
        for i in range(m):
            row = []
            for j in range(n):
                row.append(float(tokens[ptr]))
                ptr += 1
            A.append(row)

        # Read Vector b
        b = []
        for i in range(m):
            b.append(float(tokens[ptr]))
            ptr += 1

        # --- Gurobi Model ---
        model = gp.Model()
        model.setParam("OutputFlag", 0)

        # Define variables
        # vtype=GRB.INTEGER is crucial here. 
        # Without it, the solver might return 2.5 presses, which is impossible.
        x = model.addVars(n, lb=0.0, vtype=GRB.INTEGER, name="x")

        # Objective: Minimize sum of x
        model.setObjective(gp.quicksum(x[j] for j in range(n)), GRB.MINIMIZE)

        # Constraints: Ax = b
        for i in range(m):
            model.addConstr(
                gp.quicksum(A[i][j] * x[j] for j in range(n)) == b[i],
                name=f"row_{i}"
            )

        model.optimize()

        # Add to total if a solution exists
        if model.status == GRB.OPTIMAL:
            # Use round() to avoid floating point truncation errors (e.g. 2.9999 -> 2)
            result = int(round(model.objVal))
            total_presses += result

    print(f"Total fewest button presses: {total_presses}")

if __name__ == "__main__":
    solve()
