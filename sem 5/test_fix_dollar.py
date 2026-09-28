with open('/home/amitdevx/Code/practicals/sem 5/Exam Slips/CS-305 Operating System/Slip_01/Slip_01.md', 'r') as f:
    text = f.read()

# Replace \$ with &#36;
text = text.replace(r'\$', '&#36;')

with open('test_dollar.md', 'w') as f:
    f.write(text)

