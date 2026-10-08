import pandas as pd
from sklearn.ensemble import RandomForestClassifier

data = {
    'Study_Hours': [2, 3, 4, 5, 6, 7, 1, 2, 5, 8],
    'Attendance': [60, 65, 70, 75, 80, 85, 55, 62, 78, 90],
    'Assignment_Score': [55, 60, 65, 70, 75, 80, 50, 58, 72, 85],
    'Result': ['Fail', 'Fail', 'Pass', 'Pass', 'Pass', 'Pass', 'Fail', 'Fail', 'Pass', 'Pass']
}
df = pd.DataFrame(data)

X = df[['Study_Hours', 'Attendance', 'Assignment_Score']]
y = df['Result']

rf = RandomForestClassifier(n_estimators=10, random_state=42)
rf.fit(X, y)

pred = rf.predict([[6, 80, 75]])
print("\nRandom Forest Classifier\n")
print("Prediction for [Study:6h, Attend:80%, Score:75]:", pred[0])
