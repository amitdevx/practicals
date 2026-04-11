#!/usr/bin/env python3
import re
import os

# Read the full text
with open('/tmp/cn_slips_full.txt', 'r', encoding='utf-8', errors='ignore') as f:
    full_text = f.read()

# Split by "Slip N" pattern
slip_blocks = re.split(r'(?=Slip\s+\d+)', full_text)

slips_data = {}

for block in slip_blocks:
    # Extract slip number
    slip_match = re.match(r'Slip\s+(\d+)', block)
    if not slip_match:
        continue
    
    slip_num = int(slip_match.group(1))
    
    # Extract Q1 section - between "Q1)" and "Q2)" or "B"
    q1_match = re.search(r'Q1\)(.*?)(?=Q2\)|OR)', block, re.DOTALL)
    if q1_match:
        q1_text = q1_match.group(1).strip()
    else:
        q1_text = ""
    
    # Extract Q2 section - get the text after Q2)
    q2_match = re.search(r'Q2\)(.*?)(?=Q3\)|$)', block, re.DOTALL)
    if q2_match:
        q2_text = q2_match.group(1).strip()
    else:
        q2_text = ""
    
    slips_data[slip_num] = {
        'q1': q1_text,
        'q2': q2_text,
        'raw': block
    }
    
    if slip_num <= 3:  # Print for debugging
        print(f"\n{'='*70}")
        print(f"SLIP {slip_num} - Q1 SECTION:")
        print(f"{'='*70}")
        print(q1_text[:400])
        print(f"\n{'='*70}")
        print(f"SLIP {slip_num} - Q2 SECTION:")
        print(f"{'='*70}")
        print(q2_text[:400])

# Save to file for reference
import json
with open('/home/amitdevx/jupyter_notebook/sem4/Exam Slips/slips_extracted.json', 'w') as f:
    # Convert to serializable format
    json_data = {}
    for k, v in slips_data.items():
        json_data[str(k)] = {'q1': v['q1'][:1000], 'q2': v['q2'][:1000]}
    json.dump(json_data, f, indent=2)

print(f"\n\nTotal slips found: {len(slips_data)}")
print(f"Slips: {sorted(slips_data.keys())}")

