# Propositional Logic Truth Table Evaluator
def evaluate_expression():
    print("=== Propositional Logic Truth Table ===")
    print("P\tQ\tP AND Q\tP OR Q\tP -> Q\tP <-> Q")
    print("---------------------------------------------------------")

    for P in [True, False]:
        for Q in [True, False]:
            p_and_q = P and Q
            p_or_q = P or Q
            p_implies_q = (not P) or Q
            p_iff_q = P == Q
            print(f"{P}\t{Q}\t{p_and_q}\t{p_or_q}\t{p_implies_q}\t{p_iff_q}")

evaluate_expression()
