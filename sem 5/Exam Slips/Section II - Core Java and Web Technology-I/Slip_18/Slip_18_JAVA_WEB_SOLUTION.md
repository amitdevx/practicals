# Slip 18 — Core Java and Web Technology-I Solution Guide

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
cd "$HOME/Code/practicals/sem 5/Exam Slips/Section II - Core Java and Web Technology-I/Slip_18" && \
javac --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_18_Q1.java && \
java --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_18_Q1
```

---

## Question 1: JavaFX Multi-Button Color Changer [15 Marks]

### Problem Statement
Create an application with multiple buttons (Red, Green, Blue) that print color and change background color.

### Concept & Algorithm
- **GUI Framework:** JavaFX (`javafx.application.Application`, `Stage`, `Scene`, `StackPane`, `HBox`, `Button`).
- **Layout Architecture:**
  - `HBox` centers the three color buttons horizontally.
  - `StackPane` serves as the root container whose background color changes dynamically.
- **Event Handling:** Button `setOnAction` triggers `root.setStyle("-fx-background-color: <color>;")` and logs the color name to stdout.

### Compilation & Execution
Navigate to the `Slip_18` directory:
```bash
cd "$HOME/Code/practicals/sem 5/Exam Slips/Section II - Core Java and Web Technology-I/Slip_18"
```

Compile with OpenJFX modules:
```bash
javac --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_18_Q1.java
```

Run the application:
```bash
java --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_18_Q1
```

*(Optional) On headless environments without a display server:*
```bash
xvfb-run java --module-path /usr/share/openjfx/lib --add-modules javafx.controls Slip_18_Q1
```

### Sample Output
```text
[GUI window displays Red, Green, and Blue buttons]
- Click "Red"   -> Background turns Red, console prints: RED
- Click "Green" -> Background turns Green, console prints: GREEN
- Click "Blue"  -> Background turns Blue, console prints: BLUE
```

---

## Question 2: Node.js HTTP Server [15 Marks]

### Problem Statement
Create a Node.js HTTP server that sends an appropriate response to a client request.

### Concept & Design
- Uses the core `http` module (`http.createServer((req, res) => { ... })`).
- Sets headers with `res.writeHead(200, { 'Content-Type': 'text/plain' })` and sends data via `res.end()`.

### Compilation & Execution
Execute using Node.js:
```bash
node Slip_18_Q2.js
```

### Output Preview / Response
```text
Server is running at http://localhost:3000/
Response: Hello from Node.js HTTP Server!
```

---

## Question 3: Oral / Viva Questions & Answers [5 Marks]

### Q1. What is the Node.js event loop?
**Answer:** A single-threaded, non-blocking mechanism that offloads asynchronous I/O operations to the system kernel and processes callbacks.

### Q2. What does `http.createServer()` return?
**Answer:** It returns an instance of `http.Server` configured to handle incoming HTTP requests.

### Q3. How does `HBox` differ from `VBox` in JavaFX?
**Answer:** `HBox` lays out its children in a single horizontal row, while `VBox` lays out its children in a single vertical column.

### Q4. How do you print messages to the console from a JavaFX application?
**Answer:** Using standard Java output methods such as `System.out.println("Message")` inside the event handlers.

### Q5. What is npm?
**Answer:** Node Package Manager, the default registry and dependency management tool for Node.js environments.
