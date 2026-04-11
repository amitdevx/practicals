#!/usr/bin/env python3
import os
import re

def refactor_c_file(filepath):
    """Aggressively refactor C file"""
    with open(filepath, 'r') as f:
        content = f.read()
    
    lines = content.split('\n')
    refactored = []
    i = 0
    in_sample = False
    in_multiline_comment = False
    skip_blanks = 0
    
    while i < len(lines):
        line = lines[i]
        
        # Track multiline comments
        if '/*' in line and '*/' not in line:
            in_multiline_comment = True
        if '*/' in line:
            in_multiline_comment = False
        
        # Skip SAMPLE OUTPUT section
        if 'SAMPLE OUTPUT' in line or 'sample output' in line.lower():
            # Skip until closing comment or 5 lines
            for _ in range(10):
                i += 1
                if i >= len(lines) or '*/' in lines[i]:
                    break
            i += 1
            skip_blanks = 2
            continue
        
        # Remove decorative printf lines
        if 'printf' in line and any(char in line for char in ['╔', '║', '╚', '═', '╣', '╠']):
            skip_blanks = 1
            i += 1
            continue
        
        # Remove separator comment lines (many equals/dashes)
        if re.match(r'\s*/\*\s*[=\-\*\s]{15,}\*/\s*$', line):
            skip_blanks = 1
            i += 1
            continue
        if re.match(r'\s*//\s*[=\-\*\s]{15,}\s*$', line):
            skip_blanks = 1
            i += 1
            continue
        
        # Handle blank lines - skip excess
        if line.strip() == '':
            skip_blanks -= 1
            if skip_blanks >= 0:
                i += 1
                continue
            skip_blanks = 0
        else:
            skip_blanks = 0
        
        refactored.append(line)
        i += 1
    
    # Remove trailing blanks
    while refactored and refactored[-1].strip() == '':
        refactored.pop()
    
    return '\n'.join(refactored) + '\n'

# Process files
slips = [2, 3, 4, 5, 6, 9, 12, 13, 14, 15, 16, 17, 18, 19, 20]
base_dir = "Section V: Computer Networks"

total_before = 0
total_after = 0

for slip_num in slips:
    slip_dir = os.path.join(base_dir, f"Slip_{slip_num:02d}")
    
    for opt in ['A', 'B']:
        filename = f"Slip_{slip_num:02d}_Q2_Option{opt}.c"
        filepath = os.path.join(slip_dir, filename)
        
        if os.path.exists(filepath):
            with open(filepath, 'r') as f:
                original = f.read()
            orig_lines = len(original.split('\n'))
            
            refactored = refactor_c_file(filepath)
            new_lines = len(refactored.split('\n'))
            
            with open(filepath, 'w') as f:
                f.write(refactored)
            
            total_before += orig_lines
            total_after += new_lines
            
            pct = ((orig_lines - new_lines) / orig_lines * 100) if orig_lines > 0 else 0
            print(f"✓ {filename}: {orig_lines} → {new_lines} ({pct:.1f}%)")

print(f"\nTotal: {total_before} → {total_after} ({((total_before-total_after)/total_before*100):.1f}% reduction)")
