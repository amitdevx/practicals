#!/usr/bin/env python3
"""
Comprehensive refactoring of Computer Networks C files
Removes decorative elements while keeping all functional code
"""
import os
import re
import sys
import subprocess

def remove_sample_output_section(content):
    """Remove SAMPLE OUTPUT comment blocks"""
    # Pattern 1: /* SAMPLE OUTPUT ... */ with newlines
    content = re.sub(
        r'/\*\s*SAMPLE\s+OUTPUT[^*]*\*/',
        '',
        content,
        flags=re.IGNORECASE | re.DOTALL
    )
    # Pattern 2: Lines containing SAMPLE OUTPUT
    lines = content.split('\n')
    result = []
    skip = False
    for line in lines:
        if 'SAMPLE OUTPUT' in line.upper():
            skip = True
            continue
        if skip:
            if '*/' in line:
                skip = False
            continue
        result.append(line)
    return '\n'.join(result)

def remove_decorative_printf(content):
    """Remove printf lines with box-drawing characters"""
    lines = content.split('\n')
    box_chars = {'╔', '║', '╚', '═', '╣', '╠', '╩', '╦', '╝', '╞', '╟', '╢', '╣'}
    result = []
    for line in lines:
        # Skip printf lines with box chars
        if 'printf' in line and any(char in line for char in box_chars):
            continue
        result.append(line)
    return '\n'.join(result)

def remove_separator_lines(content):
    """Remove decorative separator comment lines"""
    lines = content.split('\n')
    result = []
    for line in lines:
        # Skip lines that are just separators
        if re.match(r'\s*/\*\s*[=\-*\s]{10,}\s*\*/\s*$', line):
            continue
        if re.match(r'\s*//\s*[=\-*\s]{10,}\s*$', line):
            continue
        result.append(line)
    return '\n'.join(result)

def clean_excessive_blanks(content):
    """Remove excessive blank lines (keep max 2 consecutive)"""
    lines = content.split('\n')
    result = []
    blank_count = 0
    for line in lines:
        if line.strip() == '':
            blank_count += 1
            if blank_count <= 2:
                result.append(line)
        else:
            blank_count = 0
            result.append(line)
    return '\n'.join(result)

def remove_trailing_blanks(content):
    """Remove trailing blank lines"""
    lines = content.rstrip('\n').split('\n')
    # Remove all blank lines from end
    while lines and lines[-1].strip() == '':
        lines.pop()
    return '\n'.join(lines) + '\n'

def refactor_file(filepath):
    """Refactor a single C file"""
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()
    
    # Apply refactoring steps
    content = remove_sample_output_section(content)
    content = remove_decorative_printf(content)
    content = remove_separator_lines(content)
    content = clean_excessive_blanks(content)
    content = remove_trailing_blanks(content)
    
    return content

def test_compile(filepath):
    """Test if file compiles with gcc -Wall"""
    result = subprocess.run(
        ['gcc', '-Wall', filepath, '-o', '/dev/null'],
        capture_output=True,
        text=True
    )
    return result.returncode == 0, result.stderr

def main():
    slips = [4, 5, 6, 9, 12, 13, 14, 15, 16, 17, 18, 19, 20]
    base_dir = "Section V: Computer Networks"
    
    total_before = 0
    total_after = 0
    errors = []
    
    print("Refactoring Computer Networks C files...\n")
    
    for slip_num in slips:
        slip_dir = os.path.join(base_dir, f"Slip_{slip_num:02d}")
        
        for opt in ['A', 'B']:
            filename = f"Slip_{slip_num:02d}_Q2_Option{opt}.c"
            filepath = os.path.join(slip_dir, filename)
            
            if not os.path.exists(filepath):
                continue
            
            # Get original size
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                orig_content = f.read()
            orig_lines = len(orig_content.split('\n'))
            
            # Refactor
            refactored = refactor_file(filepath)
            new_lines = len(refactored.split('\n'))
            
            # Write back
            with open(filepath, 'w', encoding='utf-8') as f:
                f.write(refactored)
            
            # Test compilation
            success, error = test_compile(filepath)
            
            reduction = ((orig_lines - new_lines) / orig_lines * 100) if orig_lines > 0 else 0
            
            total_before += orig_lines
            total_after += new_lines
            
            status = "✓" if success else "✗"
            print(f"{status} Slip_{slip_num:02d}_Q2_Option{opt}: {orig_lines} → {new_lines} ({reduction:.1f}%)")
            
            if not success:
                errors.append((filename, error[:100]))
    
    print(f"\nTotal: {total_before} → {total_after} ({((total_before-total_after)/total_before*100):.1f}% reduction)")
    
    if errors:
        print("\nCompilation errors:")
        for filename, error in errors:
            print(f"  {filename}: {error}")
        return 1
    
    return 0

if __name__ == '__main__':
    sys.exit(main())
