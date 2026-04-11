import re

# Read the file
with open('/tmp/cn_slips_full.txt', 'r', encoding='utf-8', errors='ignore') as f:
    content = f.read()

# Split by "Slip" sections
slip_pattern = r'Slip\s+(\d+)\s*\n(.*?)(?=Slip\s+\d+\s*\n|$)'
slips = re.findall(slip_pattern, content, re.DOTALL)

for slip_num, slip_content in slips[:5]:  # Print first 5 for verification
    print(f"\n{'='*60}")
    print(f"SLIP {slip_num}")
    print(f"{'='*60}")
    print(slip_content[:500])
