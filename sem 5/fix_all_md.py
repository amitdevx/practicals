import os
import re

base_dir = "/home/amitdevx/Code/practicals/sem 5/Exam Slips"
subjects = [
    "CS-305 Operating System",
    "CS-306 Core Java and Web Technology",
    "CS-308 Data Science and Analytics",
    "CS-321 Foundation of AI and ML"
]

for sub in subjects:
    sub_dir = os.path.join(base_dir, sub)
    for root, dirs, files in os.walk(sub_dir):
        for file in files:
            if file.endswith(".md"):
                filepath = os.path.join(root, file)
                with open(filepath, "r", encoding="utf-8") as f:
                    content = f.read()
                
                lines = content.split('\n')
                new_lines = []
                in_pre = False
                
                for line in lines:
                    if line.startswith("```"):
                        in_pre = not in_pre
                        new_lines.append(line)
                        continue
                    
                    if not in_pre:
                        # escape $
                        line = re.sub(r'(?<!\\)\$', r'\$', line)
                        # Add double spaces for line break
                        if line.strip() != "":
                            line = line.rstrip() + "  "
                    
                    new_lines.append(line)
                
                with open(filepath, "w", encoding="utf-8") as f:
                    f.write('\n'.join(new_lines))

print("All MD files fixed.")
