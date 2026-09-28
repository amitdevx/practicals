import os
import re
import subprocess
import shutil

base_dir = "/home/amitdevx/Code/practicals/sem 5/Exam Slips"

images_321 = {
    1: [(0, "OR"), (1, "Viva")],
    2: [(2, "OR")],
    3: [(3, "OR"), (4, "Viva")],
    4: [(5, "OR")],
    5: [(6, "OR")],
    6: [(7, "OR")],
    7: [(8, "OR"), (9, "Viva")],
    14: [(10, "OR")],
    15: [(11, "OR")],
    16: [(12, "OR")],
    17: [(13, "OR")],
    18: [(14, "OR")],
    21: [(15, "OR"), (16, "Viva")],
    23: [(17, "OR")],
    24: [(18, "OR")],
    25: [(19, "OR"), (20, "Viva")]
}
ext_map_321 = {8: "ppm"}

images_306 = {
    1: [(0, "Q3")],
    2: [(1, "Q3")]
}

def parse_table_html(text):
    if "Allocation" in text and "Max" in text and "Process" in text:
        lines = [l.strip() for l in text.strip().split('\n') if l.strip()]
        abc_line_idx = -1
        for i, l in enumerate(lines):
            if set(l.replace(' ', '')) <= set('ABCD') and len(l.replace(' ', '')) >= 6:
                abc_line_idx = i
                break
        if abc_line_idx == -1:
            return "\n```text\n" + text + "\n```\n"
        
        top_tokens = lines[abc_line_idx-1].split()
        sub_headers = lines[abc_line_idx].split()
        num_res = len(sub_headers) // (len(top_tokens) - 1)
        if num_res == 0: num_res = 3
        
        html = ["<table border='1'>"]
        html.append("  <tr>")
        html.append(f"    <th rowspan=\"2\">{top_tokens[0]}</th>")
        for th in top_tokens[1:]:
            html.append(f"    <th colspan=\"{num_res}\">{th}</th>")
        html.append("  </tr>")
        html.append("  <tr>")
        for sh in sub_headers:
            html.append(f"    <th>{sh}</th>")
        html.append("  </tr>")
        
        for l in lines[abc_line_idx+1:]:
            html.append("  <tr>")
            for c in l.split():
                html.append(f"    <td>{c}</td>")
            html.append("  </tr>")
        html.append("</table>\n")
        return '\n'.join(html)
    
    # Generic table
    if "S.No." in text or "TID" in text or "Pregnancies" in text or "transport" in text or "No." in text or "Dataset" in text:
        lines = [l.strip() for l in text.strip().split('\n') if l.strip()]
        if not lines: return text
        headers = re.split(r'\s{2,}', lines[0])
        md = ["| " + " | ".join(headers) + " |"]
        md.append("|" + "|".join(["---"]*len(headers)) + "|")
        for l in lines[1:]:
            cols = re.split(r'\s{2,}', l)
            md.append("| " + " | ".join(cols) + " |")
        return '\n'.join(md)
        
    return "\n```text\n" + text + "\n```\n"

def process_page(p, pdf_path, subject, slip_num):
    pdf_text = subprocess.run(["pdftotext", "-layout", "-f", str(p), "-l", str(p), pdf_path, "-"], capture_output=True, text=True).stdout
    lines = pdf_text.split('\n')
    md_lines = []
    
    in_pre = False
    
    for line in lines:
        stripped = line.strip()
        if re.match(r'^(Q\.?\s*\d+|Q\d+)', stripped, re.IGNORECASE):
            if in_pre:
                md_lines.append("```\n")
                in_pre = False
            md_lines.append(f"### {stripped}")
            continue
            
        if re.search(r'\S\s{3,}\S', line) and len(stripped) > 0 and not "Duration" in line:
            if not in_pre:
                md_lines.append("\n```text")
                in_pre = True
            md_lines.append(line)
        else:
            if in_pre and not stripped:
                md_lines.append(line)
            elif in_pre and stripped:
                md_lines.append("```\n")
                in_pre = False
                md_lines.append(stripped)
            else:
                md_lines.append(stripped)
    if in_pre:
        md_lines.append("```\n")
        
    content = '\n'.join(md_lines)
    
    # Convert code blocks to tables
    blocks = re.split(r'(```text\n.*?\n```)', content, flags=re.DOTALL)
    for i in range(1, len(blocks), 2):
        inner_text = blocks[i][8:-4]
        blocks[i] = parse_table_html(inner_text)
    
    content = ''.join(blocks)
    
    # Final cleanup line by line
    final_lines = []
    for line in content.split('\n'):
        if not line.startswith("<") and not line.startswith("|") and not line.startswith("```"):
            line = re.sub(r'(?<!\\)\$', r'\$', line)
            if line.strip() != "":
                line = line.rstrip() + "  "
        final_lines.append(line)
        
    content = '\n'.join(final_lines)
    
    # Insert images
    if subject == "CS-321":
        if slip_num in images_321:
            for img_info in images_321[slip_num]:
                idx, marker = img_info
                ext = ext_map_321.get(idx, "jpg")
                img_str = f"\n![Image](../../../images/CS-321-{idx:03d}.{ext})\n"
                
                # split content at marker
                parts = content.split(marker, 1)
                if len(parts) > 1:
                    content = parts[0] + img_str + marker + parts[1]
                else:
                    content += img_str
                    
    if subject == "CS-306":
        if slip_num in images_306:
            for img_info in images_306[slip_num]:
                idx, marker = img_info
                ext = "jpg"
                img_str = f"\n![Image](../../../images/CS-306-{idx:03d}.{ext})\n"
                
                parts = content.split(marker, 1)
                if len(parts) > 1:
                    content = parts[0] + img_str + marker + parts[1]
                else:
                    content += img_str

    return content

subjects = [
    {"id": "CS-305", "dir": "CS-305 Operating System", "pdf": "CS-305 Operating SystemT.Y.B.Sc(CS)Slips 26-27.pdf", "skip": 0},
    {"id": "CS-306", "dir": "CS-306 Core Java and Web Technology", "pdf": "CS-306 Core Java and Web Technology_I TYBSc(CS) Slips 26-27.pdf", "skip": 0},
    {"id": "CS-308", "dir": "CS-308 Data Science and Analytics", "pdf": "CS-308 Data Science and Anallytics TYBSc(CS) Slips 26-27.pdf", "skip": 2},
    {"id": "CS-321", "dir": "CS-321 Foundation of AI and ML", "pdf": "CS-321-VSC-P_Foundation of Artificial Intelligence(AI) and Machine Learning_Slip2026_2027.pdf", "skip": 0}
]

for sub in subjects:
    pdf_path = os.path.join(base_dir, "_references", sub["pdf"])
    sub_dir = os.path.join(base_dir, sub["dir"])
    
    if not os.path.exists(pdf_path): continue

    res = subprocess.run(["pdfinfo", pdf_path], capture_output=True, text=True)
    pages = 0
    for line in res.stdout.split('\n'):
        if line.startswith("Pages:"):
            pages = int(line.split(":")[1].strip())
            
    for p in range(sub["skip"] + 1, pages + 1):
        slip_num = p - sub["skip"]
        slip_dir = os.path.join(sub_dir, f"Slip_{slip_num:02d}")
        md_path = os.path.join(slip_dir, f"Slip_{slip_num:02d}.md")
        
        md_content = process_page(p, pdf_path, sub["id"], slip_num)
        
        with open(md_path, 'w', encoding='utf-8') as f:
            f.write(md_content)

print("Perfect MD generated.")
