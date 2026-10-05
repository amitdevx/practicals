#!/bin/bash

# ==========================================
# College PC Environment Setup & Verification Script
# ==========================================

# Colors & Symbols
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color
CHECK="✅"
CROSS="❌"
WARN="⚠️"

echo -e "${CYAN}=================================================${NC}"
echo -e "${CYAN}   Practical Exam Environment Setup & Tester     ${NC}"
echo -e "${CYAN}=================================================${NC}\n"

# Progress bar function
draw_progress_bar() {
    local width=40
    local percent=$1
    local num_hashes=$(echo "($percent * $width) / 100" | bc)
    local num_spaces=$((width - num_hashes))
    
    printf "\r[${GREEN}%-${width}s${NC}] %d%% " "$(printf '#%.0s' $(seq 1 $num_hashes))" "$percent"
}

# Function to run a command silently and return status
run_silent() {
    "$@" > /tmp/setup_script.log 2>&1
    return $?
}

# Function to install system packages with status UI
install_sys_pkg() {
    local pkg_name=$1
    local human_name=$2

    echo -ne "Installing/Updating ${human_name} ($pkg_name)... "
    
    if dpkg -l | grep -q "^ii  $pkg_name "; then
        echo -e "\r${CHECK} ${human_name} is already installed. Checking for updates..."
        # Upgrade specifically
        if run_silent sudo apt-get install --only-upgrade -y "$pkg_name"; then
            echo -e "${CHECK} ${human_name} is up-to-date."
        else
            echo -e "${WARN} ${human_name} update failed, but it is installed."
        fi
    else
        if run_silent sudo apt-get install -y "$pkg_name"; then
            echo -e "\r${CHECK} ${human_name} installed successfully."
        else
            echo -e "\r${CROSS} Failed to install ${human_name}. Check internet connection or permissions."
        fi
    fi
}

# Function to install python packages
install_py_pkg() {
    local pkgs=("$@")
    echo -e "\n${CYAN}Installing Python Libraries...${NC}"
    
    for pkg in "${pkgs[@]}"; do
        echo -ne "Installing/Updating Python package: $pkg... "
        # --break-system-packages is required in recent Ubuntu (23.04+) if not using venv
        if run_silent pip3 install --upgrade --break-system-packages "$pkg" || run_silent pip3 install --upgrade "$pkg"; then
            echo -e "\r${CHECK} Python package '$pkg' installed/updated successfully.        "
        else
            echo -e "\r${CROSS} Failed to install Python package '$pkg'.        "
        fi
    done
}

echo -e "${CYAN}Step 1: Updating APT repositories...${NC}"
run_silent sudo apt-get update -y
echo -e "${CHECK} Repositories updated.\n"

echo -e "${CYAN}Step 2: Installing Basic Programmer Tools & Compilers...${NC}"
install_sys_pkg "git" "Git"
install_sys_pkg "curl" "Curl"
install_sys_pkg "wget" "Wget"
install_sys_pkg "vim" "Vim Editor"
install_sys_pkg "unzip" "Unzip"
install_sys_pkg "build-essential" "GCC/G++ (C/C++ Compiler)"
install_sys_pkg "default-jdk" "Java Development Kit (Javac/Java)"
install_sys_pkg "nodejs" "Node.js (JavaScript Runtime)"
install_sys_pkg "npm" "NPM (Node Package Manager)"
install_sys_pkg "python3" "Python 3"
install_sys_pkg "python3-pip" "Python 3 PIP"

PY_LIBS=("numpy" "pandas" "scikit-learn" "matplotlib" "seaborn" "nltk" "mlxtend" "textblob" "scipy" "beautifulsoup4")
install_py_pkg "${PY_LIBS[@]}"

# Download NLTK data commonly used
echo -e "\n${CYAN}Downloading required NLTK datasets (punkt, stopwords)...${NC}"
run_silent python3 -c "import nltk; nltk.download('punkt'); nltk.download('stopwords')"
if [ $? -eq 0 ]; then
    echo -e "${CHECK} NLTK data downloaded successfully."
else
    echo -e "${CROSS} Failed to download NLTK data."
fi


echo -e "\n${CYAN}=================================================${NC}"
echo -e "${CYAN}Step 3: Verifying Installations via Test Codes...${NC}"
echo -e "${CYAN}=================================================${NC}\n"

