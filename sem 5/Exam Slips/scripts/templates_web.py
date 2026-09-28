# Web Technology Templates (HTML5, CSS3, JavaScript, Node.js)

def get_web_slip01_q2():
    return '''<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>College Registration Form</title>
    <style>
        body { font-family: Arial, sans-serif; background-color: #f4f6f9; display: flex; justify-content: center; padding: 20px; }
        .form-container { background: #fff; padding: 30px; border-radius: 8px; box-shadow: 0 4px 10px rgba(0,0,0,0.1); width: 450px; }
        h2 { text-align: center; color: #2c3e50; }
        .form-group { margin-bottom: 15px; }
        label { display: block; margin-bottom: 5px; font-weight: bold; color: #34495e; }
        input, select, textarea { width: 100%; padding: 10px; border: 1px solid #ccc; border-radius: 4px; box-sizing: border-box; }
        input:focus { border-color: #3498db; outline: none; }
        .btn-submit { background-color: #27ae60; color: white; border: none; padding: 12px; width: 100%; border-radius: 4px; cursor: pointer; font-size: 16px; font-weight: bold; }
        .btn-submit:hover { background-color: #219150; }
    </style>
</head>
<body>
    <div class="form-container">
        <h2>College Registration Form</h2>
        <form action="#" method="post">
            <div class="form-group">
                <label for="fullname">Full Name:</label>
                <input type="text" id="fullname" name="fullname" required pattern="[A-Za-z ]{3,50}" placeholder="Enter full name">
            </div>
            <div class="form-group">
                <label for="email">Email Address:</label>
                <input type="email" id="email" name="email" required placeholder="name@college.edu">
            </div>
            <div class="form-group">
                <label for="phone">Phone Number:</label>
                <input type="tel" id="phone" name="phone" required pattern="[0-9]{10}" placeholder="10-digit mobile number">
            </div>
            <div class="form-group">
                <label for="course">Select Course:</label>
                <select id="course" name="course" required>
                    <option value="">-- Choose Course --</option>
                    <option value="BSc-CS">T.Y. B.Sc. (Computer Science)</option>
                    <option value="BCA">BCA (Science)</option>
                    <option value="MSc-CS">M.Sc. (Computer Science)</option>
                </select>
            </div>
            <div class="form-group">
                <label for="dob">Date of Birth:</label>
                <input type="date" id="dob" name="dob" required>
            </div>
            <button type="submit" class="btn-submit">Submit Registration</button>
        </form>
    </div>
</body>
</html>
'''

def get_web_slip02_q2():
    return '''<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Student Registration Form</title>
    <style>
        body { font-family: 'Segoe UI', sans-serif; background-color: #eef2f7; display: flex; justify-content: center; align-items: center; min-height: 100vh; margin: 0; }
        .card { background: white; padding: 30px; border-radius: 10px; width: 420px; box-shadow: 0 4px 15px rgba(0,0,0,0.08); }
        h2 { color: #1e3a8a; text-align: center; margin-top: 0; }
        label { display: block; margin: 12px 0 5px; font-weight: 600; color: #374151; }
        input, select { width: 100%; padding: 10px; border: 1.5px solid #d1d5db; border-radius: 6px; box-sizing: border-box; }
        input:invalid:focus { border-color: #ef4444; }
        input:valid:focus { border-color: #10b981; }
        button { margin-top: 20px; width: 100%; padding: 12px; background: #2563eb; color: white; border: none; border-radius: 6px; font-size: 16px; cursor: pointer; }
        button:hover { background: #1d4ed8; }
    </style>
</head>
<body>
    <div class="card">
        <h2>Student Registration</h2>
        <form>
            <label>Student PRN:</label>
            <input type="text" pattern="[0-9]{10}" placeholder="10-digit PRN" required>
            <label>Student Name:</label>
            <input type="text" pattern="[A-Za-z ]{3,}" placeholder="First and Last Name" required>
            <label>Gender:</label>
            <select required>
                <option value="">Select Gender</option>
                <option>Male</option>
                <option>Female</option>
                <option>Other</option>
            </select>
            <label>Marks Percentage (HSC):</label>
            <input type="number" min="35" max="100" step="0.01" placeholder="e.g. 84.5" required>
            <button type="submit">Register Student</button>
        </form>
    </div>
</body>
</html>
'''

