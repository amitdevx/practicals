def implies(p, q):
    return (not p) or q

def evaluate_expression(p, q):
    print(f"P: {p}, Q: {q}")
    print(f"P AND Q: {p and q}")
    print(f"P OR Q: {p or q}")
    print(f"P IMPLIES Q: {implies(p, q)}")

print("\nPropositional Logic Evaluation\n")
evaluate_expression(True, True)
evaluate_expression(True, False)
evaluate_expression(False, True)
evaluate_expression(False, False)
