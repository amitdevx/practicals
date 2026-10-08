import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.preprocessing import LabelEncoder

# Load dataset
df = pd.read_csv('car_evaluation.csv')

# Rename column names
df.columns = ['buying', 'maint', 'doors', 'persons', 'lug_boot', 'safety', 'class']

# Check the frequency counts of categorical variables
print("\nFrequency Counts\n")
for col in df.columns:
    print(f"\nCounts for {col}:")
    print(df[col].value_counts())

# Check for missing values
print("\nMissing Values\n")
print(df.isnull().sum())

# Drop 'class' feature to create X and let y = 'class' variable
X = df.drop('class', axis=1)
y = df['class']

# Encode all the categorical variables
X_encoded = X.apply(LabelEncoder().fit_transform)
y_encoded = LabelEncoder().fit_transform(y)

# Split the dataset as 67:33% - train:test
X_train, X_test, y_train, y_test = train_test_split(X_encoded, y_encoded, test_size=0.33, random_state=42)

# Implement the RF classifier with default parameters
rf = RandomForestClassifier(random_state=42)
rf.fit(X_train, y_train)

# Display the accuracy of the RF classifier
accuracy = rf.score(X_test, y_test)
print(f"\nAccuracy of Random Forest Classifier: {accuracy:.4f}")
