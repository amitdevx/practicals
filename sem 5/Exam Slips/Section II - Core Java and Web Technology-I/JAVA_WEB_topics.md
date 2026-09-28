# Core Java and Web Technology-I (CS-306-MJ-P) Comprehensive Topic Analysis

> Strategic overview and breakdown of all 30 exam practical slips for SPPU TYBSc Computer Science (Sem V).

---

## 1. Core Practical Topics & Distribution

```
 CORE JAVA & WEB TECHNOLOGY-I
 │
 ├── Section A: Core Java [30 Slips - 15 Marks each]
 │   ├── Basic Java, Loops, Arrays & Math [Slips: 01, 02, 04, 29, 30]
 │   │   └── Array sum, Armstrong numbers, Matrix arithmetic, Prime/Zero checks, MyNumber
 │   ├── Object-Oriented Programming (Classes & Objects) [Slips: 06, 09, 13, 27, 28]
 │   │   └── Account, Employee, Clock, Person, MyDate date validation
 │   ├── Inheritance, Abstract Classes & Interfaces [Slips: 08, 11, 12, 21, 22, 23, 24, 25]
 │   │   └── Shape hierarchy, Vehicle hierarchy, Indoor/Outdoor games, College/Department,
 │   │       Product hierarchy, Multilevel inheritance, Cylinder volume, Calculator interface
 │   ├── Custom Exception Handling [Slips: 26, 28, 29]
 │   │   └── NotEligibleForExamException, InvalidDateException, ZeroNumberException
 │   ├── File Handling & Streams [Slips: 05, 10, 19]
 │   │   └── Reverse file content, Case conversion in files, File character/line/word count
 │   ├── Strings & Packages [Slips: 03, 07]
 │   │   └── String manipulation (concatenate, compare, reverse), Package creation & import
 │   └── Swing GUI & Event Handling [Slips: 14, 15, 16, 17, 18, 20]
 │       └── Prime check GUI, Simple Calculator GUI, Shopping Cart GUI, Key listener background,
 │           Color buttons GUI, Mouse motion/click tracker
 │
 └── Section B: Web Technology-I [30 Slips - 15 Marks each]
     ├── Client-Side Web: HTML5, CSS3 & JavaScript [Slips: 01 - 08]
     │   ├── HTML5 Form validation & CSS layout [Slips: 01, 02]
     │   ├── JavaScript Date/Time display & greeting [Slip: 03]
     │   ├── JavaScript String & Array operations [Slips: 04, 05]
     │   └── Interactive dynamic DOM manipulation [Slips: 06, 07, 08]
     │
     └── Server-Side Web: Node.js Core Modules & Server [Slips: 09 - 30]
         ├── HTTP Server (`http.createServer`) [Slips: 09, 10, 15, 20, 25]
         ├── File System Module (`fs.readFile`, `fs.writeFile`, `fs.appendFile`) [Slips: 11, 12, 16, 19, 21, 26, 27]
         ├── URL Module & Query String Parsing (`url.parse`) [Slips: 13, 14, 18, 22, 28]
         ├── Custom Modules & `exports` / `require` [Slips: 17, 23, 29]
         └── Events & Buffers (`events.EventEmitter`, `Buffer`) [Slips: 24, 30]
```

---

## 2. Complete Slip-wise Question Matrix (30 Slips)

