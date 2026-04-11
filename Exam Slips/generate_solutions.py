#!/usr/bin/env python3
import re
import os

# Read the full text
with open('/tmp/cn_slips_full.txt', 'r', encoding='utf-8', errors='ignore') as f:
    lines = f.readlines()

# Join back to text
full_text = ''.join(lines)

# Split by "Slip N" at the end of sections
slip_pattern = r'Slip\s+(\d+)\n+(.*?)(?=Slip\s+\d+\n|$)'
slip_matches = list(re.finditer(slip_pattern, full_text, re.DOTALL))

print(f"Found {len(slip_matches)} slips")

for match in slip_matches:
    slip_num = int(match.group(1))
    slip_content = match.group(2)
    
    if 1 <= slip_num <= 5:  # Print first 5 for verification
        print(f"\n{'='*70}")
        print(f"SLIP {slip_num}")
        print(f"{'='*70}")
        
        # Extract Q1 section
        q1_match = re.search(r'Q1\)(.*?)(?=Q2\)|\[)', slip_content, re.DOTALL)
        if q1_match:
            q1_text = q1_match.group(1)
            # Extract individual questions
            questions = re.findall(r'^([a-g])\)\s*(.+?)(?=^[a-g]\)|^[Q]|^B|^A|$)', q1_text, re.MULTILINE | re.DOTALL)
            print(f"\nQ1 Questions found: {len(questions)}")
            for qchar, qtext in questions[:3]:
                print(f"  {qchar}) {qtext.strip()[:80]}...")
        
        # Extract Q2 options
        q2_matches = re.findall(r'(?:OR\s+)?Q2\)\s*([^a-g]*?)(?=Q2\)|Q3\)|$)', slip_content, re.DOTALL)
        print(f"\nQ2 Options found: {len(q2_matches)}")
        for i, opt in enumerate(q2_matches[:3]):
            print(f"  Option {i+1}: {opt.strip()[:80]}...")

