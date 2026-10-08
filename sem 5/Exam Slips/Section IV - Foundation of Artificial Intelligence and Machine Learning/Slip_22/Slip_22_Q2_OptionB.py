def expert_system(symptoms):
    if "fever" in symptoms and "cough" in symptoms:
        return "You might have the flu."
    elif "fever" in symptoms:
        return "You might have a cold."
    return "Symptoms unclear."

print("\nRule-Based Expert System\n")
print("Symptoms: fever, cough ->", expert_system(["fever", "cough"]))
