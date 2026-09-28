import re

def fix_md(text):
    lines = text.split('\n')
    new_lines = []
    in_pre = False
    
    for line in lines:
        if line.startswith("```"):
            in_pre = not in_pre
            new_lines.append(line)
            continue
            
        if not in_pre:
            # escape $
            line = line.replace("$", r"\$")
            # add two spaces for line break if line is not empty and doesn't already have it
            if line.strip() != "":
                line = line.rstrip() + "  "
        new_lines.append(line)
        
    return '\n'.join(new_lines)

with open('/home/amitdevx/Code/practicals/sem 5/Exam Slips/CS-305 Operating System/Slip_01/Slip_01.md', 'r') as f:
    text = f.read()

fixed = fix_md(text)
with open('test_fixed.md', 'w') as f:
    f.write(fixed)
    
