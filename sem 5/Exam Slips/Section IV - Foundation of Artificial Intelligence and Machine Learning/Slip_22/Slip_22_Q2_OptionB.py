# Rule-Based Expert System for Medical Diagnosis
def expert_system_diagnose(symptoms):
    rules = [
        ({'fever', 'cough', 'fatigue'}, "Common Viral Flu"),
        ({'fever', 'shivering', 'headache'}, "Malaria"),
        ({'cough', 'shortness_of_breath', 'chest_pain'}, "Respiratory Infection"),
        ({'sneezing', 'runny_nose', 'sore_throat'}, "Allergic Rhinitis")
    ]

    diagnoses = []
    for symptom_set, disease in rules:
        if symptom_set.issubset(symptoms):
            diagnoses.append(disease)

    return diagnoses if diagnoses else ["General Fatigue / Consultation Required"]

patient_symptoms = {'fever', 'cough', 'fatigue'}
print("=== Rule-Based Expert System ===")
print("Patient Symptoms:", patient_symptoms)
print("Diagnosis:", expert_system_diagnose(patient_symptoms))
