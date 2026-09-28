import re

def convert_to_md(text):
    lines = text.split('\n')
    md_lines = []
    in_table = False
    
    for i, line in enumerate(lines):
        # very simple heuristic: if a line has multiple instances of 2+ spaces, it might be a table
        # but only if it's not just indented text.
        stripped = line.strip()
        if not stripped:
            md_lines.append("")
            in_table = False
            continue
            
        # Check if line has multiple space-separated columns
        # We split by 2 or more spaces
        parts = re.split(r'\s{2,}', line.strip())
        if len(parts) > 1 and not line.startswith(' ' * 15): 
            # might be a table row
            if not in_table:
                # start of table
                in_table = True
                md_lines.append("| " + " | ".join(parts) + " |")
                md_lines.append("|" + "|".join(["---"] * len(parts)) + "|")
            else:
                md_lines.append("| " + " | ".join(parts) + " |")
        else:
            in_table = False
            md_lines.append(line.strip())
            
    return '\n'.join(md_lines)

with open('test.md', 'w') as f:
    text = """                 Process        Allocation            Max            Available
                              A      B     C     A    B       C     A     B    C
                   P0         2      3     2     9     7      5     3     3    2
                   P1         4      0     0     5     2      2
"""
    f.write(convert_to_md(text))

