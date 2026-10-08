import pandas as pd
from sklearn.ensemble import ExtraTreesClassifier
from sklearn.decomposition import PCA

data = {
    'Application_ID': [f'APP{i:03d}' for i in range(1, 11)],
    'Age': [25, 32, 45, 52, 28, 36, 41, 29, 60, 33],
    'Income': [35000, 55000, 90000, 120000, 42000, 68000, 85000, 38000, 110000, 58000],
    'Credit_Score': [650, 720, 780, 810, 600, 740, 770, 630, 800, 710],
    'Loan_Amount': [20000, 40000, 80000, 150000, 25000, 50000, 75000, 30000, 120000, 45000],
    'Employment_Years': [2, 5, 10, 15, 3, 7, 8, 4, 20, 6],
    'Debt_Ratio': [0.4, 0.3, 0.2, 0.1, 0.5, 0.35, 0.25, 0.45, 0.15, 0.3],
    'Loan_Status': ['Approved', 'Approved', 'Approved', 'Approved', 'Rejected', 'Approved', 'Approved', 'Rejected', 'Approved', 'Approved']
}
df = pd.DataFrame(data)
df.to_csv('Loan_application.csv', index=False)

X = df.drop(['Application_ID', 'Loan_Status'], axis=1)
y = df['Loan_Status']

model = ExtraTreesClassifier(random_state=42)
model.fit(X, y)
print("Feature Importances:\n", pd.Series(model.feature_importances_, index=X.columns))

pca = PCA(n_components=2)
X_pca = pca.fit_transform(X)
print("\nPCA Transformed Data:\n", pd.DataFrame(X_pca, columns=['PC1', 'PC2']).head())
