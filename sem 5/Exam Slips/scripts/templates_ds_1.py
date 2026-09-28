# Data Science & Analytics Templates (Slips 1 to 10)

def get_ds_slip01():
    q1 = '''import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

data = {
    'Price': [250, 300, 150, 800, 220, 1200, 280, 310, 190, 260],
    'Rating': [4.2, 4.5, 3.8, 4.9, 4.0, 4.8, 4.3, 4.1, 3.9, 4.4],
    'Number_of_Sales': [1200, 1500, 800, 3000, 1100, 4500, 1300, 1400, 950, 1250]
}

df = pd.DataFrame(data)
print("--- Products Dataset ---")
print(df)

# Boxplots for outlier detection
plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
sns.boxplot(y=df['Price'], color='skyblue')
plt.title('Boxplot of Price (Outlier Detection)')

plt.subplot(1, 2, 2)
sns.boxplot(y=df['Rating'], color='lightgreen')
plt.title('Boxplot of Rating')
plt.tight_layout()
plt.savefig('ds_slip_01_q1_boxplot.png')
print("[+] Plot saved as ds_slip_01_q1_boxplot.png")
'''

    q2 = '''import pandas as pd
import numpy as np

# Create Loan_Application dataset
data = {
    'Application_ID': [f'APP{i:03d}' for i in range(1, 11)],
    'Age': [25, 32, 45, 52, 28, 36, 41, 29, 60, 33],
    'Income': [35000, 55000, 90000, 120000, 42000, 68000, 85000, 38000, 110000, 58000],
    'Credit_Score': [650, 720, 780, 810, 600, 740, 770, 630, 800, 710],
    'Loan_Amount': [200000, 400000, 800000, 1500000, 250000, 500000, 750000, 300000, 1200000, 450000],
    'Approval_Status': ['Approved', 'Approved', 'Approved', 'Approved', 'Rejected', 'Approved', 'Approved', 'Rejected', 'Approved', 'Approved']
}

df = pd.DataFrame(data)
df.to_csv('Loan_application.csv', index=False)
print("--- Loan Application Dataset ---")
print(df.head())
print("\\nSummary Statistics:")
print(df.describe())
'''

    q2_or = '''import pandas as pd
from sklearn.datasets import load_iris
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, accuracy_score

iris = load_iris()
X = iris.data
y = iris.target

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

model = LogisticRegression(max_iter=200)
model.fit(X_train, y_train)

y_pred = model.predict(X_test)
print("=== Logistic Regression on Iris Dataset ===")
print("Accuracy:", accuracy_score(y_test, y_pred))
print("\\nClassification Report:\\n", classification_report(y_test, y_pred, target_names=iris.target_names))
'''
    return q1, q2, q2_or

def get_ds_slip02():
    q1 = '''import matplotlib.pyplot as plt

subjects = ['Mathematics', 'Operating Systems', 'Data Science', 'Core Java', 'Artificial Intelligence']
marks = [85, 78, 92, 88, 80]

plt.figure(figsize=(8, 5))
bars = plt.bar(subjects, marks, color=['#3498db', '#e74c3c', '#2ecc71', '#f39c12', '#9b59b6'])
plt.title('Student Examination Marks Across Subjects', fontsize=14, fontweight='bold')
plt.xlabel('Subjects', fontsize=12)
plt.ylabel('Marks (Out of 100)', fontsize=12)
plt.ylim(0, 100)

for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width()/2.0, yval + 1.5, f'{yval}', ha='center', va='bottom', fontweight='bold')

plt.tight_layout()
plt.savefig('ds_slip_02_q1_barchart.png')
print("[+] Bar chart saved as ds_slip_02_q1_barchart.png")
'''

    q2 = '''import numpy as np
import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, r2_score

# YouTube Dataset: Views, Likes, Comments -> Revenue/Engagement
np.random.seed(42)
n = 100
views = np.random.randint(1000, 500000, n)
likes = (views * np.random.uniform(0.04, 0.08)).astype(int)
comments = (views * np.random.uniform(0.005, 0.015)).astype(int)
revenue = views * 0.002 + likes * 0.01 + np.random.normal(0, 20, n)

df = pd.DataFrame({'Views': views, 'Likes': likes, 'Comments': comments, 'Revenue': revenue})

X = df[['Views', 'Likes', 'Comments']]
y = df['Revenue']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

model = LinearRegression()
model.fit(X_train, y_train)

y_pred = model.predict(X_test)
print("=== YouTube Multiple Linear Regression ===")
print("R2 Score:", r2_score(y_test, y_pred))
print("MSE:", mean_squared_error(y_test, y_pred))
'''

    q2_or = '''import pandas as pd
from itertools import combinations

# Apriori Market Basket Analysis on Video Dataset
dataset = {
    'TID': [1, 2, 3, 4, 5],
    'Items': [
        ['Python Tutorial', 'Data Science', 'Machine Learning'],
        ['Data Science', 'Machine Learning'],
        ['Python Tutorial', 'Web Development'],
        ['Python Tutorial', 'Data Science', 'Deep Learning'],
        ['Machine Learning', 'Deep Learning']
    ]
}

df = pd.DataFrame(dataset)
print("--- Learning Video Transactions ---")
print(df)

min_support = 0.4
total_tx = len(df)

# Frequency count of single items
item_counts = {}
for items in df['Items']:
    for item in items:
        item_counts[item] = item_counts.get(item, 0) + 1

frequent_1 = {k: v/total_tx for k, v in item_counts.items() if (v/total_tx) >= min_support}
print(f"\\nFrequent 1-Itemsets (min_support >= {min_support}):")
for k, v in frequent_1.items():
    print(f"{{{k}}}: Support = {v:.2f}")
'''
    return q1, q2, q2_or

