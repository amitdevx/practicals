#!/usr/bin/env python3
import os
import subprocess
import re

BASE_DIR = "/home/amitdevx/Code/practicals/sem 5/Exam Slips/CS-305 Operating System"

def build_solution_md(q1_title, q1_marks, q1_stmt, q1_concept, q1_cfile, q1_out,
                      q2_title, q2_marks, q2_stmt, q2_concept, q2_cfile, q2_out,
                      viva_qas):
    lines = []
    lines.append(f"## Question 1: {q1_title} [{q1_marks} Marks]\n")
    lines.append("### Problem Statement\n" + q1_stmt.strip() + "\n")
    lines.append("### Concept & Algorithm\n" + q1_concept.strip() + "\n")
    lines.append("### Compilation & Execution\n```bash\n" + f"gcc -Wall -Wextra -o {q1_cfile[:-2]} {q1_cfile}\n./{q1_cfile[:-2]}\n```\n")
    lines.append("### Sample Output\n```text\n" + q1_out.strip() + "\n```\n")
    lines.append("---\n")
    lines.append(f"## Question 2: {q2_title} [{q2_marks} Marks]\n")
    lines.append("### Problem Statement\n" + q2_stmt.strip() + "\n")
    lines.append("### Concept & Algorithm\n" + q2_concept.strip() + "\n")
    lines.append("### Compilation & Execution\n```bash\n" + f"gcc -Wall -Wextra -o {q2_cfile[:-2]} {q2_cfile}\n./{q2_cfile[:-2]}\n```\n")
    lines.append("### Sample Output\n```text\n" + q2_out.strip() + "\n```\n")
    lines.append("---\n")
    lines.append("## Question 3: Oral / Viva Questions & Answers [5 Marks]\n")
    for i, (q, a) in enumerate(viva_qas, 1):
        lines.append(f"### Q{i}. {q}\n**Answer:** {a}\n")
    return "\n".join(lines)

print("solve_os module ready")
