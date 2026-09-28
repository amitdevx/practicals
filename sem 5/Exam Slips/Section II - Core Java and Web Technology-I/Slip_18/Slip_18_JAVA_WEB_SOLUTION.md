# Slip 18 — Core Java and Web Technology-I Solution Guide

## Question 1: Multi-Button Color Changer [15 Marks]

### Problem Statement
Create an application with multiple buttons (Red, Green, Blue) that print color and change background color.

### Concept & Algorithm
Uses JButtons with ActionListeners to modify content pane background color and print to terminal.

### Compilation & Execution
```bash
javac Slip_18_Q1.java
java Slip_18_Q1
```

### Sample Output
```text
Selected Color: RED
Selected Color: GREEN
Selected Color: BLUE
```

---

## Question 2: Node.js HTTP Server [15 Marks]

### Problem Statement
Create a Node.js HTTP server that sends an appropriate response to a client request.

### Concept & Design
Uses the core 'http' module to create an HTTP server responding with status 200 and text content.

### Compilation & Execution
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
**Answer:** A single-threaded loop that handles asynchronous I/O callbacks non-blockingly.

### Q2. What does http.createServer() do?
**Answer:** Creates an instance of http.Server that listens for HTTP requests and issues responses.

### Q3. What is res.writeHead() in Node.js?
**Answer:** Sends an HTTP status code and response headers to the incoming request.

### Q4. What is FlowLayout in Java GUI?
**Answer:** The default layout manager for JPanel that arranges components in a directional flow, like words in a paragraph.

### Q5. What is npm?
**Answer:** Node Package Manager, the default package repository and dependency manager for Node.js.