| Slip | Question 1: Core Java (15 Marks) | Question 2: Web Technology (15 Marks) | File Format |
| :---: | :--- | :--- | :--- |
| **01** | Array sum and element display | Student Registration Form with HTML5 Validation | `Slip_01_Q1.java`, `Slip_01_Q2.html` |
| **02** | Armstrong numbers in given range | Responsive layout with CSS Flexbox / Grid | `Slip_02_Q1.java`, `Slip_02_Q2.html` |
| **03** | String operations (Concat, Compare, Reverse) | Real-time digital clock and greeting banner | `Slip_03_Q1.java`, `Slip_03_Q2.html` |
| **04** | Matrix Addition, Multiplication, Transpose | Factorial and Fibonacci generator in JS | `Slip_04_Q1.java`, `Slip_04_Q2.html` |
| **05** | Reverse file contents using FileReader | Email and Mobile Regex validation | `Slip_05_Q1.java`, `Slip_05_Q2.html` |
| **06** | Bank Account class with deposit/withdraw | Dynamic HTML table generator via JS | `Slip_06_Q1.java`, `Slip_06_Q2.html` |
| **07** | Custom Package creation & Driver import | Interactive Image Slider with auto-play | `Slip_07_Q1.java`, `Slip_07_Q2.html` |
| **08** | Shape abstract class (Rectangle, Triangle, Circle) | Multi-level dropdown navigation menu | `Slip_08_Q1.java`, `Slip_08_Q2.html` |
| **09** | Employee details and highest salary display | Node.js HTTP Hello World Web Server | `Slip_09_Q1.java`, `Slip_09_Q2.js` |
| **10** | Convert file contents to UPPERCASE | Node.js Web Server returning system information | `Slip_10_Q1.java`, `Slip_10_Q2.js` |
| **11** | Vehicle hierarchy (Light & Heavy Motor Vehicle) | Node.js Async File Reader (`fs.readFile`) | `Slip_11_Q1.java`, `Slip_11_Q2.js` |
| **12** | Indoor & Outdoor Games inheritance | Node.js File Copy and append utility | `Slip_12_Q1.java`, `Slip_12_Q2.js` |
| **13** | Clock class with AM/PM validation | Node.js URL Query String parser | `Slip_13_Q1.java`, `Slip_13_Q2.js` |
| **14** | Prime Checker Swing GUI | Node.js Search Query Parameter responder | `Slip_14_Q1.java`, `Slip_14_Q2.js` |
| **15** | Simple Arithmetic Calculator Swing GUI | Node.js Static File Web Server | `Slip_15_Q1.java`, `Slip_15_Q2.js` |
| **16** | Shopping Cart Item Selection Swing GUI | Node.js JSON Data API endpoint | `Slip_16_Q1.java`, `Slip_16_Q2.js` |
| **17** | Key listener background color change GUI | Custom Math Module export and calculation | `Slip_17_Q1.java`, `Slip_17_Q2.js` |
| **18** | Color buttons (Red, Green, Blue) Swing GUI | Node.js HTTP Request Method & Header inspector | `Slip_18_Q1.java`, `Slip_18_Q2.js` |
| **19** | Count characters, words and lines in file | Node.js Asynchronous Directory Lister | `Slip_19_Q1.java`, `Slip_19_Q2.js` |
| **20** | Mouse coordinates and click tracker GUI | Node.js Basic Routing Server (Home, About, Contact) | `Slip_20_Q1.java`, `Slip_20_Q2.js` |
| **21** | College & Department containment model | Node.js File Deletion and Rename utility | `Slip_21_Q1.java`, `Slip_21_Q2.js` |
| **22** | Product object array & highest price finder | Node.js HTTP POST Body parser | `Slip_22_Q1.java`, `Slip_22_Q2.js` |
| **23** | Continent -> Country -> State inheritance | Node.js Custom String Utilities Module | `Slip_23_Q1.java`, `Slip_23_Q2.js` |
| **24** | Cylinder volume and surface area calculation | Node.js EventEmitter custom event handling | `Slip_24_Q1.java`, `Slip_24_Q2.js` |
| **25** | Calculator interface implementation | Node.js Web Server returning current timestamp | `Slip_25_Q1.java`, `Slip_25_Q2.js` |
| **26** | User Exception: NotEligibleForExamException | Node.js File Stats inspector (size, birthtime) | `Slip_26_Q1.java`, `Slip_26_Q2.js` |
| **27** | Person class with address and details | Node.js File line-by-line stream reader | `Slip_27_Q1.java`, `Slip_27_Q2.js` |
| **28** | User Exception: InvalidDateException | Node.js Query parameter addition calculator | `Slip_28_Q1.java`, `Slip_28_Q2.js` |
| **29** | User Exception: ZeroNumberException for primes | Node.js Custom Date Formatter Module | `Slip_29_Q1.java`, `Slip_29_Q2.js` |
| **30** | MyNumber class with isNegative, isOdd, isEven | Node.js Buffer operations and Base64 conversion | `Slip_30_Q1.java`, `Slip_30_Q2.js` |

---

## 3. Quick Compilation & Execution Guide

```bash
# Compile and run Java Question 1
javac Slip_XX_Q1.java
java Slip_XX_Q1

# Run Web Technology Question 2
# For Slips 01 - 08 (HTML):
xdg-open Slip_XX_Q2.html   # or double-click to open in browser

# For Slips 09 - 30 (Node.js):
node Slip_XX_Q2.js
```
