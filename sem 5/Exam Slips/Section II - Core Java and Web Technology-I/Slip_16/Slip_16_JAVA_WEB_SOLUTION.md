# Slip 16 — Core Java and Web Technology-I Solution Guide

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
cd "$HOME/Code/practicals/sem 5/Exam Slips/Section II - Core Java and Web Technology-I/Slip_16" && \
javac --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_16_Q1.java && \
java --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_16_Q1
```

---

## Question 1: Shopping Cart Simulator GUI [15 Marks]

### Problem Statement
Write a JavaFX application that simulates a shopping cart with item buttons and running total.

### Concept & Algorithm
- **GUI Framework:** JavaFX (`javafx.application.Application`, `Stage`, `Scene`, `VBox`, `HBox`, `ListView`, `Button`, `Label`).
- **Dynamic List Handling:** Uses `cartList.getItems().add(itemName)` to append selected items dynamically to the JavaFX `ListView`.
- **Event Handling:** Lambda expressions on item buttons update the item list and recalculate the cumulative running total.

### Compilation & Execution
Navigate to the `Slip_16` directory:
```bash
cd "$HOME/Code/practicals/sem 5/Exam Slips/Section II - Core Java and Web Technology-I/Slip_16"
```

Compile with OpenJFX modules:
```bash
javac --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_16_Q1.java
```

Run the application:
```bash
java --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_16_Q1
```

*(Optional) On headless environments without a display server:*
```bash
xvfb-run java --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_16_Q1
```

### Sample Output
```text
[Shopping cart GUI displaying items added and updated bill total]
- Click "Notebook (₹50)" -> Cart shows: Notebook (₹50) | Total Bill: ₹50.0
- Click "Backpack (₹600)" -> Cart shows: Notebook (₹50), Backpack (₹600) | Total Bill: ₹650.0
```

---

## Question 2: Rest Parameter for Variable Arguments Sum [15 Marks]

### Problem Statement
Write a JavaScript program using rest parameter to accept any number of values and calculate sum.

### Concept & Design
- Uses ES6 rest parameter syntax `(...numbers)` to collect all passed arguments into a real JavaScript array.
- Uses `numbers.reduce((acc, curr) => acc + curr, 0)` for functional accumulation.

### Compilation & Execution
Execute using Node.js:
```bash
node Slip_16_Q2.js
```

### Output Preview / Response
```text
Sum of (10, 20, 30): 60
Sum of (5, 15, 25, 35, 45): 125
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the rest parameter in ES6?
**Answer:** A syntax prefix `...` that allows a function to collect an arbitrary number of arguments into a single standard JavaScript array.

### Q2. What is the difference between rest parameter and spread operator?
**Answer:** Rest parameter condenses individual elements into a single array (in parameter lists), whereas the spread operator expands an existing array into separate elements.

### Q3. How does `ListView` in JavaFX differ from `JList` in Swing?
**Answer:** JavaFX `ListView<T>` operates with observable collections (`ObservableList`) that automatically update the UI when modified via `getItems().add()`, without requiring explicit model adapters like `DefaultListModel`.

### Q4. What is `reduce()` in JavaScript arrays?
**Answer:** An array method that executes an accumulator function on each element from left to right to reduce the array to a single value.

### Q5. Can a rest parameter appear anywhere in a function parameter list?
**Answer:** No, the rest parameter must strictly be the last parameter in the function signature.
