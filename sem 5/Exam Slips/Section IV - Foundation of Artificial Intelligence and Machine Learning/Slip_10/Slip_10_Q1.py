# Means-End Analysis (Goal-driven state operator reduction)

def apply_operator(op_name, preconds, add_effects, state, operators, plan):
    for p in preconds:
        if p not in state:
            print(f"Subgoal needed: {p}")
            solve_goal(p, state, operators, plan)
    
    print(f"[Applied Operator] {op_name}")
    state.update(add_effects)
    plan.append(op_name)

def solve_goal(goal, state, operators, plan):
    if goal in state:
        return True
    
    for op_name, (preconds, add_effects) in operators.items():
        if goal in add_effects:
            apply_operator(op_name, preconds, add_effects, state, operators, plan)
            return True
            
    print(f"[-] No operator available to resolve {goal}!")
    return False

def solve_mea(initial_state, goal_state, operators):
    state = set(initial_state)
    plan = []
    print("Initial State:", state)
    print("Goal State:   ", goal_state)
    
    for g in goal_state:
        solve_goal(g, state, operators, plan)
        
    print("Current State:", state)
    return plan

operators = {
    'Drive_Car': ({'Has_Car', 'Has_Fuel'}, {'At_Destination'}),
    'Fill_Fuel': ({'Has_Money'}, {'Has_Fuel'}),
    'Earn_Money': (set(), {'Has_Money'}),
    'Buy_Car': ({'Has_Money'}, {'Has_Car'})
}

if __name__ == "__main__":
    plan = solve_mea(initial_state={'Has_Money'}, goal_state={'At_Destination'}, operators=operators)
    print("Solution Plan:", " -> ".join(plan))
