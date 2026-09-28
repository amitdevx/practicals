#!/usr/bin/env python3
"""
migrate_to_sem4_structure.py
Migrates all 110 slips across 4 subjects to the exact Semester IV directory structure:
Section I - Operating System-I (30 slips)
Section II - Core Java and Web Technology-I (30 slips)
Section III - Data Science and Analytics (25 slips)
Section IV - Foundation of Artificial Intelligence and Machine Learning (25 slips)
"""

import os
import shutil
import re
import subprocess

BASE_DIR = "/home/amitdevx/Code/practicals/sem 5/Exam Slips"

def sanitize_md_header(content, title):
    # Remove any existing top H1 header or redundant banner
    # And start with: # title
    content = content.strip()
    if content.startswith("# "):
        # Replace the first line
        lines = content.splitlines()
        content = "\n".join(lines[1:]).strip()
    
    # Check if there is an old banner block like Practical Examination — Sem V
    content = re.sub(r"^\*\*Practical Examination — Sem V.*?\n---\n", "", content, flags=re.DOTALL)
    # Also remove Index of Files in this Folder table if present
    content = re.sub(r"## Index of Files in this Folder.*?\n---\n", "", content, flags=re.DOTALL)

    return f"# {title}\n\n" + content.strip() + "\n"

def migrate_os():
    src_dir = os.path.join(BASE_DIR, "CS-305 Operating System")
    dst_section = os.path.join(BASE_DIR, "Section I - Operating System-I")
    os.makedirs(dst_section, exist_ok=True)
    print(">>> Migrating Section I - Operating System-I...")

    for slip_num in range(1, 31):
        s_src = os.path.join(src_dir, f"os_slip_{slip_num:02d}")
        s_dst = os.path.join(dst_section, f"Slip_{slip_num:02d}")
        os.makedirs(s_dst, exist_ok=True)

        # 1. PDF
        pdf_src = os.path.join(s_src, f"os_slip_{slip_num:02d}.pdf")
        pdf_dst = os.path.join(s_dst, f"Slip_{slip_num:02d}_OS_SOLUTION.pdf")
        if os.path.exists(pdf_src):
            shutil.copy2(pdf_src, pdf_dst)

        # 2. C files
        q1_c_src = os.path.join(s_src, f"os_slip_{slip_num:02d}_q1.c")
        q1_c_dst = os.path.join(s_dst, f"Slip_{slip_num:02d}_Q1.c")
        if os.path.exists(q1_c_src):
            shutil.copy2(q1_c_src, q1_c_dst)

        q2_c_src = os.path.join(s_src, f"os_slip_{slip_num:02d}_q2.c")
        q2_c_dst = os.path.join(s_dst, f"Slip_{slip_num:02d}_Q2.c")
        if os.path.exists(q2_c_src):
            shutil.copy2(q2_c_src, q2_c_dst)

        # 3. Solution MD
        sol_src = os.path.join(s_src, f"os_slip_{slip_num:02d}_solution.md")
        sol_dst = os.path.join(s_dst, f"Slip_{slip_num:02d}_OS_SOLUTION.md")
        if os.path.exists(sol_src):
            with open(sol_src, "r", encoding="utf-8") as f:
                c = f.read()
            # Replace file references
            c = c.replace(f"os_slip_{slip_num:02d}_q1.c", f"Slip_{slip_num:02d}_Q1.c")
            c = c.replace(f"os_slip_{slip_num:02d}_q2.c", f"Slip_{slip_num:02d}_Q2.c")
            c = c.replace(f"os_slip_{slip_num:02d}_q1", f"Slip_{slip_num:02d}_Q1")
            c = c.replace(f"os_slip_{slip_num:02d}_q2", f"Slip_{slip_num:02d}_Q2")
            c = c.replace(f"os_slip_{slip_num:02d}.pdf", f"Slip_{slip_num:02d}_OS_SOLUTION.pdf")
            c = sanitize_md_header(c, f"Slip {slip_num:02d} — Operating System-I Solution Guide")
            with open(sol_dst, "w", encoding="utf-8") as f:
                f.write(c)

    print("✓ Section I migration complete.")

