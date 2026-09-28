import os
import re

base_dir = "/home/amitdevx/Code/practicals/sem 5/Exam Slips"

def parse_cs305_table_to_html(text):
    if "Allocation" in text and "Max" in text and "Available" in text and "Process" in text:
        lines = [l.strip() for l in text.strip().split('\n') if l.strip()]
        if len(lines) < 3: return text
        
        abc_line_idx = -1
        for i, l in enumerate(lines):
            if set(l.replace(' ', '')) <= set('ABCD') and len(l.replace(' ', '')) >= 6:
                abc_line_idx = i
                break
                
        if abc_line_idx == -1: return text # fallback
        
        top_headers_line = lines[abc_line_idx-1]
        # Top headers are typically "Process", "Allocation", "Max", "Available" or "Request"
        # We know the fixed structure:
        # Process is rowspan=2
        # The others are colspan = len(resources)
        
        # Let's dynamically find it based on the number of resources in A B C line
        sub_headers = lines[abc_line_idx].split()
        num_res = len(sub_headers) // 3
        if "Request" in top_headers_line or len(sub_headers) % 3 != 0:
            num_res = len(sub_headers) // 2 if len(sub_headers) % 2 == 0 else len(sub_headers) // 3
            if num_res == 0: num_res = 3
            
        html = ["<table>"]
        
        # First row
        top_tokens = top_headers_line.split()
        html.append("  <tr>")
        html.append(f"    <th rowspan=\"2\">{top_tokens[0]}</th>")
        
        # for subsequent headers, distribute colspan
        # usually it's Allocation, Max, Available.
        for th in top_tokens[1:]:
            # Count how many subheaders belong to it based on position, or just divide evenly
            # Standard is num_res
            colspan = num_res
            # if the table is Process | Allocation | Request
            # and A B C A B C -> 2 * 3 = 6
            html.append(f"    <th colspan=\"{colspan}\">{th}</th>")
        html.append("  </tr>")
        
        # Second row
        html.append("  <tr>")
        for sh in sub_headers:
            html.append(f"    <th>{sh}</th>")
        html.append("  </tr>")
        
        # Data rows
        for l in lines[abc_line_idx+1:]:
            html.append("  <tr>")
            cols = l.split()
            for c in cols:
                html.append(f"    <td>{c}</td>")
            html.append("  </tr>")
        
        html.append("</table>\n")
        return '\n'.join(html)
    return text

def process_file(filepath):
    with open(filepath, 'r') as f:
        content = f.read()
    
    # We replace the markdown tables generated earlier back to HTML? No, wait!
    # I already converted them to markdown tables!
    # I need to re-extract from PDF to get the raw text again!
    pass

