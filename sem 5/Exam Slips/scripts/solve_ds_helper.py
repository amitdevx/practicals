#!/usr/bin/env python3
import os
import subprocess

PYTHON_BIN = "/home/amitdevx/py-env/bin/python"
BASE_DIR = "/home/amitdevx/Code/practicals/sem 5/Exam Slips/CS-308 Data Science and Analytics"

def build_solution_md(q1_title, q1_marks, q1_stmt, q1_concept, q1_file, q1_out,
                      q2_title, q2_marks, q2_stmt, q2_concept, q2_file, q2_out,
                      q2_or_title, q2_or_stmt, q2_or_concept, q2_or_file, q2_or_out,
                      viva_qas):
    lines = []
    lines.append(f"## Question 1: {q1_title} [{q1_marks} Marks]\n")
    lines.append("### Problem Statement\n" + q1_stmt.strip() + "\n")
    lines.append("### Concept & Methodology\n" + q1_concept.strip() + "\n")
    lines.append("### Execution\n```bash\n" + f"python3 {q1_file}\n```\n")
    lines.append("### Output Preview\n```text\n" + q1_out.strip() + "\n```\n")
    lines.append("---\n")
    lines.append(f"## Question 2: {q2_title} [{q2_marks} Marks]\n")
    lines.append("### Problem Statement\n" + q2_stmt.strip() + "\n")
    lines.append("### Concept & Machine Learning Algorithm\n" + q2_concept.strip() + "\n")
    lines.append("### Execution\n```bash\n" + f"python3 {q2_file}\n```\n")
    lines.append("### Output Preview\n```text\n" + q2_out.strip() + "\n```\n")
    if q2_or_file:
        lines.append("---\n")
        lines.append(f"#### OR\n\n## Question 2 (Alternative): {q2_or_title} [{q2_marks} Marks]\n")
        lines.append("### Problem Statement\n" + q2_or_stmt.strip() + "\n")
        lines.append("### Concept & Algorithm\n" + q2_or_concept.strip() + "\n")
        lines.append("### Execution\n```bash\n" + f"python3 {q2_or_file}\n```\n")
        lines.append("### Output Preview\n```text\n" + q2_or_out.strip() + "\n```\n")
    lines.append("---\n")
    lines.append("## Question 3: Oral / Viva Questions & Answers [5 Marks]\n")
    for i, (q, a) in enumerate(viva_qas, 1):
        lines.append(f"### Q{i}. {q}\n**Answer:** {a}\n")
    return "\n".join(lines)

def solve_ds_slip(slip_num, q1_info, q2_info, q2_or_info, viva_qas):
    folder = os.path.join(BASE_DIR, f"ds_slip_{slip_num:02d}")
    os.makedirs(folder, exist_ok=True)

    q1_file = f"ds_slip_{slip_num:02d}_q1.py"
    q2_file = f"ds_slip_{slip_num:02d}_q2.py"
    q2_or_file = f"ds_slip_{slip_num:02d}_q2_or.py" if q2_or_info else None

    # Write files
    with open(os.path.join(folder, q1_file), "w") as f:
        f.write(q1_info["code"])

    with open(os.path.join(folder, q2_file), "w") as f:
        f.write(q2_info["code"])

    if q2_or_info:
        with open(os.path.join(folder, q2_or_file), "w") as f:
            f.write(q2_or_info["code"])

    # Write Solution MD
    sol_md = build_solution_md(
        q1_info["title"], 10, q1_info["stmt"], q1_info["concept"], q1_file, q1_info["out"],
        q2_info["title"], 20, q2_info["stmt"], q2_info["concept"], q2_file, q2_info["out"],
        q2_or_info["title"] if q2_or_info else "",
        q2_or_info["stmt"] if q2_or_info else "",
        q2_or_info["concept"] if q2_or_info else "",
        q2_or_file,
        q2_or_info["out"] if q2_or_info else "",
        viva_qas
    )
    with open(os.path.join(folder, f"ds_slip_{slip_num:02d}_solution.md"), "w") as f:
        f.write(sol_md)

    # Test run scripts with python
    for py_f in [q1_file, q2_file] + ([q2_or_file] if q2_or_file else []):
        full_p = os.path.join(folder, py_f)
        res = subprocess.run([PYTHON_BIN, full_p], cwd=folder, capture_output=True, text=True)
        if res.returncode != 0:
            print(f"[-] Error in {py_f}:", res.stderr)

    print(f"  -> Solved and verified ds_slip_{slip_num:02d}")
