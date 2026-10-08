import pandas as pd

student_details = pd.DataFrame({
    'Student_ID': [1, 2, 3],
    'Name': ['Alice', 'Bob', 'Charlie'],
    'Age': [20, 21, 20]
})

academic_records = pd.DataFrame({
    'Student_ID': [1, 2, 3],
    'Grade': ['A', 'B', 'A'],
    'Marks': [85, 75, 90]
})

print("Student Details:\n", student_details)
print("\nAcademic Records:\n", academic_records)

integrated_df = pd.merge(student_details, academic_records, on='Student_ID')
print("\nIntegrated DataFrame:\n", integrated_df)
