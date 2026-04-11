#!/usr/bin/env python3
"""
Refactor Computer Networks C files by removing decorative elements
and redundant comments while preserving all functional code.
"""

import os
import re
import sys
from pathlib import Path

def count_lines(text):
    return len(text.strip().split('\n'))

def refactor_file(filepath):
    """Refactor a single C file."""
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()
    
    original_lines = count_lines(content)
    
    # 1. Remove SAMPLE OUTPUT section (everything between "SAMPLE OUTPUT" and closing comment)
    content = re.sub(
        r'/\*\s*\n\s*\*\s*SAMPLE OUTPUT:.*?\*/',
        '/* */\n',
        content,
        flags=re.DOTALL
    )
    
    # 2. Remove decorative separator lines
    # Patterns: /* ==================== TEXT ==================== */
    content = re.sub(
        r'/\*\s*[=\-_*]{10,}.*?[=\-_*]{10,}\s*\*/',
        '',
        content,
        flags=re.DOTALL
    )
    
    # 3. Replace fancy box characters with simple dashes
    # Match lines with ╔, ║, ╠, ╣, ╚, ═, etc.
    content = re.sub(
        r'printf\s*\(\s*"[^"]*[╔╠╙║╚═┐┘├┤┬┴┼─│┌][^"]*"\s*(?:,\s*[^)]*?)?\s*\);',
        '',
        content,
        flags=re.MULTILINE
    )
    
    # Replace printf with box characters with simple "--- Text ---"
    def replace_box_printf(match):
        text = match.group(0)
        # Extract text between quotes
        m = re.search(r'"([^"]*)"', text)
        if m:
            extracted = m.group(1)
            # Clean up the text from box characters
            cleaned = re.sub(r'[╔╠╙║╚═┐┘├┤┬┴┼─│┌┃]+', '', extracted)
            cleaned = cleaned.strip()
            if cleaned and cleaned not in ['', '║', '║░', '║ ']:
                return f'printf("--- {cleaned} ---\\n");'
        return ''
    
    content = re.sub(
        r'printf\s*\(\s*"[^"]*[╔╠╙║╚═┐┘├┤┬┴┼─│┌][^"]*"\s*(?:,\s*[^)]*?)?\s*\);',
        replace_box_printf,
        content,
        flags=re.MULTILINE
    )
    
    # 4. Remove lines with only box-drawing characters in printf
    content = re.sub(
        r'\s*printf\s*\(\s*"[╔╠╙║╚═┐┘├┤┬┴┼─│┌\s]+"\s*\);\s*\n',
        '',
        content
    )
    
    # 5. Clean up redundant comments (comments that just repeat what code does)
    # Remove comments like "// Set x to 0" for "x = 0;"
    lines = content.split('\n')
    cleaned_lines = []
    i = 0
    while i < len(lines):
        line = lines[i]
        # Skip lines that are just decorative comments
        if re.match(r'^\s*/\*\s*[=\-_*]{5,}\s*\*/', line):
            i += 1
            continue
        # Skip certain redundant comment patterns
        if '/*' in line and '*/' in line and len(line) < 60:
            comment_text = re.search(r'/\*\s*(.+?)\s*\*/', line)
            if comment_text:
                text = comment_text.group(1).lower()
                # Remove trivial comments
                if any(x in text for x in ['print', 'display', 'show', 'close file', 'end', 'done']):
                    code_part = re.sub(r'/\*.*?\*/', '', line).strip()
                    if code_part:
                        cleaned_lines.append(code_part)
                    else:
                        i += 1
                        continue
        
        cleaned_lines.append(line)
        i += 1
    
    content = '\n'.join(cleaned_lines)
    
    # 6. Remove excessive blank lines (reduce multiple blank lines to single)
    content = re.sub(r'\n\n\n+', '\n\n', content)
    
    # 7. Clean up trailing whitespace on each line
    lines = content.split('\n')
    lines = [line.rstrip() for line in lines]
    content = '\n'.join(lines)
    
    # 8. Remove empty comment blocks
    content = re.sub(r'/\*\s*\*/\n', '', content)
    
    new_lines = count_lines(content)
    
    # Write back
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    
    return original_lines, new_lines

def main():
    # List of files to process
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
            print(f"✓ {file_path}")
            print(f"  Lines: {before} → {after} ({reduction:.1f}% reduction)")
        except Exception as e:
            failed.append(f"{file_path}: {str(e)}")
            print(f"✗ {file_path}: {str(e)}")
    
    # Summary
    print("\n" + "="*70)
    print("REFACTORING SUMMARY")
    print("="*70)
    
    total_before = sum(r['before'] for r in results)
    total_after = sum(r['after'] for r in results)
    total_reduction = ((total_before - total_after) / total_before * 100) if total_before > 0 else 0
    
    print(f"\nTotal files processed: {len(results)}")
    print(f"Total lines before: {total_before}")
    print(f"Total lines after: {total_after}")
    print(f"Overall reduction: {total_reduction:.1f}%")
    
    if failed:
        print(f"\nFailed to process {len(failed)} files:")
        for fail in failed:
            print(f"  - {fail}")

if __name__ == '__main__':
    main()
