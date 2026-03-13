# Code Images - CS-253 Exam Slips

📁 **Generated**: 90 PNG images with VS Code Dark+ theme  
📊 **Total Size**: ~15 MB  
🎨 **Theme**: VS Code Dark background (#1E1E1E)

## Structure

```
code_images/
├── Slip_01/
│   ├── Slip_01_Q1_OptionA.png      (C code - Data Structures)
│   ├── Slip_01_Q1_OptionB.png      (C code - Data Structures)
│   └── Slip_01_DBMS_Solution.png   (SQL code - Database)
├── Slip_02/
│   ├── Slip_02_Q1_OptionA.png
│   ├── Slip_02_Q1_OptionB.png
│   └── Slip_02_DBMS_Solution.png
...
└── Slip_30/
    ├── Slip_30_Q1_OptionA.png
    ├── Slip_30_Q1_OptionB.png
    └── Slip_30_DBMS_Solution.png
```

## Features

✅ **VS Code Dark+ Theme**  
✅ **Line Numbers** (left margin, gray)  
✅ **Clean Title Bar** with traffic lights  
✅ **Rounded Corners** (10px radius)  
✅ **Monospace Font** (Consolas/Monaco/Courier)  
✅ **High Resolution** (1400px wide)  
✅ **Auto-sizing** based on code length  

## Notes

- **btree.h inlined**: For slips using `#include "btree.h"`, the header content is automatically embedded
- **Maximum 100 lines per image**: Longer code is truncated with a note
- **Plain text rendering**: No syntax highlighting to ensure stability (all code in light gray)
- **XML-safe**: All special characters properly escaped

## Generation

Generated using `generate_code_images_fixed.js` with Node.js and Sharp library.

**Command**: `node generate_code_images_fixed.js`