def get_web_slip03_q2():
    return '''<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>College Homepage - Flexbox Layout</title>
    <style>
        * { box-sizing: border-box; margin: 0; padding: 0; font-family: Arial, sans-serif; }
        header { background: #2c3e50; color: white; padding: 20px; text-align: center; }
        nav { background: #34495e; display: flex; justify-content: center; }
        nav a { color: white; padding: 14px 20px; text-decoration: none; font-weight: bold; }
        nav a:hover { background: #1abc9c; }
        .main-container { display: flex; flex-wrap: wrap; padding: 20px; gap: 20px; min-height: 400px; }
        .content { flex: 3; background: #ecf0f1; padding: 20px; border-radius: 5px; }
        .sidebar { flex: 1; background: #bdc3c7; padding: 20px; border-radius: 5px; }
        footer { background: #2c3e50; color: white; text-align: center; padding: 15px; }
        @media (max-width: 768px) {
            .main-container { flex-direction: column; }
            nav { flex-direction: column; text-align: center; }
        }
    </style>
</head>
<body>
    <header>
        <h1>Savitribai Phule Pune University Affiliated College</h1>
        <p>Excellence in Higher Education</p>
    </header>
    <nav>
        <a href="#home">Home</a>
        <a href="#about">About</a>
        <a href="#academics">Academics</a>
        <a href="#admissions">Admissions</a>
        <a href="#contact">Contact</a>
    </nav>
    <div class="main-container">
        <section class="content">
            <h2>Welcome to Computer Science Department</h2>
            <p>Offering specialized undergraduate and postgraduate courses under NEP 2020 curriculum with hands-on lab practicals and cutting edge research.</p>
        </section>
        <aside class="sidebar">
            <h3>Latest Notices</h3>
            <ul>
                <li>Sem-V Practical Exam Schedule</li>
                <li>Campus Placement Drive 2026</li>
                <li>Annual TechFest Registration</li>
            </ul>
        </aside>
    </div>
    <footer>
        <p>&copy; 2026 College Portal. All Rights Reserved.</p>
    </footer>
</body>
</html>
'''

def get_web_slip04_q2():
    return '''<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>DOM Background Color Switcher</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; padding-top: 100px; transition: background 0.4s; }
        h1 { color: #333; }
        button { padding: 12px 24px; font-size: 16px; font-weight: bold; background: #3498db; color: white; border: none; border-radius: 6px; cursor: pointer; }
        button:hover { background: #2980b9; }
    </style>
</head>
<body>
    <h1 id="heading">Click Button to Change Background Color</h1>
    <button onclick="changeBackground()">Change Color</button>

    <script>
        const colors = ['#f1c40f', '#e74c3c', '#2ecc71', '#9b59b6', '#34495e', '#1abc9c'];
        let idx = 0;
        function changeBackground() {
            document.body.style.backgroundColor = colors[idx];
            document.getElementById('heading').innerText = "Current Background: " + colors[idx];
            idx = (idx + 1) % colors.length;
        }
    </script>
</body>
</html>
'''

