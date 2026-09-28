import matplotlib.pyplot as plt

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
