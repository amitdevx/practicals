# Slip 14 — Core Java and Web Technology-I Solution Guide

## Environment Prerequisites & Installation Setup

Before running the programs in this slip, ensure the required runtime environments and libraries (Java JDK, OpenJFX, Node.js) are installed on your Linux / Ubuntu system.

### 1. Install Java JDK, JavaFX (OpenJFX), and Node.js
Run the following command in your terminal to install all required packages:
```bash
sudo apt update && sudo apt install -y default-jdk openjfx nodejs
```

### 2. Verify Installation & JavaFX Library Path
Verify that the tools and OpenJFX libraries are correctly placed:
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
You can copy and paste this single chained command to verify/install prerequisites, navigate to the folder, compile, and run Question 1:
```bash
sudo apt update && sudo apt install -y openjfx default-jdk nodejs && \
test -f /usr/share/openjfx/lib/javafx.controls.jar && \
cd "$HOME/Code/practicals/sem 5/Exam Slips/Section II - Core Java and Web Technology-I/Slip_14" && \
javac --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_14_Q1.java && \
java --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_14_Q1
```

---

## Question 1: JavaFX GUI Prime Number Checker [15 Marks]

### Problem Statement
Write a GUI program that takes numeric input via TextField and displays whether it is prime upon clicking the Process button.

### Concept & Algorithm
- **GUI Framework:** JavaFX (`javafx.application.Application`, `Stage`, `Scene`, `VBox`, `TextField`, `Button`, `Label`).
- **Event Handling:** Lambda expression attached via `processButton.setOnAction(e -> ...)`.
- **Prime Logic:** 
  - Numbers $\le 1$ are not prime.
  - Test divisibility from $2$ up to $\lfloor\sqrt{n}\rfloor$. If divisible by any factor, the number is not prime; otherwise, it is prime.
- **Input Validation:** Wrapped inside `try-catch (NumberFormatException ex)` to gracefully handle non-numeric inputs.

### Compilation & Execution
Navigate to the `Slip_14` directory:
```bash
cd "$HOME/Code/practicals/sem 5/Exam Slips/Section II - Core Java and Web Technology-I/Slip_14"
```

Compile with OpenJFX modules:
```bash
javac --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_14_Q1.java
```

Run the application:
```bash
java --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_14_Q1
```

*(Optional) On headless environments without a display server:*
```bash
xvfb-run java --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_14_Q1
```

### Sample Output
```text
[GUI window titled "Prime Number Checker"]
- Input: 17  -> Result: "17 is a Prime Number"
- Input: 24  -> Result: "24 is NOT a Prime Number"
- Input: abc -> Result: "Invalid Integer!"
```

---

## Question 2: Object Destructuring for Employee Details [15 Marks]

### Problem Statement
Create an object containing employee details (name, department, salary) and extract using object destructuring.

### Concept & Design
- Uses ES6 object destructuring syntax:
  ```javascript
  const { name, department, salary } = employee;
  ```
- Extracts object properties directly into local variables by matching key names, eliminating repetitive property lookups.

### Compilation & Execution
Execute using Node.js:
```bash
node Slip_14_Q2.js
```

### Output Preview / Response
```text
=== Employee Information (Destructured) ===
Employee Name : Rohan Varma
Department    : Cloud Engineering
Salary        : ₹85000
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the lifecycle of a JavaFX Application?
**Answer:** The `Application` class executes `init()` (initialization), then `start(Stage primaryStage)` (main entry point for constructing GUI on the JavaFX Application Thread), and finally `stop()` when the application exits.

### Q2. Why are `--module-path` and `--add-modules` required when compiling JavaFX?
**Answer:** Since JDK 11, JavaFX was decoupled from the standard JDK into separate modular JARs. Hence, we must explicitly specify the library directory (`--module-path /usr/share/openjfx/lib`) and the required modules (`--add-modules javafx.controls`).

### Q3. How does event handling work in JavaFX?
**Answer:** Components like `Button` use the `setOnAction()` method accepting an `EventHandler<ActionEvent>`, which can be concisely implemented using a lambda expression (`e -> { ... }`).

### Q4. What is object destructuring in ES6 JavaScript?
**Answer:** A syntax that unpacks properties from an object into distinct variables matching the property names, e.g., `const { name, salary } = employee;`.

### Q5. Why is checking up to $\sqrt{n}$ sufficient for a primality test?
**Answer:** If $n$ has a factor larger than $\sqrt{n}$, its paired factor must be smaller than $\sqrt{n}$. If no factor is found up to $\sqrt{n}$, $n$ is guaranteed to be prime.