# 1. Test C (GCC)
echo -ne "Testing C (GCC) Compiler... "
cat << 'EOF' > test_c.c
#include <stdio.h>
int main() { printf("SUCCESS\n"); return 0; }
EOF
if run_silent gcc -o test_c test_c.c && [ "$(./test_c)" == "SUCCESS" ]; then
    echo -e "\r${CHECK} C (GCC) Compiler working perfectly.       "
else
    echo -e "\r${CROSS} C (GCC) Compiler failed execution.        "
fi
rm -f test_c.c test_c

# 2. Test Java
echo -ne "Testing Java (JDK)... "
cat << 'EOF' > TestJava.java
public class TestJava {
    public static void main(String[] args) { System.out.println("SUCCESS"); }
}
EOF
if run_silent javac TestJava.java && [ "$(java TestJava)" == "SUCCESS" ]; then
    echo -e "\r${CHECK} Java (JDK) working perfectly.             "
else
    echo -e "\r${CROSS} Java (JDK) failed execution.              "
fi
rm -f TestJava.java TestJava.class

# 3. Test Node.js
echo -ne "Testing Node.js... "
cat << 'EOF' > test_node.js
console.log("SUCCESS");
EOF
if [ "$(node test_node.js)" == "SUCCESS" ]; then
    echo -e "\r${CHECK} Node.js working perfectly.                "
else
    echo -e "\r${CROSS} Node.js failed execution.                 "
fi
rm -f test_node.js

# 4. Test Python & Libraries
echo -ne "Testing Python & Libraries... "
cat << 'EOF' > test_py.py
try:
    import numpy as np
    import pandas as pd
    import sklearn
    import matplotlib
    import seaborn as sns
    import nltk
    import mlxtend
    import textblob
    import scipy
    import bs4
    print("SUCCESS")
except Exception as e:
    print("FAILED:", str(e))
EOF
PY_OUT=$(python3 test_py.py)
if [ "$PY_OUT" == "SUCCESS" ]; then
    echo -e "\r${CHECK} Python and all Data Science/AI libraries working perfectly."
else
    echo -e "\r${CROSS} Python library import failed: $PY_OUT"
fi
rm -f test_py.py

echo -e "\n${CYAN}=================================================${NC}"
echo -e "${CYAN}Step 4: Running All Practical Slips (Test Sweep)${NC}"
echo -e "${CYAN}=================================================${NC}\n"

echo "This phase will simulate running all practicals to ensure they compile/execute."
echo "Note: Programs requiring GUI or infinite input loops may block. We pipe default input."

TARGET_DIR="$(dirname "$0")/sem 5/Exam Slips"

if [ ! -d "$TARGET_DIR" ]; then
    echo -e "${WARN} Directory '$TARGET_DIR' not found. Skipping slip execution test."
else
    # OS
    echo -e "\n[Testing OS - C Files]"
    find "$TARGET_DIR/Section I - Operating System-I" -type f -name "*.c" | while read -r file; do
        gcc -Wall -Wno-unused-result "$file" -o "${file%.c}.out" 2>/dev/null
        if [ $? -eq 0 ]; then
            echo -e "${CHECK} Compiled: $(basename "$file")"
            # We don't execute here to avoid infinite loops, just verify compilation
        else
            echo -e "${CROSS} Failed to compile: $(basename "$file")"
        fi
        rm -f "${file%.c}.out"
    done

    # Java
    echo -e "\n[Testing Java/Web - Java Files]"
    find "$TARGET_DIR/Section II - Core Java and Web Technology-I" -type f -name "*.java" | while read -r file; do
        javac "$file" 2>/dev/null
        if [ $? -eq 0 ]; then
            echo -e "${CHECK} Compiled: $(basename "$file")"
        else
            echo -e "${CROSS} Failed to compile: $(basename "$file")"
        fi
        rm -f "${file%.java}.class"
    done

    # Data Science & AI (Syntax Check)
    echo -e "\n[Testing Data Science & AI - Python Files]"
    find "$TARGET_DIR" -type f -name "*.py" | while read -r file; do
        python3 -m py_compile "$file" 2>/dev/null
        if [ $? -eq 0 ]; then
            echo -e "${CHECK} Syntax OK: $(basename "$file")"
        else
            echo -e "${CROSS} Syntax Error: $(basename "$file")"
        fi
    done
fi

echo -e "\n${CYAN}Setup & Verification Completed!${NC}"
