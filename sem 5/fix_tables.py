import os
import re

base_dir = "/home/amitdevx/Code/practicals/sem 5/Exam Slips"

def parse_cs305_table(text):
    # check if it's the standard banker's table
    if "Allocation" in text and "Max" in text and "Available" in text and "Process" in text:
        # standard 4-column group table
        lines = [l.strip() for l in text.strip().split('\n') if l.strip()]
        if len(lines) < 3: return text
        # usually line 1: Process Allocation Max Available
        # line 2: A B C A B C A B C
        # line 3+: P0 2 3 2 9 7 5 3 3 2
        # sometimes there's a Request instead of Available, or 4 resources (A B C D)
        
        # We can just extract all tokens line by line
        md = []
        # find the row with A B C...
        abc_line_idx = -1
        for i, l in enumerate(lines):
            if set(l.replace(' ', '')) <= set('ABCD') and len(l.replace(' ', '')) >= 6:
                abc_line_idx = i
                break
        
        if abc_line_idx == -1:
            # Maybe just simple columns
            headers = re.split(r'\s{2,}', lines[0])
            md.append("| " + " | ".join(headers) + " |")
            md.append("|" + "|".join(["---"]*len(headers)) + "|")
            for l in lines[1:]:
                cols = re.split(r'\s{2,}', l)
                md.append("| " + " | ".join(cols) + " |")
            return '\n'.join(md)
            
        # Top headers
        top_headers = re.split(r'\s{2,}', lines[abc_line_idx-1])
        sub_headers = lines[abc_line_idx].split()
        
        # We will flatten to one header row: e.g. Process | Alloc A | Alloc B | Max A | Max B ...
        # Actually it's simpler: Just make top headers span by repeating or just put them as columns
        # Let's just create a generic table for the numbers.
        col_count = len(lines[abc_line_idx+1].split())
        md.append("| " + " | ".join(["Col"] * col_count) + " |")
        md.append("|" + "|".join(["---"] * col_count) + "|")
        for l in lines[abc_line_idx-1:]:
            cols = l.split()
            # pad to col_count
            cols += [""] * (col_count - len(cols))
            md.append("| " + " | ".join(cols) + " |")
        return '\n'.join(md)
    else:
        # Generic table
        lines = [l.strip() for l in text.strip().split('\n') if l.strip()]
        if not lines: return text
        headers = re.split(r'\s{2,}', lines[0])
        md = ["| " + " | ".join(headers) + " |"]
        md.append("|" + "|".join(["---"]*len(headers)) + "|")
        for l in lines[1:]:
            cols = re.split(r'\s{2,}', l)
            md.append("| " + " | ".join(cols) + " |")
        return '\n'.join(md)

def process_file(filepath, parser):
    with open(filepath, 'r') as f:
        content = f.read()
    
    blocks = re.split(r'(```text\n.*?\n```)', content, flags=re.DOTALL)
    for i in range(1, len(blocks), 2):
        inner_text = blocks[i][8:-4] # strip ```text\n and \n```
        # check if it contains a table
        if "Process" in inner_text or "S.No." in inner_text or "TID" in inner_text or "Pregnancies" in inner_text or "Dataset" in inner_text or "No." in inner_text or "transport" in inner_text:
            blocks[i] = parser(inner_text)
    
    with open(filepath, 'w') as f:
        f.write(''.join(blocks))

for root, dirs, files in os.walk(os.path.join(base_dir, "CS-305 Operating System")):
    for file in files:
        if file.endswith(".md"):
            process_file(os.path.join(root, file), parse_cs305_table)
            
for root, dirs, files in os.walk(os.path.join(base_dir, "CS-308 Data Science and Analytics")):
    for file in files:
        if file.endswith(".md"):
            process_file(os.path.join(root, file), parse_cs305_table)
            
for root, dirs, files in os.walk(os.path.join(base_dir, "CS-321 Foundation of AI and ML")):
    for file in files:
        if file.endswith(".md"):
            process_file(os.path.join(root, file), parse_cs305_table)

print("Tables converted.")