def migrate_java():
    src_dir = os.path.join(BASE_DIR, "CS-306 Core Java and Web Technology")
    dst_section = os.path.join(BASE_DIR, "Section II - Core Java and Web Technology-I")
    os.makedirs(dst_section, exist_ok=True)
    print(">>> Migrating Section II - Core Java and Web Technology-I...")

    for slip_num in range(1, 31):
        s_src = os.path.join(src_dir, f"java_slip_{slip_num:02d}")
        s_dst = os.path.join(dst_section, f"Slip_{slip_num:02d}")
        os.makedirs(s_dst, exist_ok=True)

        # 1. PDF
        pdf_src = os.path.join(s_src, f"java_slip_{slip_num:02d}.pdf")
        pdf_dst = os.path.join(s_dst, f"Slip_{slip_num:02d}_JAVA_WEB_SOLUTION.pdf")
        if os.path.exists(pdf_src):
            shutil.copy2(pdf_src, pdf_dst)

        # 2. Java file
        jfiles = [f for f in os.listdir(s_src) if f.endswith(".java")]
        old_jname = jfiles[0] if jfiles else None
        target_jname = f"Slip_{slip_num:02d}_Q1.java"
        target_class = f"Slip_{slip_num:02d}_Q1"

        if old_jname:
            j_src = os.path.join(s_src, old_jname)
            j_dst = os.path.join(s_dst, target_jname)
            with open(j_src, "r", encoding="utf-8") as f:
                jcode = f.read()

            # Find public class
            m = re.search(r"public\s+class\s+(\w+)", jcode)
            if m:
                old_pub_class = m.group(1)
                # Replace public class <old> with public class Slip_XX_Q1
                jcode = re.sub(rf"public\s+class\s+{old_pub_class}\b", f"public class {target_class}", jcode)
                # Replace constructor <old>() if it exists
                jcode = re.sub(rf"\b{old_pub_class}\s*\(", f"{target_class}(", jcode)

            with open(j_dst, "w", encoding="utf-8") as f:
                f.write(jcode)

        # 3. Web file (HTML or JS)
        web_target_name = None
        for wf in os.listdir(s_src):
            if wf.endswith(".html"):
                web_target_name = f"Slip_{slip_num:02d}_Q2.html"
                shutil.copy2(os.path.join(s_src, wf), os.path.join(s_dst, web_target_name))
            elif wf.endswith(".js"):
                web_target_name = f"Slip_{slip_num:02d}_Q2.js"
                shutil.copy2(os.path.join(s_src, wf), os.path.join(s_dst, web_target_name))

        # 4. Solution MD
        sol_src = os.path.join(s_src, f"java_slip_{slip_num:02d}_solution.md")
        sol_dst = os.path.join(s_dst, f"Slip_{slip_num:02d}_JAVA_WEB_SOLUTION.md")
        if os.path.exists(sol_src):
            with open(sol_src, "r", encoding="utf-8") as f:
                c = f.read()
            if old_jname:
                c = c.replace(old_jname, target_jname)
                # Also replace `java <OldClass>` with `java Slip_XX_Q1`
                old_class_name = old_jname.replace(".java", "")
                c = c.replace(f"java {old_class_name}", f"java {target_class}")
                c = c.replace(f"javac {old_jname}", f"javac {target_jname}")
            c = c.replace(f"java_slip_{slip_num:02d}_q2.html", f"Slip_{slip_num:02d}_Q2.html")
            c = c.replace(f"java_slip_{slip_num:02d}_q2.js", f"Slip_{slip_num:02d}_Q2.js")
            c = c.replace(f"java_slip_{slip_num:02d}.pdf", f"Slip_{slip_num:02d}_JAVA_WEB_SOLUTION.pdf")
            c = sanitize_md_header(c, f"Slip {slip_num:02d} — Core Java and Web Technology-I Solution Guide")
            with open(sol_dst, "w", encoding="utf-8") as f:
                f.write(c)

    print("✓ Section II migration complete.")

