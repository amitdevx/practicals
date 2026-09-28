import re

def convert_page_to_md(text):
    lines = text.split('\n')
    md_lines = []
    
    in_pre = False
    
    for line in lines:
        # Check if line has multiple space-separated chunks (likely a table or code)
        # We consider it preformatted if it has a sequence of 3 or more spaces, and isn't just leading spaces
        stripped = line.strip()
        
        # If it's a heading like Q.1 or Q1
        if re.match(r'^Q\.?\s*\d+', stripped):
            if in_pre:
                md_lines.append("```\n")
                in_pre = False
            md_lines.append(f"### {stripped}")
            continue
            
        if "  " in line.lstrip() and len(stripped) > 0:
            # It has multiple internal spaces, probably a table or formatted code
            if not in_pre:
                md_lines.append("\n```text")
                in_pre = True
            md_lines.append(line)
        else:
            if in_pre and not stripped:
                # empty line inside pre, keep it
                md_lines.append(line)
            elif in_pre and stripped:
                # end of preformatted block
                md_lines.append("```\n")
                in_pre = False
                md_lines.append(stripped)
            else:
                md_lines.append(stripped)
                
    if in_pre:
        md_lines.append("```\n")
        
    return '\n'.join(md_lines)

text = """                                     Savitribai Phule Pune University
                        T.Y.B.Sc.(C.S.) (NEP – 2020) SEM – V Practical Examination
                                        Lab Course CS-305-MJ-P
                                           Operating System-I
    Duration: 3 Hours                                                           Maximum Marks:35



Q.1) Write a C Menu driven Program to implement following functionality
    a) Accept Available
    b) Display Allocation, Max
    c) Display the contents of need matrix
    d) Display Available

                 Process        Allocation            Max            Available
                              A      B     C     A    B       C     A     B    C
                   P0         2      3     2     9     7      5     3     3    2
                   P1         4      0     0     5     2      2
                   P2         5      0     4     1     0      4
                   P3         4      3     3     4     4      4
                   P4         2      2     4     6     5      5

                                                                                  [15 Marks]

Q.2 Write a C program that behaves like a shell which displays the command
      prompt ‘$’. It accepts the command, tokenize the command line and
      execute it by creating the child process. Also implement the additional
       command ‘count’ as
    a. $ count c filename: It will display the number of characters in
        given file
    b. $ count w filename: It will display the number of words in given
        file
    c. $ count l filename: It will display the number of lines in given
        file
                                                                                  [15 Marks]

Q.3. Oral/Viva                                                                    [5 Marks]
"""
print(convert_page_to_md(text))

