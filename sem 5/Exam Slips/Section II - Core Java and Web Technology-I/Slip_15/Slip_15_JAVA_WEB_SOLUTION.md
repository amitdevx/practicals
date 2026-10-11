# Slip 15 — Core Java and Web Technology-I Solution Guide

## Environment Prerequisites & Installation Setup

Before running the programs in this slip, ensure the required runtime environments and libraries (Java JDK, OpenJFX, Node.js) are installed on your Linux / Ubuntu system.

### 1. Install Java JDK, JavaFX (OpenJFX), and Node.js
```bash
sudo apt update && sudo apt install -y default-jdk openjfx nodejs
```

### 2. Verify Installation & JavaFX Library Path
```bash
# Verify compilers and runtimes
javac -version
java -version
node -v

# Verify JavaFX controls library exists
test -f /usr/share/openjfx/lib/javafx.controls.jar && echo "✓ OpenJFX is installed at /usr/share/openjfx/lib"
```

> [!NOTE]
> On Ubuntu/Debian, `openjfx` installs JAR files into `/usr/share/openjfx/lib/`.
> If you manually downloaded the JavaFX SDK, set `--module-path` to your downloaded SDK's `lib` folder instead.

### 3. All-in-One One-Liner (Install, Verify, Compile & Run)
```bash
sudo apt update && sudo apt install -y openjfx default-jdk nodejs && \
test -f /usr/share/openjfx/lib/javafx.controls.jar && \
cd "$HOME/Code/practicals/sem 5/Exam Slips/Section II - Core Java and Web Technology-I/Slip_15" && \
javac --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_15_Q1.java && \
java --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_15_Q1
```

---

## Question 1: JavaFX Simple GUI Calculator [15 Marks]

### Problem Statement
Write a GUI program to build a simple calculator with digit buttons (0-9) and operators (+, -, *, /).

### Concept & Algorithm
- **GUI Framework:** JavaFX (`javafx.application.Application`, `Stage`, `Scene`, `VBox`, `GridPane`, `TextField`, `Button`).
- **Layout Architecture:**
  - `GridPane` arranges calculator keys in a 4x4 matrix with horizontal/vertical spacing.
  - `VBox` stacks the top output `TextField` above the button grid.
- **Calculator State:**
  - Maintains `num1`, `num2`, and `operator`.
  - Supports continuous digit concatenation, clear (`C`), binary arithmetic operators, and evaluation (`=`).

### Compilation & Execution
Navigate to the `Slip_15` directory:
```bash
cd "$HOME/Code/practicals/sem 5/Exam Slips/Section II - Core Java and Web Technology-I/Slip_15"
```

Compile with OpenJFX modules:
```bash
javac --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_15_Q1.java
```

Run the application:
```bash
java --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_15_Q1
```

*(Optional) On headless environments without a display server:*
```bash
xvfb-run java --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_15_Q1
```

### Sample Output
```text
[Interactive calculator GUI displaying calculation results]
- Press "7", "+", "8", "=" -> Display shows: 15.0
- Press "C"                 -> Display clears to empty
```

---

## Question 2: Spread Operator for Array Copy and Extension [15 Marks]

### Problem Statement
Write a JavaScript program to create copy of existing array using spread operator and add new element.

### Concept & Design
- Uses ES6 spread operator syntax `[...originalArray, newElement]` to perform a non-mutating shallow copy while appending an element.
- The original array remains completely unaltered.

### Compilation & Execution
Execute using Node.js:
```bash
node Slip_15_Q2.js
```

### Output Preview / Response
```text
Original Array: [ 'Apple', 'Banana', 'Cherry' ]
Copied & Extended Array: [ 'Apple', 'Banana', 'Cherry', 'Dragonfruit' ]
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the spread operator (...) in JavaScript?
**Answer:** An operator that expands an iterable (like an array) into individual elements in places where arguments or elements are expected.

### Q2. Does the spread operator create a shallow or deep copy?
**Answer:** It creates a shallow copy: top-level elements are cloned, but nested objects/arrays are copied by reference.

### Q3. How does GridPane arrange components in JavaFX?
**Answer:** `GridPane` positions nodes in a flexible grid of rows and columns using `grid.add(node, colIndex, rowIndex)`.

### Q4. How do you handle division by zero in Java?
**Answer:** For integer arithmetic, Java throws `ArithmeticException`; for floating-point values (`double` or `float`), dividing by zero results in `Infinity` or `NaN`.

### Q5. Why is `--module-path` required for JavaFX applications?
**Answer:** Since Java 11, JavaFX is not bundled inside the default JDK. The `--module-path` points `javac` and `java` to the external modular JavaFX libraries.