def migrate_ds():
    src_dir = os.path.join(BASE_DIR, "CS-308 Data Science and Analytics")
    dst_section = os.path.join(BASE_DIR, "Section III - Data Science and Analytics")
    os.makedirs(dst_section, exist_ok=True)
    print(">>> Migrating Section III - Data Science and Analytics...")

    for slip_num in range(1, 26):
        s_src = os.path.join(src_dir, f"ds_slip_{slip_num:02d}")
        s_dst = os.path.join(dst_section, f"Slip_{slip_num:02d}")
        os.makedirs(s_dst, exist_ok=True)

        # 1. PDF
        pdf_src = os.path.join(s_src, f"ds_slip_{slip_num:02d}.pdf")
        pdf_dst = os.path.join(s_dst, f"Slip_{slip_num:02d}_DS_SOLUTION.pdf")
        if os.path.exists(pdf_src):
            shutil.copy2(pdf_src, pdf_dst)

        # 2. Python files
        q1_src = os.path.join(s_src, f"ds_slip_{slip_num:02d}_q1.py")
        q1_dst = os.path.join(s_dst, f"Slip_{slip_num:02d}_Q1.py")
        if os.path.exists(q1_src):
            shutil.copy2(q1_src, q1_dst)

        q2_src = os.path.join(s_src, f"ds_slip_{slip_num:02d}_q2.py")
        q2_or_src = os.path.join(s_src, f"ds_slip_{slip_num:02d}_q2_or.py")

        has_or = os.path.exists(q2_or_src)
        if has_or:
            q2_dst_a = os.path.join(s_dst, f"Slip_{slip_num:02d}_Q2_OptionA.py")
            q2_dst_b = os.path.join(s_dst, f"Slip_{slip_num:02d}_Q2_OptionB.py")
            if os.path.exists(q2_src):
                shutil.copy2(q2_src, q2_dst_a)
            shutil.copy2(q2_or_src, q2_dst_b)
        else:
            q2_dst = os.path.join(s_dst, f"Slip_{slip_num:02d}_Q2.py")
            if os.path.exists(q2_src):
                shutil.copy2(q2_src, q2_dst)

        # Datasets / images if present
        for f in os.listdir(s_src):
            if f.endswith(".csv") or f.endswith(".txt") or f.endswith(".png"):
                shutil.copy2(os.path.join(s_src, f), os.path.join(s_dst, f))

        # 3. Solution MD
        sol_src = os.path.join(s_src, f"ds_slip_{slip_num:02d}_solution.md")
        sol_dst = os.path.join(s_dst, f"Slip_{slip_num:02d}_DS_SOLUTION.md")
        if os.path.exists(sol_src):
            with open(sol_src, "r", encoding="utf-8") as f:
                c = f.read()
            c = c.replace(f"ds_slip_{slip_num:02d}_q1.py", f"Slip_{slip_num:02d}_Q1.py")
            if has_or:
                c = c.replace(f"ds_slip_{slip_num:02d}_q2.py", f"Slip_{slip_num:02d}_Q2_OptionA.py")
                c = c.replace(f"ds_slip_{slip_num:02d}_q2_or.py", f"Slip_{slip_num:02d}_Q2_OptionB.py")
            else:
                c = c.replace(f"ds_slip_{slip_num:02d}_q2.py", f"Slip_{slip_num:02d}_Q2.py")
            c = c.replace(f"ds_slip_{slip_num:02d}.pdf", f"Slip_{slip_num:02d}_DS_SOLUTION.pdf")
            c = sanitize_md_header(c, f"Slip {slip_num:02d} — Data Science and Analytics Solution Guide")
            with open(sol_dst, "w", encoding="utf-8") as f:
                f.write(c)

    print("✓ Section III migration complete.")