def get_web_slip05_q2():
    return '''<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Responsive Image Gallery with Flexbox</title>
    <style>
        body { font-family: Arial, sans-serif; background: #f8f9fa; padding: 20px; }
        h1 { text-align: center; color: #2c3e50; }
        .gallery { display: flex; flex-wrap: wrap; justify-content: center; gap: 20px; }
        .gallery-item { flex: 1 1 250px; max-width: 300px; overflow: hidden; border-radius: 8px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); background: white; transition: transform 0.3s, box-shadow 0.3s; }
        .gallery-item:hover { transform: translateY(-8px); box-shadow: 0 8px 16px rgba(0,0,0,0.2); }
        .gallery-img { width: 100%; height: 200px; background-color: #3498db; display: flex; align-items: center; justify-content: center; color: white; font-weight: bold; font-size: 18px; }
        .gallery-caption { padding: 10px; text-align: center; font-weight: bold; color: #555; }
    </style>
</head>
<body>
    <h1>Responsive Campus Gallery</h1>
    <div class="gallery">
        <div class="gallery-item"><div class="gallery-img" style="background:#e74c3c;">Library</div><div class="gallery-caption">Central Library</div></div>
        <div class="gallery-item"><div class="gallery-img" style="background:#2ecc71;">Computer Lab</div><div class="gallery-caption">Advanced Computing Lab</div></div>
        <div class="gallery-item"><div class="gallery-img" style="background:#f39c12;">Auditorium</div><div class="gallery-caption">Seminar Hall</div></div>
        <div class="gallery-item"><div class="gallery-img" style="background:#9b59b6;">Sports Arena</div><div class="gallery-caption">Indoor Sports Complex</div></div>
    </div>
</body>
</html>
'''

def get_web_slip06_q2():
    return '''<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hover Effects Demonstration</title>
    <style>
        body { font-family: Arial, sans-serif; display: flex; flex-direction: column; align-items: center; justify-content: center; height: 80vh; background: #ecf0f1; }
        .custom-btn { background: #3498db; color: white; padding: 14px 28px; border: none; border-radius: 5px; font-size: 18px; cursor: pointer; transition: all 0.3s ease; margin-bottom: 30px; }
        .custom-btn:hover { background: #e67e22; transform: scale(1.1); box-shadow: 0 6px 15px rgba(0,0,0,0.3); }
        .custom-link { color: #2c3e50; font-size: 20px; text-decoration: none; font-weight: bold; position: relative; padding-bottom: 5px; transition: color 0.3s; }
        .custom-link:hover { color: #e74c3c; letter-spacing: 1px; }
    </style>
</head>
<body>
    <button class="custom-btn">Interactive Button</button>
    <a href="#" class="custom-link">Animated Navigation Link</a>
</body>
</html>
'''

def get_web_slip07_q2():
    return '''<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Styled Programming Languages List</title>
    <style>
        body { font-family: 'Segoe UI', sans-serif; background: #fafafa; padding: 40px; }
        h2 { color: #2c3e50; }
        ul.prog-list { list-style: none; padding: 0; width: 350px; }
        ul.prog-list li { background: white; margin-bottom: 10px; padding: 12px 20px; border-left: 6px solid #3498db; border-radius: 4px; box-shadow: 0 2px 5px rgba(0,0,0,0.06); transition: all 0.2s ease; }
        ul.prog-list li:nth-child(1) { border-color: #f39c12; }
        ul.prog-list li:nth-child(2) { border-color: #27ae60; }
        ul.prog-list li:nth-child(3) { border-color: #8e44ad; }
        ul.prog-list li:nth-child(4) { border-color: #e74c3c; }
        ul.prog-list li:hover { transform: translateX(8px); background: #f0f7fb; }
    </style>
</head>
<body>
    <h2>Top Programming Languages</h2>
    <ul class="prog-list">
        <li>Java (Enterprise & Android)</li>
        <li>Python (Data Science & AI)</li>
        <li>JavaScript (Full-stack Web)</li>
        <li>C / C++ (Systems & OS)</li>
    </ul>
</body>
</html>
'''

