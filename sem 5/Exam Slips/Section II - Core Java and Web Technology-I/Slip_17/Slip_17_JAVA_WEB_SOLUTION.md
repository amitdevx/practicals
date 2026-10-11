# Slip 17 — Core Java and Web Technology-I Solution Guide

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
cd "$HOME/Code/practicals/sem 5/Exam Slips/Section II - Core Java and Web Technology-I/Slip_17" && \
javac --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_17_Q1.java && \
java --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_17_Q1
```

---

## Question 1: Key Combination Background Color Switcher [15 Marks]

### Problem Statement
Write a JavaFX application that changes background color based on combination of keys pressed (e.g. Ctrl+Alt+O for orange, Ctrl+Alt+R for red).

### Concept & Algorithm
- **GUI Framework:** JavaFX (`javafx.application.Application`, `Stage`, `Scene`, `StackPane`, `Label`).
- **Event Handling:** Attaches an event handler via `scene.addEventHandler(KeyEvent.KEY_PRESSED, e -> ...)`.
- **Modifier Detection:** Checks modifier states using `e.isControlDown()` and `e.isAltDown()`.
- **Key Code Identification:** Matches key identity with `e.getCode() == KeyCode.O` and `KeyCode.R`, then dynamically updates the CSS style `root.setStyle("-fx-background-color: ...")`.

### Compilation & Execution
Navigate to the `Slip_17` directory:
```bash
cd "$HOME/Code/practicals/sem 5/Exam Slips/Section II - Core Java and Web Technology-I/Slip_17"
```

Compile with OpenJFX modules:
```bash
javac --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_17_Q1.java
```

Run the application:
```bash
java --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_17_Q1
```

*(Optional) On headless environments without a display server:*
```bash
xvfb-run java --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_17_Q1
```

### Sample Output
```text
[GUI window displays instructions: "Press Ctrl+Alt+O for Orange, Ctrl+Alt+R for Red"]
- Press Ctrl + Alt + O -> Background switches to Orange
- Press Ctrl + Alt + R -> Background switches to Red
```

---

## Question 2: JavaScript Module Export and Import [15 Marks]

### Problem Statement
Create a JavaScript module containing arithmetic operations, export functions and import them.

### Concept & Design
- Uses CommonJS module system (`module.exports = { add, multiply }`) and consumption via `const math = require('./mathModule')` (or modular ES6 syntax).
- Encourages encapsulation of reusable arithmetic utility logic.

### Compilation & Execution
Execute using Node.js:
```bash
node Slip_17_Q2.js
```

### Output Preview / Response
```text
Add(15, 5) : 20
Multiply(15, 5) : 75
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. How are keyboard events captured in JavaFX?
**Answer:** By adding an event handler to the `Scene` or a focusable `Node` using `scene.addEventHandler(KeyEvent.KEY_PRESSED, e -> { ... })`.

### Q2. How do you detect if Ctrl and Alt are simultaneously held in JavaFX?
**Answer:** Using the boolean accessor methods `e.isControlDown()` and `e.isAltDown()`.

### Q3. How do CommonJS modules differ from ES6 modules?
**Answer:** CommonJS uses runtime synchronous loading via `require()` and `module.exports` (standard in Node.js); ES6 modules use compile-time static `import` and `export` statements.

### Q4. What is `KeyCode` in JavaFX?
**Answer:** An enum in `javafx.scene.input` representing physical keyboard keys (e.g., `KeyCode.O`, `KeyCode.ENTER`, `KeyCode.ESCAPE`).

### Q5. How do you change component background color dynamically in JavaFX?
**Answer:** By applying CSS styling directly via `node.setStyle("-fx-background-color: <color>;")` or using JavaFX `Background` and `BackgroundFill` objects.