def migrate_ai():
    src_dir = os.path.join(BASE_DIR, "CS-321 Foundation of AI and ML")
    dst_section = os.path.join(BASE_DIR, "Section IV - Foundation of Artificial Intelligence and Machine Learning")
    os.makedirs(dst_section, exist_ok=True)
    print(">>> Migrating Section IV - Foundation of Artificial Intelligence and Machine Learning...")

    for slip_num in range(1, 26):
        s_src = os.path.join(src_dir, f"ai_slip_{slip_num:02d}")
        s_dst = os.path.join(dst_section, f"Slip_{slip_num:02d}")
        os.makedirs(s_dst, exist_ok=True)

        # 1. PDF
        pdf_src = os.path.join(s_src, f"ai_slip_{slip_num:02d}.pdf")
        pdf_dst = os.path.join(s_dst, f"Slip_{slip_num:02d}_AI_SOLUTION.pdf")
        if os.path.exists(pdf_src):
            shutil.copy2(pdf_src, pdf_dst)

        # 2. Python files
        q1_src = os.path.join(s_src, f"ai_slip_{slip_num:02d}_q1.py")
        q1_dst = os.path.join(s_dst, f"Slip_{slip_num:02d}_Q1.py")
        if os.path.exists(q1_src):
            shutil.copy2(q1_src, q1_dst)

        q2_src = os.path.join(s_src, f"ai_slip_{slip_num:02d}_q2.py")
        q2_or_src = os.path.join(s_src, f"ai_slip_{slip_num:02d}_q2_or.py")

        has_or = os.path.exists(q2_or_src)
        if has_or:
            q2_dst_a = os.path.join(s_dst, f"Slip_{slip_num:02d}_Q2_OptionA.py")
            q2_dst_b = os.path.join(s_dst, f"Slip_{slip_num:02d}_Q2_OptionB.py")
            if os.path.exists(q2_src):
                shutil.copy2(q2_src, q2_dst_a)
            shutil.copy2(q2_or_src, q2_dst_b)
        else:
            q2_dst = os.path.join(s_dst, f"Slip_{slip_num:02d}_Q2.py")
            if os.path.exists(q2_src):
                shutil.copy2(q2_src, q2_dst)

        # Datasets if present
        for f in os.listdir(s_src):
            if f.endswith(".csv") or f.endswith(".txt"):
                shutil.copy2(os.path.join(s_src, f), os.path.join(s_dst, f))

        # 3. Solution MD
        sol_src = os.path.join(s_src, f"ai_slip_{slip_num:02d}_solution.md")
        sol_dst = os.path.join(s_dst, f"Slip_{slip_num:02d}_AI_SOLUTION.md")
        if os.path.exists(sol_src):
            with open(sol_src, "r", encoding="utf-8") as f:
                c = f.read()
            c = c.replace(f"ai_slip_{slip_num:02d}_q1.py", f"Slip_{slip_num:02d}_Q1.py")
            if has_or:
                c = c.replace(f"ai_slip_{slip_num:02d}_q2.py", f"Slip_{slip_num:02d}_Q2_OptionA.py")
                c = c.replace(f"ai_slip_{slip_num:02d}_q2_or.py", f"Slip_{slip_num:02d}_Q2_OptionB.py")
            else:
                c = c.replace(f"ai_slip_{slip_num:02d}_q2.py", f"Slip_{slip_num:02d}_Q2.py")
            c = c.replace(f"ai_slip_{slip_num:02d}.pdf", f"Slip_{slip_num:02d}_AI_SOLUTION.pdf")
            c = sanitize_md_header(c, f"Slip {slip_num:02d} — Foundation of AI & ML Solution Guide")
            with open(sol_dst, "w", encoding="utf-8") as f:
                f.write(c)

    print("✓ Section IV migration complete.")

if __name__ == "__main__":
    migrate_os()
    migrate_java()
    migrate_ds()
    migrate_ai()
    print("\nAll 4 Sections successfully migrated!")