def get_ds_slip03():
    q1 = '''import pandas as pd
import numpy as np
from scipy.cluster.hierarchy import dendrogram, linkage
import matplotlib.pyplot as plt

data = {
    'Product': ['P1', 'P2', 'P3', 'P4', 'P5'],
    'Price': [250, 270, 800, 850, 290],
    'Rating': [4.1, 4.2, 4.8, 4.9, 4.0],
    'Sales': [1200, 1300, 3500, 3600, 1150]
}
df = pd.DataFrame(data)
features = df[['Price', 'Rating', 'Sales']]

# Generate Dendrogram
Z = linkage(features, method='ward')
plt.figure(figsize=(8, 5))
dendrogram(Z, labels=df['Product'].values)
plt.title('Hierarchical Clustering Dendrogram of Products')
plt.xlabel('Product')
plt.ylabel('Distance')
plt.tight_layout()
plt.savefig('ds_slip_03_q1_dendrogram.png')
print("[+] Dendrogram saved as ds_slip_03_q1_dendrogram.png")
'''

    q2 = '''import numpy as np
import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import r2_score

data = {
    'Years_Experience': [1.1, 1.3, 1.5, 2.0, 2.2, 2.9, 3.0, 3.2, 3.9, 4.0, 4.5, 5.1],
    'Salary': [39343, 46205, 37731, 43525, 39891, 56642, 60150, 54445, 63218, 55794, 61111, 67938]
}
df = pd.DataFrame(data)

X = df[['Years_Experience']]
y = df['Salary']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=42)

model = LinearRegression()
model.fit(X_train, y_train)

y_pred = model.predict(X_test)
print("=== Salary Prediction (Linear Regression) ===")
print("Slope (Coefficient):", model.coef_[0])
print("Intercept:", model.intercept_)
print("R2 Score:", r2_score(y_test, y_pred))
'''

    q2_or = '''import pandas as pd
from sklearn.datasets import load_wine
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, classification_report

wine = load_wine()
X, y = wine.data, wine.target

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

rf = RandomForestClassifier(n_estimators=50, random_state=42)
rf.fit(X_train, y_train)

preds = rf.predict(X_test)
print("=== Random Forest Classifier on Wine Dataset ===")
print("Accuracy:", accuracy_score(y_test, preds))
'''
    return q1, q2, q2_or

