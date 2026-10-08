# Propositional Logic Evaluator
def evaluate_expression():
    print("\nPropositional Logic Evaluator\n")
    print("P\tQ\tNOT P\tP AND Q\tP OR Q")

    for P in [True, False]:
        for Q in [True, False]:
            not_p = not P
            p_and_q = P and Q
            p_or_q = P or Q
            print(f"{P}\t{Q}\t{not_p}\t{p_and_q}\t{p_or_q}")

if __name__ == "__main__":
    evaluate_expression()