def get_web_slip08_q2():
    return '''<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>DOM Image Switcher</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; padding: 50px; background: #fdfefe; }
        .img-box { width: 300px; height: 200px; line-height: 200px; margin: 20px auto; border-radius: 8px; color: white; font-weight: bold; font-size: 24px; transition: background 0.3s; }
        button { padding: 12px 24px; font-size: 16px; background: #2c3e50; color: white; border: none; border-radius: 4px; cursor: pointer; }
        button:hover { background: #1a252f; }
    </style>
</head>
<body>
    <h2>JavaScript DOM Manipulation & Event Handling</h2>
    <div id="imgBox" class="imgBox" style="background:#3498db;">State 1 (Blue)</div>
    <button onclick="toggleImage()">Toggle Image State</button>

    <script>
        let isAlt = false;
        function toggleImage() {
            const box = document.getElementById('imgBox');
            if (!isAlt) {
                box.style.backgroundColor = '#e67e22';
                box.innerText = 'State 2 (Orange)';
            } else {
                box.style.backgroundColor = '#3498db';
                box.innerText = 'State 1 (Blue)';
            }
            isAlt = !isAlt;
        }
    </script>
</body>
</html>
'''

def get_web_slip09_q2():
    return '''// JavaScript Arrow Functions for Arithmetic Operations
const add = (a, b) => a + b;
const subtract = (a, b) => a - b;
const multiply = (a, b) => a * b;
const divide = (a, b) => (b !== 0 ? a / b : "Cannot divide by zero");

const num1 = 20;
const num2 = 5;

console.log("=== Demonstration of Arrow Functions ===");
console.log(`${num1} + ${num2} = ${add(num1, num2)}`);
console.log(`${num1} - ${num2} = ${subtract(num1, num2)}`);
console.log(`${num1} * ${num2} = ${multiply(num1, num2)}`);
console.log(`${num1} / ${num2} = ${divide(num1, num2)}`);
'''

def get_web_slip10_q2():
    return '''// Student Report using Template Literals
const studentName = "Aarav Sharma";
const rollNo = 101;
const marks = {
    OperatingSystems: 88,
    CoreJava: 92,
    DataScience: 85
};

const total = marks.OperatingSystems + marks.CoreJava + marks.DataScience;
const percentage = (total / 300) * 100;
const result = percentage >= 40 ? "PASS" : "FAIL";

const report = `
=============================================
           STUDENT GRADE REPORT
=============================================
Student Name : ${studentName}
Roll Number  : ${rollNo}
---------------------------------------------
Subject                  Marks (Out of 100)
---------------------------------------------
Operating Systems        : ${marks.OperatingSystems}
Core Java & Web Tech     : ${marks.CoreJava}
Data Science & Analytics : ${marks.DataScience}
---------------------------------------------
Total Marks  : ${total} / 300
Percentage   : ${percentage.toFixed(2)}%
Final Status : ${result}
=============================================
`;

console.log(report);
'''

def get_web_slip11_q2():
    return '''// Total and Average Marks using Arrow Functions and Template Literals
const calculateScore = (m1, m2, m3) => {
    const total = m1 + m2 + m3;
    const avg = total / 3;
    return { total, avg };
};

const sub1 = 78, sub2 = 85, sub3 = 90;
const { total, avg } = calculateScore(sub1, sub2, sub3);

console.log(`
Subject 1 Marks : ${sub1}
Subject 2 Marks : ${sub2}
Subject 3 Marks : ${sub3}
-------------------------
Total Marks     : ${total}
Average Marks   : ${avg.toFixed(2)}
`);
'''

def get_web_slip12_q2():
    return '''// Product Bill using Arrow Function and Template Literals
const generateBill = (productName, price, quantity) => {
    const subtotal = price * quantity;
    const gst = subtotal * 0.18; // 18% GST
    const grandTotal = subtotal + gst;
    return `
=====================================
          RETAIL STORE BILL
=====================================
Product Name : ${productName}
Unit Price   : ₹${price.toFixed(2)}
Quantity     : ${quantity}
-------------------------------------
Subtotal     : ₹${subtotal.toFixed(2)}
GST (18%)    : ₹${gst.toFixed(2)}
-------------------------------------
Grand Total  : ₹${grandTotal.toFixed(2)}
=====================================
`;
};

console.log(generateBill("Wireless Headphones", 2499.00, 2));
'''