def get_ds_slip04():
    q1 = '''import matplotlib.pyplot as plt

payment_methods = ['Credit Card', 'UPI / NetBanking', 'Cash on Delivery', 'Debit Card', 'Digital Wallet']
counts = [350, 820, 210, 180, 140]

plt.figure(figsize=(7, 7))
plt.pie(counts, labels=payment_methods, autopct='%1.1f%%', startangle=140, colors=['#3498db', '#2ecc71', '#e74c3c', '#f1c40f', '#9b59b6'])
plt.title('Customer Preferred Payment Methods', fontsize=14, fontweight='bold')
plt.tight_layout()
plt.savefig('ds_slip_04_q1_piechart.png')
print("[+] Pie chart saved as ds_slip_04_q1_piechart.png")
'''

    q2 = '''import numpy as np
import pandas as pd
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

# Online Food Delivery dataset simulation
np.random.seed(42)
n = 150
order_value = np.random.randint(150, 1500, n)
delivery_time = np.random.randint(15, 60, n)
discount = np.random.randint(0, 50, n)
# 1 = Repeat Customer, 0 = Non-repeat
repeat = (order_value * 0.001 - delivery_time * 0.02 + discount * 0.05 > 0.5).astype(int)

df = pd.DataFrame({'Order_Value': order_value, 'Delivery_Time': delivery_time, 'Discount': discount, 'Repeat_Customer': repeat})

X = df[['Order_Value', 'Delivery_Time', 'Discount']]
y = df['Repeat_Customer']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=42)
model = LogisticRegression()
model.fit(X_train, y_train)

preds = model.predict(X_test)
print("=== Online Food Delivery Logistic Regression ===")
print("Model Accuracy:", accuracy_score(y_test, preds))
'''

    q2_or = '''import pandas as pd
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt

# Mall Customer dataset simulation
data = {
    'Annual_Income': [15, 16, 17, 18, 19, 60, 62, 64, 65, 90, 95, 100],
    'Spending_Score': [39, 81, 6, 77, 40, 48, 55, 42, 59, 15, 85, 20]
}
df = pd.DataFrame(data)

kmeans = KMeans(n_clusters=3, random_state=42, n_init='auto')
df['Cluster'] = kmeans.fit_predict(df[['Annual_Income', 'Spending_Score']])

print("=== Customer Segmentation using K-Means ===")
print(df)
'''
    return q1, q2, q2_or

def get_ds_slip05():
    q1 = '''import pandas as pd
import matplotlib.pyplot as plt

sales_data = {
    'Month': ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun'],
    'Sales_Units': [1200, 1350, 1100, 1600, 1850, 2100]
}
df = pd.DataFrame(sales_data)

plt.figure(figsize=(8, 4.5))
plt.plot(df['Month'], df['Sales_Units'], marker='o', color='#2980b9', linewidth=2.5, markersize=7)
plt.title('Monthly Sales Trend', fontsize=14, fontweight='bold')
plt.xlabel('Month', fontsize=12)
plt.ylabel('Sales (Units)', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.6)
plt.tight_layout()
plt.savefig('ds_slip_05_q1_linechart.png')
print("[+] Line chart saved as ds_slip_05_q1_linechart.png")
'''

    q2 = '''import matplotlib.pyplot as plt
import matplotlib.patches as patches

# Venn diagram / Overlap of Netflix and Amazon Prime users
fig, ax = plt.subplots(figsize=(7, 5))
circle1 = plt.Circle((0.4, 0.5), 0.3, color='#e50914', alpha=0.5, label='Netflix Users (450)')
circle2 = plt.Circle((0.6, 0.5), 0.3, color='#00a8e1', alpha=0.5, label='Amazon Prime Users (300)')

ax.add_patch(circle1)
ax.add_patch(circle2)
ax.set_xlim(0, 1)
ax.set_ylim(0, 1)
ax.set_aspect('equal')
plt.text(0.28, 0.5, "Netflix Only\\n300", fontsize=11, fontweight='bold', color='white', ha='center')
plt.text(0.5, 0.5, "Both\\n150", fontsize=11, fontweight='bold', color='black', ha='center')
plt.text(0.72, 0.5, "Prime Only\\n150", fontsize=11, fontweight='bold', color='white', ha='center')
plt.title('Subscriber Distribution (Netflix vs Amazon Prime)', fontsize=14, fontweight='bold')
plt.axis('off')
plt.legend(loc='lower center')
plt.tight_layout()
plt.savefig('ds_slip_05_q2_streaming.png')
print("[+] Native Venn overlap chart saved as ds_slip_05_q2_streaming.png")
'''

    q2_or = '''import pandas as pd
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

data = {
    'Attendance': [85, 70, 95, 60, 75, 90, 50, 65, 88, 78],
    'Marks': [82, 65, 90, 55, 72, 88, 45, 60, 85, 74],
    'Grade': ['A', 'B', 'A', 'C', 'B', 'A', 'C', 'C', 'A', 'B']
}
df = pd.DataFrame(data)

X = df[['Attendance', 'Marks']]
y = df['Grade']

knn = KNeighborsClassifier(n_neighbors=3)
knn.fit(X, y)

test_student = [[80, 75]]
pred = knn.predict(test_student)
print("=== KNN Student Grade Classifier ===")
print(f"Predicted Grade for Attendance=80, Marks=75: {pred[0]}")
'''
    return q1, q2, q2_or
