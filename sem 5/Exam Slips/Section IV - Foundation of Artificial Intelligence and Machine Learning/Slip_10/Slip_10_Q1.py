# Means-End Analysis (Goal-driven state operator reduction)
class MeansEndSolver:
    def __init__(self, current_state, goal_state, operators):
        self.current = set(current_state)
        self.goal = set(goal_state)
        self.operators = operators

    def solve(self):
        print("Initial State:", self.current)
        print("Goal State:   ", self.goal)
        steps = []

        while self.current != self.goal:
            diff = self.goal - self.current
            if not diff:
                break
            target_fact = next(iter(diff))
            # Find operator that yields target_fact
            chosen_op = None
            for op_name, (preconds, add_effects) in self.operators.items():
                if target_fact in add_effects:
                    chosen_op = (op_name, preconds, add_effects)
                    break

            if chosen_op:
                op_name, preconds, add_effects = chosen_op
                # Satisfy preconditions
                for p in preconds:
                    self.current.add(p)
                for a in add_effects:
                    self.current.add(a)
                steps.append(op_name)
                print(f"[Applied Operator] {op_name} -> Current State: {self.current}")
            else:
                print("[-] No operator available to resolve difference!")
                break
        return steps

operators = {
    'Drive_Car': ({'Has_Car', 'Has_Fuel'}, {'At_Destination'}),
    'Fill_Fuel': ({'Has_Money'}, {'Has_Fuel'}),
    'Earn_Money': (set(), {'Has_Money'}),
    'Buy_Car': ({'Has_Money'}, {'Has_Car'})
}

solver = MeansEndSolver(current_state={'Has_Money'}, goal_state={'At_Destination'}, operators=operators)
steps = solver.solve()
print("Solution Plan:", " -> ".join(steps))
