#!/usr/bin/env python3
"""
Improved refactoring script for Computer Networks C files.
"""

import os
import re

def count_lines(text):
    return len(text.strip().split('\n'))

def refactor_file(filepath):
    """Refactor a single C file."""
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
        lines = f.readlines()
    
    original_count = len(lines)
    refactored = []
    i = 0
    
    while i < len(lines):
        line = lines[i]
        
        # 1. Remove SAMPLE OUTPUT sections (multiline comments with SAMPLE OUTPUT)
        if '/*' in line and 'SAMPLE OUTPUT' in line:
            # Skip until we find closing */
            while i < len(lines):
                if '*/' in lines[i]:
                    i += 1
                    break
                i += 1
            continue
        
        # 2. Skip decorative box-drawing printf lines completely
        if 'printf' in line and any(char in line for char in ['║', '╔', '╚', '╠', '╣', '═', '╝', '┐', '┘', '├', '┤', '┬', '┴', '┼', '─', '│', '┌']):
            i += 1
            continue
        
        # 3. Skip lines that are just decorative comment separators
        if re.match(r'\s*/\*\s*[=\-_*]{10,}\s*\*/', line):
            i += 1
            continue
        if re.match(r'\s*\*\s*[=\-_*]{10,}\s*\*/', line):
            i += 1
            continue
        if re.match(r'\s*/\*\s*[─═─]+\s*\*/', line):
            i += 1
            continue
        
        # 4. Clean redundant comments in function documentation
        # If next line is a comment explaining the code immediately following
        if i + 2 < len(lines):
            curr_line = line.strip()
            next_line = lines[i + 1].strip()
            next_next = lines[i + 2].strip()
            
            # Skip trivial comments that just repeat what the code does
            if curr_line.startswith('//') and (
                'print' in curr_line.lower() or
                'display' in curr_line.lower() or
                'show' in curr_line.lower() or
                'close' in curr_line.lower() or
                'set to' in curr_line.lower() or
                'initialize' in curr_line.lower()
            ):
                # Only skip if next line is code (not another comment)
                if next_line and not next_line.startswith('//') and not next_line.startswith('/*'):
                    i += 1
                    continue
        
        # 5. Skip excessive printf formatting for visual decoration
        # Lines with only decorative dashes
        if re.match(r'\s*printf\s*\(\s*"[-─]*"\s*\);\s*$', line):
            i += 1
            continue
        
        # Keep the line
        refactored.append(line)
        i += 1
    
    # Remove excessive blank lines (more than 2 consecutive)
    final_lines = []
    blank_count = 0
    for line in refactored:
        if line.strip() == '':
            blank_count += 1
            if blank_count <= 2:  # Allow max 2 blank lines
                final_lines.append(line)
        else:
            blank_count = 0
            final_lines.append(line)
    
    # Remove trailing blank lines at end
    while final_lines and final_lines[-1].strip() == '':
        final_lines.pop()
    
    content = ''.join(final_lines)
    
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    
    new_count = len(final_lines)
    return original_count, new_count

def main():
    files = [
        "Section V: Computer Networks/Slip_02/Slip_02_Q2_OptionA.c",
        "Section V: Computer Networks/Slip_02/Slip_02_Q2_OptionB.c",
        "Section V: Computer Networks/Slip_03/Slip_03_Q2_OptionA.c",
        "Section V: Computer Networks/Slip_03/Slip_03_Q2_OptionB.c",
        "Section V: Computer Networks/Slip_04/Slip_04_Q2_OptionA.c",
        "Section V: Computer Networks/Slip_04/Slip_04_Q2_OptionB.c",
        "Section V: Computer Networks/Slip_05/Slip_05_Q2_OptionA.c",
        "Section V: Computer Networks/Slip_05/Slip_05_Q2_OptionB.c",
        "Section V: Computer Networks/Slip_06/Slip_06_Q2_OptionA.c",
        "Section V: Computer Networks/Slip_06/Slip_06_Q2_OptionB.c",
        "Section V: Computer Networks/Slip_09/Slip_09_Q2_OptionA.c",
        "Section V: Computer Networks/Slip_09/Slip_09_Q2_OptionB.c",
        "Section V: Computer Networks/Slip_12/Slip_12_Q2_OptionA.c",
        "Section V: Computer Networks/Slip_12/Slip_12_Q2_OptionB.c",
        "Section V: Computer Networks/Slip_13/Slip_13_Q2_OptionA.c",
        "Section V: Computer Networks/Slip_13/Slip_13_Q2_OptionB.c",
        "Section V: Computer Networks/Slip_14/Slip_14_Q2_OptionA.c",
        "Section V: Computer Networks/Slip_14/Slip_14_Q2_OptionB.c",
        "Section V: Computer Networks/Slip_15/Slip_15_Q2_OptionA.c",
        "Section V: Computer Networks/Slip_15/Slip_15_Q2_OptionB.c",
        "Section V: Computer Networks/Slip_16/Slip_16_Q2_OptionA.c",
        "Section V: Computer Networks/Slip_16/Slip_16_Q2_OptionB.c",
        "Section V: Computer Networks/Slip_17/Slip_17_Q2_OptionA.c",
        "Section V: Computer Networks/Slip_17/Slip_17_Q2_OptionB.c",
        "Section V: Computer Networks/Slip_18/Slip_18_Q2_OptionA.c",
        "Section V: Computer Networks/Slip_18/Slip_18_Q2_OptionB.c",
        "Section V: Computer Networks/Slip_19/Slip_19_Q2_OptionA.c",
        "Section V: Computer Networks/Slip_19/Slip_19_Q2_OptionB.c",
        "Section V: Computer Networks/Slip_20/Slip_20_Q2_OptionA.c",
        "Section V: Computer Networks/Slip_20/Slip_20_Q2_OptionB.c",
    ]
    
    results = []
    failed = []
    
    for file_path in files:
        full_path = os.path.join('.', file_path)
        if not os.path.exists(full_path):
            failed.append(f"{file_path}: File not found")
            continue
        
        try:
            before, after = refactor_file(full_path)
            reduction = ((before - after) / before * 100) if before > 0 else 0
            results.append({
                'file': file_path,
                'before': before,
                'after': after,
                'reduction': reduction
            })
        except Exception as e:
            failed.append(f"{file_path}: {str(e)}")
    
    # Print results sorted by file
    print("="*80)
    print("COMPUTER NETWORKS REFACTORING RESULTS")
    print("="*80)
    
    for r in sorted(results, key=lambda x: x['file']):
        reduction = r['reduction']
        status = "✓" if reduction > 0 else "○"
        print(f"{status} {r['file']}")
        print(f"    {r['before']} → {r['after']} lines ({reduction:+.1f}%)")
    
    # Summary
    print("\n" + "="*80)
    print("SUMMARY")
    print("="*80)
    
    total_before = sum(r['before'] for r in results)
    total_after = sum(r['after'] for r in results)
    total_reduction = ((total_before - total_after) / total_before * 100) if total_before > 0 else 0
    
    print(f"Total files processed: {len(results)}")
    print(f"Total lines before: {total_before}")
    print(f"Total lines after: {total_after}")
    print(f"Overall reduction: {total_reduction:+.1f}%")
    
    if failed:
        print(f"\nFailed to process {len(failed)} files:")
        for fail in failed:
            print(f"  - {fail}")

if __name__ == '__main__':
    main()