def get_web_slip13_q2():
    return '''// Swap two numbers without third variable using Array Destructuring
let a = 42;
let b = 99;

console.log(`Before Swap: a = ${a}, b = ${b}`);

// Destructuring assignment swap
[a, b] = [b, a];

console.log(`After Swap:  a = ${a}, b = ${b}`);
'''

def get_web_slip14_q2():
    return '''// Object Destructuring for Employee Details
const employee = {
    name: "Rohan Varma",
    department: "Cloud Engineering",
    salary: 85000,
    city: "Pune",
    experienceYears: 4
};

// Extract values using object destructuring
const { name, department, salary } = employee;

console.log("=== Employee Information (Destructured) ===");
console.log(`Employee Name : ${name}`);
console.log(`Department    : ${department}`);
console.log(`Salary        : ₹${salary}`);
'''

def get_web_slip15_q2():
    return '''// Array Copy using Spread Operator and adding a new element
const originalArray = ["Apple", "Banana", "Cherry"];

// Copy using spread operator and append new element
const updatedArray = [...originalArray, "Dragonfruit"];

console.log("Original Array:", originalArray);
console.log("Copied & Extended Array:", updatedArray);
'''

def get_web_slip16_q2():
    return '''// Rest Parameter to accept any number of values and calculate sum
const sumAll = (...numbers) => {
    return numbers.reduce((acc, curr) => acc + curr, 0);
};

console.log("Sum of (10, 20, 30):", sumAll(10, 20, 30));
console.log("Sum of (5, 15, 25, 35, 45):", sumAll(5, 15, 25, 35, 45));
console.log("Sum of empty list:", sumAll());
'''

def get_web_slip17_q2():
    return '''// ES6 Module Export / Import Demonstration
const mathOperations = {
    add: (a, b) => a + b,
    subtract: (a, b) => a - b,
    multiply: (a, b) => a * b,
    divide: (a, b) => (b !== 0 ? a / b : "Infinity")
};

// Exporting module for CommonJS / ES6
module.exports = mathOperations;

// In-file test demonstration
const { add, subtract, multiply, divide } = mathOperations;
console.log("Math Module Operations:");
console.log(`Add(15, 5)      : ${add(15, 5)}`);
console.log(`Subtract(15, 5) : ${subtract(15, 5)}`);
console.log(`Multiply(15, 5) : ${multiply(15, 5)}`);
console.log(`Divide(15, 5)   : ${divide(15, 5)}`);
'''

def get_web_slip18_q2():
    return '''// Node.js HTTP Server
const http = require('http');

const PORT = 3000;
const server = http.createServer((req, res) => {
    res.writeHead(200, { 'Content-Type': 'text/plain' });
    res.end('Hello from Node.js HTTP Server! Request received successfully.\\n');
});

// Self-test snippet: listens briefly and confirms
server.listen(PORT, () => {
    console.log(`Server is running at http://localhost:${PORT}/`);
    server.close(); // Close immediately for test automation
});
'''

def get_web_slip19_q2():
    return '''// Async/Await User Login Simulation
const authenticateUser = async (username, password) => {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            if (username === "admin" && password === "secret123") {
                resolve("Login Successful! Welcome to the dashboard.");
            } else {
                reject(new Error("Invalid Username or Password!"));
            }
        }, 300);
    });
};

const handleLogin = async (user, pass) => {
    try {
        console.log(`Attempting login for '${user}'...`);
        const message = await authenticateUser(user, pass);
        console.log(`[+] Success: ${message}`);
    } catch (error) {
        console.error(`[-] Error: ${error.message}`);
    }
};

(async () => {
    await handleLogin("admin", "secret123");
    await handleLogin("guest", "wrongpass");
})();
'''

def get_web_slip20_q2():
    return '''// Promise to Divide Two Numbers with Zero Handling
const divideNumbers = (numerator, denominator) => {
    return new Promise((resolve, reject) => {
        if (denominator === 0) {
            reject(new Error("Division by zero error: Denominator cannot be 0."));
        } else {
            resolve(numerator / denominator);
        }
    });
};

divideNumbers(100, 4)
    .then(result => console.log(`100 / 4 = ${result}`))
    .catch(err => console.error(err.message));

divideNumbers(50, 0)
    .then(result => console.log(`50 / 0 = ${result}`))
    .catch(err => console.error(`Caught rejection: ${err.message}`));
'''

