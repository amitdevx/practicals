import pandas as pd
from sklearn.decomposition import PCA
from sklearn.ensemble import ExtraTreesClassifier

df = pd.DataFrame({
    'Application_ID': range(1, 11),
    'Age': [25, 35, 45, 20, 30, 50, 40, 22, 38, 48],
    'Income': [40000, 60000, 80000, 30000, 50000, 90000, 70000, 35000, 65000, 85000],
    'Credit_Score': [600, 700, 750, 500, 650, 800, 720, 550, 680, 780],
    'Loan_Amount': [10000, 20000, 30000, 5000, 15000, 40000, 25000, 8000, 18000, 35000],
    'Employment_Years': [2, 5, 10, 1, 4, 15, 8, 1, 6, 12],
    'Debt_Ratio': [0.4, 0.3, 0.2, 0.5, 0.35, 0.15, 0.25, 0.45, 0.3, 0.2],
    'Loan_Status': [0, 1, 1, 0, 1, 1, 1, 0, 1, 1] # 0 = Rejected, 1 = Approved
})
df.to_csv('Loan_application.csv', index=False)

df = pd.read_csv('Loan_application.csv')
X = df.drop(['Application_ID', 'Loan_Status'], axis=1)
y = df['Loan_Status']

# Feature Selection
model = ExtraTreesClassifier(random_state=42)
model.fit(X, y)
print("Feature Importances:", dict(zip(X.columns, model.feature_importances_)))

# Feature Extraction (PCA)
pca = PCA(n_components=2)
X_pca = pca.fit_transform(X)
print("\nPCA Variance Ratio:", pca.explained_variance_ratio_)
print("Transformed Shape:", X_pca.shape)