def get_web_slip21_q2():
    return '''// Node.js Path Module Operations
const path = require('path');

const samplePath = '/home/user/docs/file.txt';

console.log("=== Node.js Path Module Operations ===");
console.log("Joined Path:   ", path.join('/root', 'projects', 'node_app', 'index.js'));
console.log("Resolved Path: ", path.resolve('temp', 'sample.txt'));
console.log("Directory Name:", path.dirname(samplePath));
console.log("Base Name:     ", path.basename(samplePath));
console.log("Extension:     ", path.extname(samplePath));
console.log("Parsed Object: ", path.parse(samplePath));
'''

def get_web_slip22_q2():
    return '''// Asynchronous File Operations using Node.js fs module
const fs = require('fs');

const filename = 'async_demo.txt';

fs.writeFile(filename, 'Initial content written asynchronously.', (err) => {
    if (err) throw err;
    console.log('[+] File written successfully.');

    fs.readFile(filename, 'utf8', (err, data) => {
        if (err) throw err;
        console.log('[+] File contents:', data);

        fs.unlink(filename, (err) => {
            if (err) throw err;
            console.log('[+] File cleaned up.');
        });
    });
});
'''

def get_web_slip23_q2():
    return '''// Node.js fs: Create, Write, Read and Append Data
const fs = require('fs');

const file = 'crud_demo.txt';

fs.writeFileSync(file, 'Initial Line 1.\\n');
console.log('[+] Created and wrote to file.');

fs.appendFileSync(file, 'Appended Line 2.\\n');
console.log('[+] Appended data to file.');

const data = fs.readFileSync(file, 'utf8');
console.log('--- Current File Contents ---');
console.log(data);

fs.unlinkSync(file);
console.log('[+] File deleted.');
'''

def get_web_slip24_q2():
    return '''// Synchronous vs Asynchronous File Operations in Node.js
const fs = require('fs');

const syncFile = 'sync_test.txt';
const asyncFile = 'async_test.txt';

console.log('--- Starting Synchronous Execution ---');
fs.writeFileSync(syncFile, 'Synchronous file content.');
const syncData = fs.readFileSync(syncFile, 'utf8');
console.log('Read Synchronous:', syncData);
fs.unlinkSync(syncFile);
console.log('Synchronous operations completed (Blocking).\\n');

console.log('--- Starting Asynchronous Execution ---');
fs.writeFile(asyncFile, 'Asynchronous file content.', () => {
    fs.readFile(asyncFile, 'utf8', (err, asyncData) => {
        console.log('Read Asynchronous:', asyncData);
        fs.unlinkSync(asyncFile);
        console.log('Asynchronous operations completed (Non-blocking).');
    });
});
'''

def get_web_slip25_q2():
    return '''// Directory Management & JSON Parsing in Node.js
const fs = require('fs');
const path = require('path');

const dirName = 'test_dir';
const jsonFile = path.join(dirName, 'data.json');

// 1. Create Directory
if (!fs.existsSync(dirName)) {
    fs.mkdirSync(dirName);
    console.log(`[+] Directory '${dirName}' created.`);
}

// 2. Write structured JSON
const student = { name: "Snehal", roll: 105, marks: [85, 90, 78] };
fs.writeFileSync(jsonFile, JSON.stringify(student, null, 2));
console.log('[+] JSON data written.');

// 3. Read and Parse JSON
const rawData = fs.readFileSync(jsonFile, 'utf8');
const parsed = JSON.parse(rawData);
console.log('[+] Parsed JSON Student Name:', parsed.name);

// Cleanup
fs.unlinkSync(jsonFile);
fs.rmdirSync(dirName);
console.log('[+] Cleanup complete.');
'''

def get_web_slip26_q2():
    return '''// Copy, Rename and Delete Files Asynchronously using Node.js fs
const fs = require('fs');

const src = 'source.txt';
const copy = 'copy.txt';
const renamed = 'renamed.txt';

fs.writeFileSync(src, 'Sample data to copy.');

fs.copyFile(src, copy, (err) => {
    if (err) throw err;
    console.log('[+] File copied successfully.');

    fs.rename(copy, renamed, (err) => {
        if (err) throw err;
        console.log('[+] File renamed successfully.');

        fs.unlink(renamed, (err) => {
            if (err) throw err;
            console.log('[+] File deleted successfully.');
            fs.unlinkSync(src);
        });
    });
});
'''

def get_web_slip27_q2():
    return '''// Read JSON, Modify properties, and Write back
const fs = require('fs');

const jsonPath = 'profile.json';
const initialData = { username: "amit_dev", role: "Student", active: false };

fs.writeFileSync(jsonPath, JSON.stringify(initialData, null, 2));

// Read & parse
const fileData = fs.readFileSync(jsonPath, 'utf8');
const user = JSON.parse(fileData);
console.log('Original Object:', user);

// Modify selected properties
user.role = "Administrator";
user.active = true;
user.lastLogin = "2026-09-26";

// Write back
fs.writeFileSync(jsonPath, JSON.stringify(user, null, 2));
console.log('Updated Object written to file:');
console.log(fs.readFileSync(jsonPath, 'utf8'));

fs.unlinkSync(jsonPath);
'''

def get_web_slip28_q2():
    return '''// List files in directory and filter by extensions (.txt, .json, .js)
const fs = require('fs');
const path = require('path');

const targetDir = '.';
const allowedExtensions = ['.txt', '.json', '.js'];

console.log(`Filtering files in '${targetDir}' for: ${allowedExtensions.join(', ')}`);

const files = fs.readdirSync(targetDir);
const filtered = files.filter(f => allowedExtensions.includes(path.extname(f)));

console.log('Matching Files:');
filtered.forEach(f => console.log('  ->', f));
'''

def get_web_slip29_q2():
    return '''// File statistics using fs.stat()
const fs = require('fs');

const target = __filename;

fs.stat(target, (err, stats) => {
    if (err) {
        console.error('Error fetching stats:', err);
        return;
    }
    console.log('=== File Statistics ===');
    console.log('Target:           ', target);
    console.log('File Size:        ', stats.size, 'bytes');
    console.log('Is Directory:     ', stats.isDirectory());
    console.log('Is File:          ', stats.isFile());
    console.log('Created At:       ', stats.birthtime);
    console.log('Last Modified:    ', stats.mtime);
    console.log('Last Accessed:    ', stats.atime);
});
'''

def get_web_slip30_q2():
    return '''// Mini File Management CLI in Node.js
const fs = require('fs');
const path = require('path');

const manageFile = (action, filename, content = '') => {
    switch (action) {
        case 'create':
            fs.writeFileSync(filename, content);
            console.log(`[+] Created '${filename}'.`);
            break;
        case 'read':
            if (fs.existsSync(filename)) {
                console.log(`--- Content of '${filename}' ---`);
                console.log(fs.readFileSync(filename, 'utf8'));
            } else {
                console.log(`[-] File '${filename}' not found.`);
            }
            break;
        case 'update':
            if (fs.existsSync(filename)) {
                fs.appendFileSync(filename, content);
                console.log(`[+] Appended content to '${filename}'.`);
            }
            break;
        case 'delete':
            if (fs.existsSync(filename)) {
                fs.unlinkSync(filename);
                console.log(`[+] Deleted '${filename}'.`);
            }
            break;
        default:
            console.log('Unknown action. Available: create, read, update, delete');
    }
};

// Demonstration
const testFile = 'cli_test.txt';
manageFile('create', testFile, 'Hello Node CLI!\\n');
manageFile('update', testFile, 'Second Line added.\\n');
manageFile('read', testFile);
manageFile('delete', testFile);
'''
