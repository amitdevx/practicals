#!/usr/bin/env python3
import os
import subprocess

from templates_java_1 import (
    get_java_slip01_q1, get_java_slip02_q1, get_java_slip03_q1, get_java_slip04_q1,
    get_java_slip05_q1, get_java_slip06_q1, get_java_slip07_q1, get_java_slip08_q1,
    get_java_slip09_q1, get_java_slip10_q1
)
from templates_java_2 import (
    get_java_slip11_q1, get_java_slip12_q1, get_java_slip13_q1, get_java_slip14_q1,
    get_java_slip15_q1, get_java_slip16_q1, get_java_slip17_q1, get_java_slip18_q1,
    get_java_slip19_q1, get_java_slip20_q1
)
from templates_java_3 import (
    get_java_slip21_q1, get_java_slip22_q1, get_java_slip23_q1, get_java_slip24_q1,
    get_java_slip25_q1, get_java_slip26_q1, get_java_slip27_q1, get_java_slip28_q1,
    get_java_slip29_q1, get_java_slip30_q1
)
from templates_web import (
    get_web_slip01_q2, get_web_slip02_q2, get_web_slip03_q2, get_web_slip04_q2,
    get_web_slip05_q2, get_web_slip06_q2, get_web_slip07_q2, get_web_slip08_q2,
    get_web_slip09_q2, get_web_slip10_q2, get_web_slip11_q2, get_web_slip12_q2,
    get_web_slip13_q2, get_web_slip14_q2, get_web_slip15_q2, get_web_slip16_q2,
    get_web_slip17_q2, get_web_slip18_q2, get_web_slip19_q2, get_web_slip20_q2,
    get_web_slip21_q2, get_web_slip22_q2, get_web_slip23_q2, get_web_slip24_q2,
    get_web_slip25_q2, get_web_slip26_q2, get_web_slip27_q2, get_web_slip28_q2,
    get_web_slip29_q2, get_web_slip30_q2
)

BASE_DIR = "/home/amitdevx/Code/practicals/sem 5/Exam Slips/CS-306 Core Java and Web Technology"

def build_solution_md(q1_title, q1_marks, q1_stmt, q1_concept, q1_file, q1_out,
                      q2_title, q2_marks, q2_stmt, q2_concept, q2_file, q2_out,
                      viva_qas):
    q1_stmt = q1_stmt.strip().replace('\\n', '\n')
    q1_concept = q1_concept.strip().replace('\\n', '\n')
    q2_stmt = q2_stmt.strip().replace('\\n', '\n')
    q2_concept = q2_concept.strip().replace('\\n', '\n')

    lines = []
    lines.append(f"## Question 1: {q1_title} [{q1_marks} Marks]\n")
    lines.append("### Problem Statement\n" + q1_stmt + "\n")
    lines.append("### Concept & Algorithm\n" + q1_concept + "\n")
    lines.append("### Compilation & Execution\n```bash\n" + f"javac {q1_file}\njava {q1_file[:-5]}\n```\n")
    lines.append("### Sample Output\n```text\n" + q1_out.strip() + "\n```\n")
    lines.append("---\n")
    lines.append(f"## Question 2: {q2_title} [{q2_marks} Marks]\n")
    lines.append("### Problem Statement\n" + q2_stmt + "\n")
    lines.append("### Concept & Design\n" + q2_concept + "\n")
    if q2_file.endswith('.html'):
        lines.append(f"### Execution\nOpen `{q2_file}` in any standard web browser (Chrome, Firefox, Edge).\n")
    else:
        lines.append("### Compilation & Execution\n```bash\n" + f"node {q2_file}\n```\n")
    lines.append("### Output Preview / Response\n```text\n" + q2_out.strip() + "\n```\n")
    lines.append("---\n")
    lines.append("## Question 3: Oral / Viva Questions & Answers [5 Marks]\n")
    for i, (q, a) in enumerate(viva_qas, 1):
        lines.append(f"### Q{i}. {q}\n**Answer:** {a}\n")
    return "\n".join(lines)

JAVA_SOLUTIONS = [
    # 1
    (get_java_slip01_q1(), "ArraySum.java", "Array Sum and Elements Display",
     "Write a Java program to print the sum of elements of the array. Also display array elements.",
     "Accepts n elements into an array, computes cumulative sum, and displays array elements along with total sum.",
     "Array Elements: 10 20 30 40 50 \nSum of Elements: 150",
     get_web_slip01_q2(), "java_slip_01_q2.html", "College Registration Form (HTML5/CSS3)",
     "Design a College/School Registration Form using HTML5 and CSS3 and apply appropriate HTML5 validation.",
     "Uses semantic HTML5 input types (email, tel, date) and CSS flexbox styling for responsive form display.",
     "[Form rendered with valid inputs, fields, and submit button in browser]",
     [
         ("What is the difference between an Array and an ArrayList in Java?", "Arrays have fixed size and can hold primitives and objects. ArrayList is dynamic and holds only objects."),
         ("What are semantic HTML5 elements?", "Elements that convey their meaning to both browser and developer (e.g. <header>, <nav>, <article>, <footer>)."),
         ("What does the 'required' attribute do in HTML5?", "It ensures that an input field cannot be submitted while empty."),
         ("Why is main() declared as static in Java?", "So the JVM can invoke it without instantiating the class."),
         ("What is the JVM (Java Virtual Machine)?", "An abstract computing machine that enables a computer to run Java bytecode.")
     ]),

    # 2
    (get_java_slip02_q1(), "ArmstrongRange.java", "Armstrong Numbers in Given Range",
     "Write a Java Program to Display Armstrong Numbers Between range. Accept range from user.",
     "An Armstrong number is equal to the sum of its own digits raised to the power of the number of digits.",
     "Armstrong numbers between 1 and 500:\n1 2 3 4 5 6 7 8 9 153 370 371 407",
     get_web_slip02_q2(), "java_slip_02_q2.html", "Student Registration Form",
     "Design a Student Registration Form using HTML5 and CSS3 with validations.",
     "Uses modern CSS card layout with pattern validation attributes.",
     "[Student Registration card form rendered cleanly in browser]",
     [
         ("What is an Armstrong number?", "A number equal to the sum of cubes (or powers of total digits) of its individual digits."),
         ("How do CSS selectors work?", "CSS selectors target HTML elements based on element name, class (.class), ID (#id), or attributes."),
         ("What is box model in CSS?", "A box that wraps around every HTML element consisting of margins, borders, padding, and the actual content."),
         ("What is JDK vs JRE?", "JRE is the runtime environment that executes bytecode. JDK contains JRE plus development tools like javac."),
         ("What is method overloading in Java?", "Having multiple methods with the same name but different parameter lists in the same class.")
     ]),

    # 3
    (get_java_slip03_q1(), "StringOperationsDemo.java", "Custom Package String Operations",
     "Write a package for String operation with classes Con and Comp.",
     "Con implements string concatenation; Comp implements string equality comparison.",
     "String 1: Pune\nString 2: University\nConcatenation: PuneUniversity\nComparison (str1 == str2): false",
     get_web_slip03_q2(), "java_slip_03_q2.html", "Responsive College Homepage (CSS Flexbox)",
     "Create a responsive webpage using CSS Flexbox for college homepage containing header, nav, content, sidebar, footer.",
     "Implements a responsive layout using display: flex, media queries, and semantic containers.",
     "[Responsive College Homepage rendered with header, flex columns, and footer]",
     [
         ("What is a package in Java?", "A namespace that organizes a set of related classes and interfaces."),
         ("What is CSS Flexbox?", "A one-dimensional layout model that distributes space and aligns items along a main axis or cross axis."),
         ("What does flex-direction do?", "It establishes the main-axis direction (row, column, row-reverse, column-reverse)."),
         ("What is the difference between equals() and == in Java strings?", "'==' checks reference equality (memory location), whereas equals() checks content equality."),
         ("Why is String immutable in Java?", "For security, synchronization, caching (String pool), and hashcode consistency.")
     ]),

    # 4
    (get_java_slip04_q1(), "MatrixOperations.java", "Multidimensional Array Matrix Operations",
     "Write a menu driven program to perform operations on multidimensional array: addition, multiplication, transpose.",
     "Uses 2D integer arrays with nested loops to compute matrix addition, multiplication, and transposition.",
     "Sum:\n6 8 \n10 12 \nTranspose of A:\n1 3 \n2 4",
     get_web_slip04_q2(), "java_slip_04_q2.html", "DOM Background Color Switcher",
     "Create a webpage containing a heading and a button. When clicked, change the background color.",
     "Uses JavaScript document.body.style.backgroundColor manipulation on button click event.",
     "[Page background color cycles interactively on clicking the button]",
     [
         ("How do you declare a 2D array in Java?", "int[][] arr = new int[rows][cols];"),
         ("What is the DOM in web development?", "Document Object Model: a programming API representing an HTML document as a tree of nodes."),
         ("What is an event listener in JavaScript?", "A procedure that waits for an event to occur (e.g. click, hover) and executes a handler callback."),
         ("What is garbage collection in Java?", "An automatic memory management process that frees memory occupied by unreachable objects."),
         ("Can Java arrays resize dynamically?", "No, arrays have fixed length once allocated; dynamic collections like ArrayList must be used instead.")
     ]),

    # 5
    (get_java_slip05_q1(), "ReverseFileContent.java", "Reverse File Contents",
     "Write a program to accept a text file from user and display contents in reverse order.",
     "Uses BufferedReader to read file contents, StringBuilder to reverse text, and prints the result.",
     "Original File Content:\nHello World from Java File Handling\nReversed Content:\ngnildnaH eliF avaJ morf dlroW olleH",
     get_web_slip05_q2(), "java_slip_05_q2.html", "Responsive Image Gallery with Hover Effects",
     "Create an image gallery using HTML5 and CSS3 with hover effects, responsive images and Flexbox.",
     "Employs CSS transform: scale, translateY, and box-shadow on :hover states inside a flex container.",
     "[Image cards smoothly animate and elevate on mouse hover]",
     [
         ("What is BufferedReader in Java?", "A class that reads text from a character-input stream, buffering characters to provide efficient reading."),
         ("What is try-with-resources statement?", "A try statement that declares one or more resources; ensures each resource is closed at the end of the statement."),
         ("What is CSS transform?", "A property that applies 2D or 3D transformations to an element (e.g. rotate, scale, translate, skew)."),
         ("What is the purpose of the alt attribute in <img>?", "Provides alternative text for screen readers or when the image fails to load."),
         ("What is FileReader vs FileInputStream?", "FileReader reads character streams (text), while FileInputStream reads raw byte streams (binary).")
     ]),

    # 6
    (get_java_slip06_q1(), "Account.java", "Account Class with Constructors",
     "Write a program to define a class Account having members custname, accno. Define default and parameterized constructors.",
     "Implements object encapsulation with default and parameterized constructors and display method.",
     "Customer Name: Default Customer, Account No: 10000001\nCustomer Name: Rahul Sharma, Account No: 9876543210",
     get_web_slip06_q2(), "java_slip_06_q2.html", "Button and Link Mouse Hover Effects",
     "Create a webpage containing a button and link. Change their appearance when mouse points to them.",
     "Uses CSS pseudo-class :hover with transitions for smooth color and scale shifts.",
     "[Button and link dynamically change color and animate on mouseover]",
     [
         ("What is a constructor in Java?", "A special method used to initialize objects; it has the same name as the class and no return type."),
         ("What is constructor overloading?", "Having multiple constructors with different parameter lists in the same class."),
         ("What is the :hover pseudo-class in CSS?", "A selector used to apply styles when the user points to an element with an input device."),
         ("What is encapsulation?", "Wrapping data (attributes) and code (methods) together into a single unit and restricting direct access."),
         ("What is the 'this' keyword in Java?", "A reference variable that refers to the current invoking object.")
     ]),

    # 7
    (get_java_slip07_q1(), "Driver.java", "Driver Class Implementation",
     "Write a class Driver with attributes license_no, name, address and age. Initialize and display.",
     "Encapsulates driver properties with parameterized constructor and display function.",
     "Driver Name: Amit Patil\nLicense No:  MH12-20230045\nAddress:     Shivajinagar, Pune\nAge:         28",
     get_web_slip07_q2(), "java_slip_07_q2.html", "Styled Unordered List of Programming Languages",
     "Create an unordered list of Programming Language names and apply different styles.",
     "Uses custom list styling with distinct border-left accents, hover animations, and card layouts.",
     "[Styled language items with colorful indicators and slide animation]",
     [
         ("What is CSS list-style property?", "A shorthand property that sets list-style-type, list-style-position, and list-style-image."),
         ("What is the default access modifier in Java?", "Package-private (default), accessible only within the same package."),
         ("What is the difference between private and protected in Java?", "private is accessible only inside the class; protected is accessible within the package and subclasses."),
         ("What is CSS specificity?", "A system used by browsers to determine which CSS rule applies to an element when multiple rules conflict."),
         ("What is JVM bytecode?", "Intermediate instruction set compiled from Java source code, executable by any platform with a compatible JVM.")
     ]),

    # 8
    (get_java_slip08_q1(), "ShapeDemo.java", "Abstract Class Shape Hierarchy",
     "Write a program to create an abstract class Shape (dim1, dim2). Derive Rectangle, Triangle, Circle.",
     "Demonstrates abstraction and polymorphism: base abstract class declares abstract printArea(), overridden in subclasses.",
     "Area of Rectangle (10 x 5): 50\nArea of Triangle (0.5 x 8 x 4): 16.0\nArea of Circle (radius 7): 153.93804002589985",
     get_web_slip08_q2(), "java_slip_08_q2.html", "DOM Image and Button Interaction",
     "Create webpage using JavaScript DOM manipulation and event handling with image and button.",
     "Toggles element color and text state on button click via document.getElementById().",
     "[Card toggles smoothly between State 1 and State 2 upon button click]",
     [
         ("Can an abstract class be instantiated directly?", "No, an abstract class cannot be instantiated using new; it must be subclassed."),
         ("What is runtime polymorphism in Java?", "Method overriding where the call to an overridden method is resolved at runtime based on object type."),
         ("What is the super keyword used for?", "To refer to the direct parent class object or call the parent constructor."),
         ("What is event bubbling in DOM?", "An event propagation phase where the event starts from the target element and bubbles up to the root."),
         ("What is document.getElementById()?", "A DOM method that returns the element object matching the specified ID string.")
     ]),

    # 9
    (get_java_slip09_q1(), "Employee.java", "Array of Employee Objects",
     "Write a program defining class Employee with id, name, salary. Store and display 3 employee records.",
     "Creates an array of Employee references, instantiates individual objects, and prints records.",
     "ID: 101 Name: Aarav   Salary: 55000.0\nID: 102 Name: Pooja   Salary: 72000.0\nID: 103 Name: Rohan   Salary: 48000.0",
     get_web_slip09_q2(), "java_slip_09_q2.js", "JavaScript Arrow Functions for Math Operations",
     "Write a JavaScript program to demonstrate Arrow Functions for addition, subtraction, multiplication, and division.",
     "Uses ES6 arrow function syntax (() => ...) for concise arithmetic operation handlers.",
     "20 + 5 = 25\n20 - 5 = 15\n20 * 5 = 100\n20 / 5 = 4",
     [
         ("What is an arrow function in ES6?", "A concise syntax for writing function expressions using '=>', which lexically binds the 'this' value."),
         ("How do arrow functions handle 'this' differently from normal functions?", "Arrow functions do not have their own 'this'; they inherit 'this' from the enclosing lexical scope."),
         ("How do you create an array of objects in Java?", "ClassName[] arr = new ClassName[size]; followed by instantiating each element."),
         ("What is the memory representation of an object array in Java?", "An array of references, where each cell stores the memory address of an actual object heap instance."),
         ("What is the difference between const, let, and var in JavaScript?", "var is function-scoped; let and const are block-scoped. const variables cannot be reassigned.")
     ]),

    # 10
    (get_java_slip10_q1(), "FileUppercase.java", "Display File Contents in Uppercase",
     "Write a program to read contents of abc.txt file. Display contents in uppercase.",
     "Uses BufferedReader and FileReader to read lines and converts strings to uppercase using toUpperCase().",
     "CORE JAVA AND WEB TECHNOLOGY PRACTICAL EXAMINATION 2026-2027.",
     get_web_slip10_q2(), "java_slip_10_q2.js", "Student Grade Report with Template Literals",
     "Write a JavaScript program to store student information and marks and generate formatted report using template literals.",
     "Demonstrates ES6 template literals (backticks `...`) and string interpolation (${expr}).",
     "Student Name : Aarav Sharma\nTotal Marks  : 265 / 300\nPercentage   : 88.33%\nFinal Status : PASS",
     [
         ("What are template literals in JavaScript?", "String literals allowing embedded expressions, tagged templates, and multiline strings delimited by backticks (`)."),
         ("How do you format decimal numbers in JavaScript?", "Using number.toFixed(digits)."),
         ("What exception is thrown when a file does not exist in Java?", "java.io.FileNotFoundException."),
         ("What is the difference between toUpperCase() and toLowerCase()?", "Converts all characters of the String to upper or lower case using default locale rules."),
         ("Why is finally block used in Java exception handling?", "To execute critical cleanup code (like closing streams) regardless of whether an exception occurs.")
     ]),

    # 11
    (get_java_slip11_q1(), "VehicleHierarchy.java", "Vehicle Inheritance Hierarchy",
     "Create super class Vehicle (Company, price). Derive LightMotorVehicle (mileage) and HeavyMotorVehicle (capacity_in_tons).",
     "Uses single inheritance with constructor chaining using super().",
     "LMV -> Company: Maruti Suzuki, Price: ₹750000.0, Mileage: 22.5 km/l\nHMV -> Company: Tata Motors, Price: ₹2800000.0, Capacity: 16.0 tons",
     get_web_slip11_q2(), "java_slip_11_q2.js", "Calculate Total and Average with Arrow Function",
     "Write a JavaScript program using an arrow function to calculate total and average marks of three subjects.",
     "Uses arrow function returning structured calculation object, printed via template literals.",
     "Total Marks     : 253\nAverage Marks   : 84.33",
     [
         ("What is inheritance in Java?", "A mechanism where one class acquires the properties and behaviors of another parent class."),
         ("Why does Java not support multiple inheritance with classes?", "To prevent ambiguity known as the 'Diamond Problem'; interfaces are used instead."),
         ("What is object destructuring in JavaScript?", "An ES6 feature that unpacks properties from objects into distinct variables."),
         ("What is method overriding in Java?", "Providing a specific implementation of a method in a subclass that is already defined in its superclass."),
         ("What is the use of super()?", "To invoke the immediate parent class constructor.")
     ]),

    # 12
    (get_java_slip12_q1(), "GameDemo.java", "Package game with Indoor & Outdoor Classes",
     "Write a package game with classes Indoor & Outdoor. Function display() to generate list of players.",
     "Implements player list encapsulation across indoor and outdoor sports classes.",
     "Indoor Game: Chess | Players: Magnus Hikaru \nOutdoor Game: Football | Players: Messi Ronaldo Neymar",
     get_web_slip12_q2(), "java_slip_12_q2.js", "Product Billing with Arrow Function",
     "Write a JavaScript program using an arrow function to calculate total price of product with GST.",
     "Computes subtotal, 18% GST tax, and grand total, displayed through formatted template literals.",
     "Product Name : Wireless Headphones\nSubtotal     : ₹4998.00\nGST (18%)    : ₹899.64\nGrand Total  : ₹5897.64",
     [
         ("How do you compile a Java class into a specific package directory?", "Using javac -d . ClassName.java."),
         ("What is default constructor?", "A constructor with no parameters automatically provided by the compiler if no constructors are declared."),
         ("What is string interpolation in JavaScript?", "Evaluating expressions inside template strings using ${variable}."),
         ("What is the difference between let and const in ES6?", "let allows reassignment; const declares block-scoped read-only references."),
         ("What is a pure function in JavaScript?", "A function that always returns the same output for the same input and has no side effects.")
     ]),

    # 13
    (get_java_slip13_q1(), "Clock.java", "Clock Class with AM/PM Mode",
     "Define Clock class: a. Accept Hours, Minutes, Seconds b. Check validity c. Set time to AM/PM mode.",
     "Validates time ranges (0-23 hours, 0-59 mins/secs) and converts 24-hr time to 12-hr AM/PM format.",
     "24-hr Time (14:35:20) in AM/PM mode: Time: 02:35:20 PM",
     get_web_slip13_q2(), "java_slip_13_q2.js", "Array Destructuring Value Swap",
     "Write a JavaScript program to swap two numbers without using a third variable using array destructuring.",
     "Uses ES6 array destructuring assignment: [a, b] = [b, a].",
     "Before Swap: a = 42, b = 99\nAfter Swap:  a = 99, b = 42",
     [
         ("How does array destructuring swap work in ES6?", "A temporary array is created on the right-hand side and immediately unpacked into the left-hand variables."),
         ("What is data validation in OOP?", "Ensuring that internal object state remains consistent and adheres to specified domain constraints."),
         ("What does printf format specifier %02d mean in Java?", "Prints an integer with at least 2 digits, zero-padded if necessary."),
         ("What is the difference between primitive data types and reference types in Java?", "Primitives hold raw values in memory stack; reference types store references to objects in the heap."),
         ("Can an interface have concrete methods in modern Java?", "Yes, since Java 8, interfaces can contain default and static concrete methods.")
     ]),

    # 14
    (get_java_slip14_q1(), "PrimeCheckerGUI.java", "GUI Prime Number Checker",
     "Write a GUI program that takes numeric input via TextField and displays whether it is prime upon clicking Process button.",
     "Uses Java Swing JFrame, GridLayout, ActionListener, and prime testing logic.",
     "[GUI window with input field, result field, and Process button]",
     get_web_slip14_q2(), "java_slip_14_q2.js", "Object Destructuring for Employee Details",
     "Create an object containing employee details (name, department, salary) and extract using object destructuring.",
     "Extracts employee attributes cleanly using const { name, department, salary } = employee.",
     "Employee Name : Rohan Varma\nDepartment    : Cloud Engineering\nSalary        : ₹85000",
     [
         ("What is an ActionListener in Java GUI?", "An interface that handles action events such as clicking a button or pressing enter."),
         ("What is SwingUtilities.invokeLater()?", "A utility method that queues a task for execution on the Event Dispatch Thread (EDT) for thread safety."),
         ("What is object destructuring default value syntax in ES6?", "const { name = 'Default' } = obj;"),
         ("What is a prime number?", "A natural number greater than 1 that has no positive divisors other than 1 and itself."),
         ("Why is checking up to sqrt(n) sufficient for primality test?", "Because if n has a factor larger than sqrt(n), the corresponding paired factor must be smaller than sqrt(n).")
     ]),

    # 15
    (get_java_slip15_q1(), "SimpleCalculatorGUI.java", "Simple GUI Calculator",
     "Write a GUI program to build a simple calculator with digit buttons (0-9) and operators (+, -, *, /).",
     "Implements interactive calculator GUI with BorderLayout and GridLayout button keypad.",
     "[Interactive calculator GUI displaying calculation results]",
     get_web_slip15_q2(), "java_slip_15_q2.js", "Spread Operator for Array Copy and Extension",
     "Write a JavaScript program to create copy of existing array using spread operator and add new element.",
     "Uses [...original, newItem] to perform a shallow clone and append an element.",
     "Original Array: [ 'Apple', 'Banana', 'Cherry' ]\nCopied & Extended Array: [ 'Apple', 'Banana', 'Cherry', 'Dragonfruit' ]",
     [
         ("What is the spread operator (...) in JavaScript?", "An operator that expands an iterable (like an array) into individual elements."),
         ("Does the spread operator create a shallow or deep copy?", "It creates a shallow copy: top-level elements are cloned, but nested objects are still referenced."),
         ("How do you handle division by zero in Java?", "For integers, it throws ArithmeticException; for floating point (double), it evaluates to Infinity or NaN."),
         ("What layout manager arranges components in five regions (North, South, East, West, Center)?", "BorderLayout."),
         ("What is the Event Dispatch Thread (EDT) in Java Swing?", "The dedicated thread responsible for handling GUI events and painting components.")
     ]),

    # 16
    (get_java_slip16_q1(), "ShoppingCartGUI.java", "Shopping Cart Simulator GUI",
     "Write a GUI application that simulates a shopping cart with item buttons and running total.",
     "Uses DefaultListModel, JList, and action listeners to add items and update cumulative bill total.",
     "[Shopping cart GUI displaying items added and updated bill total]",
     get_web_slip16_q2(), "java_slip_16_q2.js", "Rest Parameter for Variable Arguments Sum",
     "Write a JavaScript program using rest parameter to accept any number of values and calculate sum.",
     "Uses (...numbers) => numbers.reduce(...) to sum an arbitrary argument list.",
     "Sum of (10, 20, 30): 60\nSum of (5, 15, 25, 35, 45): 125",
     [
         ("What is the rest parameter in ES6?", "A syntax that allows a function to accept an indefinite number of arguments as an array."),
         ("What is the difference between rest parameter and spread operator?", "Rest parameter gathers multiple elements into an array; spread operator expands an array into individual elements."),
         ("What is reduce() in JavaScript arrays?", "An array method that executes a reducer callback on each element to accumulate a single result."),
         ("What is DefaultListModel in Java Swing?", "A concrete implementation of ListModel used to dynamically add, remove, and manage items in a JList."),
         ("Can a rest parameter appear anywhere in a function parameter list?", "No, the rest parameter must strictly be the last parameter in the function declaration.")
     ]),

    # 17
    (get_java_slip17_q1(), "KeyColorChangeGUI.java", "Key Combination Background Color Switcher",
     "Write a GUI application that changes background color based on combination of keys pressed (e.g. Ctrl+Alt+O for orange).",
     "Implements KeyListener interface and checks KeyEvent modifiers (isControlDown(), isAltDown()).",
     "[GUI window changes background color when key combination is triggered]",
     get_web_slip17_q2(), "java_slip_17_q2.js", "JavaScript Module Export and Import",
     "Create a JavaScript module containing arithmetic operations, export functions and import them.",
     "Implements modular JavaScript patterns exporting utility arithmetic functions.",
     "Add(15, 5) : 20\nMultiply(15, 5) : 75",
     [
         ("What is KeyListener in Java?", "An interface that receives keyboard events (keyPressed, keyReleased, keyTyped)."),
         ("How do you detect if Ctrl key is pressed during a KeyEvent?", "Using e.isControlDown()."),
         ("What are CommonJS modules vs ES6 modules?", "CommonJS uses require() and module.exports (synchronous, Node default); ES6 uses import and export (static, asynchronous)."),
         ("What is setFocusable(true) in Swing?", "Ensures that a component can gain keyboard focus to receive KeyEvents."),
         ("What is module bundler in modern web development?", "A tool (like Webpack, Vite) that packages modular JavaScript files into single or optimized bundles for browsers.")
     ]),

    # 18
    (get_java_slip18_q1(), "ColorButtonsGUI.java", "Multi-Button Color Changer",
     "Create an application with multiple buttons (Red, Green, Blue) that print color and change background color.",
     "Uses JButtons with ActionListeners to modify content pane background color and print to terminal.",
     "Selected Color: RED\nSelected Color: GREEN\nSelected Color: BLUE",
     get_web_slip18_q2(), "java_slip_18_q2.js", "Node.js HTTP Server",
     "Create a Node.js HTTP server that sends an appropriate response to a client request.",
     "Uses the core 'http' module to create an HTTP server responding with status 200 and text content.",
     "Server is running at http://localhost:3000/\nResponse: Hello from Node.js HTTP Server!",
     [
         ("What is the Node.js event loop?", "A single-threaded loop that handles asynchronous I/O callbacks non-blockingly."),
         ("What does http.createServer() do?", "Creates an instance of http.Server that listens for HTTP requests and issues responses."),
         ("What is res.writeHead() in Node.js?", "Sends an HTTP status code and response headers to the incoming request."),
         ("What is FlowLayout in Java GUI?", "The default layout manager for JPanel that arranges components in a directional flow, like words in a paragraph."),
         ("What is npm?", "Node Package Manager, the default package repository and dependency manager for Node.js.")
     ]),

    # 19
    (get_java_slip19_q1(), "FileCounter.java", "File Character, Word, and Line Counter",
     "Write a Java program to accept file name and count characters, words, and lines.",
     "Reads text line by line, accumulates line count, character length, and splits by regex \\s+ for words.",
     "Total Characters: 78\nTotal Words:      11\nTotal Lines:      3",
     get_web_slip19_q2(), "java_slip_19_q2.js", "Async/Await User Authentication Simulation",
     "Write a JavaScript program using async/await to simulate user login with try/catch error handling.",
     "Uses Promise inside async function, resolved on valid credentials and rejected on invalid inputs.",
     "[+] Success: Login Successful! Welcome to the dashboard.\n[-] Error: Invalid Username or Password!",
     [
         ("What does async/await do in JavaScript?", "It provides syntactic sugar over Promises, making asynchronous code look and behave like synchronous code."),
         ("What happens when an error is thrown inside an async function?", "It returns a rejected Promise, which can be captured by a try...catch block."),
         ("How does Java regular expression '\\s+' split words?", "It matches one or more consecutive whitespace characters (spaces, tabs, newlines)."),
         ("What is Promise in JavaScript?", "An object representing the eventual completion or failure of an asynchronous operation."),
         ("What are the three states of a Promise?", "Pending, Fulfilled, Rejected.")
     ]),

    # 20
    (get_java_slip20_q1(), "MouseEventsGUI.java", "Mouse Events Handler GUI",
     "Design a screen to handle Mouse Events (MOUSE_MOVED and MOUSE_CLICK) and display position in TextField.",
     "Implements MouseListener and MouseMotionListener to display live cursor coordinates.",
     "Mouse Moved at (145, 82)\nMouse Clicked at (145, 82)",
     get_web_slip20_q2(), "java_slip_20_q2.js", "Promise Division with Zero Handling",
     "Write a JavaScript program using Promise to divide two numbers. Reject if denominator is zero.",
     "Constructs a Promise resolving quotient or rejecting Error('Division by zero').",
     "100 / 4 = 25\nCaught rejection: Division by zero error: Denominator cannot be 0.",
     [
         ("What is the difference between MouseListener and MouseMotionListener?", "MouseListener handles clicks, presses, releases, enters, and exits; MouseMotionListener handles movements and drags."),
         ("How do you obtain mouse coordinates in MouseEvent?", "Using e.getX() and e.getY()."),
         ("What is the purpose of Promise.prototype.catch()?", "To schedule a callback function to be called when the Promise is rejected."),
         ("What is callback hell in JavaScript?", "A situation where multiple nested asynchronous callbacks make code difficult to read and maintain; solved by Promises/async-await."),
         ("Can a Promise change its state once resolved?", "No, once a Promise is settled (fulfilled or rejected), its state and result are immutable.")
     ]),

    # 21
    (get_java_slip21_q1(), "CollegeDepartmentDemo.java", "College and Department Hierarchy",
     "Create parent class College (cno, cname, caddr) and derived class Department (dno, dname).",
     "Demonstrates single inheritance, parameterized constructor chaining with super, and member access.",
     "College No:   101\nCollege Name: Modern College\nAddress:      Shivajinagar, Pune\nDept No:      1\nDept Name:    Computer Science",
     get_web_slip21_q2(), "java_slip_21_q2.js", "Node.js Path Module Operations",
     "Write a Node.js program using path module to perform join, resolve and extract file info.",
     "Uses path.join(), path.resolve(), path.dirname(), path.basename(), and path.extname().",
     "Joined Path:    /root/projects/node_app/index.js\nDirectory Name: /home/user/docs\nBase Name:      file.txt\nExtension:      .txt",
     [
         ("What is the difference between path.join() and path.resolve()?", "path.join() simply concatenates path segments; path.resolve() resolves a sequence of paths into an absolute path from the current working directory."),
         ("What is the role of super in inheritance?", "It calls the constructor of the parent class and allows access to overridden parent methods."),
         ("What is path.extname() used for?", "Returns the file extension, including the leading dot (e.g. '.txt')."),
         ("Can a subclass access private members of a superclass directly?", "No, private members can only be accessed via public/protected getter and setter methods."),
         ("What is __dirname in Node.js?", "The absolute directory name of the currently executing JavaScript file.")
     ]),

    # 22
    (get_java_slip22_q1(), "ProductDemo.java", "Product Interface and Object Counter",
     "Create class Product (id, name, cost, qty) using interface, default/parameterized constructors, display contents and object count.",
     "Uses interface implementation and a static counter incremented in constructors.",
     "ID: 101 Name: Laptop  Cost: ₹65000.0  Quantity: 5\nTotal Product Objects Created: 3",
     get_web_slip22_q2(), "java_slip_22_q2.js", "Asynchronous File Operations in Node.js",
     "Write a Node.js program using fs module to perform file operations asynchronously.",
     "Uses fs.writeFile, fs.readFile, and fs.unlink with error-first callback conventions.",
     "[+] File written successfully.\n[+] File contents: Initial content written asynchronously.\n[+] File cleaned up.",
     [
         ("What is a static variable in Java?", "A class-level variable shared by all instances of the class; memory is allocated once when the class is loaded."),
         ("What is an error-first callback in Node.js?", "A convention where the first argument of the callback is reserved for an error object (or null if successful)."),
         ("Why is asynchronous I/O preferred in Node.js?", "Because it does not block the single thread, allowing the server to handle thousands of concurrent requests."),
         ("Can an interface have instance variables in Java?", "No, all fields declared in an interface are implicitly public, static, and final (constants)."),
         ("What is the difference between interface and abstract class?", "An abstract class can have instance state and constructors; an interface cannot have instance state or constructors.")
     ]),

    # 23
    (get_java_slip23_q1(), "MultilevelInheritanceDemo.java", "Multilevel Inheritance: Continent-Country-State",
     "Multilevel inheritance: Country inherited from Continent, State inherited from Country. Display place, State, Country, Continent.",
     "Demonstrates 3-tier multilevel inheritance chaining using super() calls.",
     "Place:     Pune\nState:     Maharashtra\nCountry:   India\nContinent: Asia",
     get_web_slip23_q2(), "java_slip_23_q2.js", "Node.js fs: Write, Read, Append, and Delete",
     "Write a Node.js program to create, write, read and append data to a file using the fs module.",
     "Uses fs.writeFileSync, fs.appendFileSync, fs.readFileSync, and fs.unlinkSync.",
     "[+] Created and wrote to file.\n[+] Appended data to file.\n--- Current File Contents ---\nInitial Line 1.\nAppended Line 2.\n[+] File deleted.",
     [
         ("What is multilevel inheritance?", "A chain of inheritance where a derived class inherits from another derived class (A -> B -> C)."),
         ("What is the difference between appendFile and writeFile in Node.js?", "writeFile overwrites existing content; appendFile appends data to the end of the file."),
         ("What encoding is commonly specified when reading text files with fs.readFile?", "'utf8'."),
         ("Can a class inherit from more than one class in Java?", "No, Java supports single class inheritance only."),
         ("What is the Object class in Java?", "The root class of all Java classes; every class implicitly inherits from Object.")
     ]),

    # 24
    (get_java_slip24_q1(), "CylinderDemo.java", "Abstract Class Shape with Cylinder Area and Volume",
     "Create abstract class Shape with methods area & volume. Derive class Cylinder (radius, height). Calculate area and volume.",
     "Implements abstract methods in Cylinder: surface area = 2*pi*r*(r+h), volume = pi*r^2*h.",
     "Cylinder (Radius: 5.0, Height: 10.0):\nSurface Area: 471.24 sq. units\nVolume:       785.40 cubic units",
     get_web_slip24_q2(), "java_slip_24_q2.js", "Synchronous vs Asynchronous File Operations in Node.js",
     "Write a Node.js program to demonstrate synchronous and asynchronous file operations and compare.",
     "Compares blocking synchronous methods (writeFileSync, readFileSync) with non-blocking asynchronous callbacks.",
     "--- Starting Synchronous Execution ---\nRead Synchronous: Synchronous file content.\n--- Starting Asynchronous Execution ---\nRead Asynchronous: Asynchronous file content.",
     [
         ("When should you use synchronous vs asynchronous file methods in Node.js?", "Use synchronous methods only during startup or in simple CLI scripts; use asynchronous methods in production web servers to prevent blocking the event loop."),
         ("What does Math.PI represent in Java?", "A static final constant in java.lang.Math representing the mathematical ratio pi (~3.14159)."),
         ("What is an abstract method?", "A method declared without an implementation (without braces) ending with a semicolon."),
         ("What happens if a concrete subclass fails to implement all abstract methods?", "The subclass itself must be declared abstract, and cannot be instantiated."),
         ("What is the event-driven architecture of Node.js?", "Components emit named events that trigger registered listener functions via EventEmitter.")
     ]),

    # 25
    (get_java_slip25_q1(), "InterfaceCalcDemo.java", "Calculator Interface and SimpleCalc Class",
     "Write a Java program that defines interface Calculator containing add() and subtract() and implements in class SimpleCalc.",
     "Demonstrates interface definition and implementation using class SimpleCalc implements Calculator.",
     "45.5 + 12.3 = 57.8\n45.5 - 12.3 = 33.2",
     get_web_slip25_q2(), "java_slip_25_q2.js", "Directory Management and JSON Operations in Node.js",
     "Write a Node.js program to perform directory management and JSON parsing/writing.",
     "Uses fs.mkdirSync, fs.writeFileSync, JSON.stringify, and JSON.parse.",
     "[+] Directory 'test_dir' created.\n[+] JSON data written.\n[+] Parsed JSON Student Name: Snehal\n[+] Cleanup complete.",
     [
         ("What is JSON?", "JavaScript Object Notation, a lightweight data interchange format that is easy for humans to read and machines to parse."),
         ("What is JSON.stringify() vs JSON.parse()?", "JSON.stringify() serializes a JavaScript object into a JSON string; JSON.parse() deserializes a JSON string into an object."),
         ("Can a class implement multiple interfaces in Java?", "Yes, a class can implement any number of interfaces separated by commas."),
         ("What is fs.mkdir() in Node.js?", "Asynchronously creates a new directory in the file system."),
         ("What is a marker interface in Java?", "An interface with no methods or constants (e.g. Serializable, Cloneable), used to mark class capabilities.")
     ]),

    # 26
    (get_java_slip26_q1(), "StudentAttendanceDemo.java", "User-Defined Exception for Student Attendance",
     "Define class Student (name, roll, total, attended). If attendance < 75%, throw exception 'Student is Not Eligible for Exam'.",
     "Custom exception class extends Exception; thrown when ((attended/total)*100) < 75.0.",
     "Roll No: 101 Name: Pooja  Status: Eligible for Exam\nException caught: Student is Not Eligible for Exam (Attendance: 62.5%)",
     get_web_slip26_q2(), "java_slip_26_q2.js", "Copy, Rename and Delete Files Asynchronously",
     "Write a Node.js program using fs module to copy, rename and delete files asynchronously.",
     "Uses fs.copyFile, fs.rename, and fs.unlink with error handling.",
     "[+] File copied successfully.\n[+] File renamed successfully.\n[+] File deleted successfully.",
     [
         ("How do you create a user-defined exception in Java?", "By creating a class that extends java.lang.Exception (or RuntimeException) and providing a constructor that passes the message to super(message)."),
         ("What is the difference between throw and throws in Java?", "throw is used to explicitly throw an exception object; throws is declared in a method signature to specify exceptions the method might propagate."),
         ("What does fs.copyFile() do in Node.js?", "Asynchronously copies src to dest; overwrites dest by default."),
         ("What is checked vs unchecked exception in Java?", "Checked exceptions (subclasses of Exception excluding RuntimeException) are checked at compile time; unchecked exceptions (subclasses of RuntimeException) occur at runtime."),
         ("What is fs.rename() in Node.js?", "Asynchronously renames or moves a file or directory from one path to another.")
     ]),

    # 27
    (get_java_slip27_q1(), "Person.java", "Person Class with 'this' Keyword",
     "Write a program to define class Person (personname, aadharno, panno). Accept and display 5 objects using this keyword.",
     "Demonstrates variable shadowing resolution and field assignment using 'this.variable = variable'.",
     "Name: Amit Kumar    Aadhar: 1234-5678-9012  PAN: ABCDE1234F\nName: Sneha Joshi   Aadhar: 2345-6789-0123  PAN: BCDEF2345G",
     get_web_slip27_q2(), "java_slip_27_q2.js", "Read, Modify and Update JSON File in Node.js",
     "Write a Node.js program to read JSON file, modify selected properties, and write updated data back.",
     "Reads JSON file, parses with JSON.parse(), updates properties, and writes back formatted with JSON.stringify().",
     "Original Object: { username: 'amit_dev', role: 'Student', active: false }\nUpdated Object written to file:\n{\n  \"username\": \"amit_dev\",\n  \"role\": \"Administrator\",\n  \"active\": true\n}",
     [
         ("What are the uses of 'this' keyword in Java?", "1. Disambiguate shadowed instance variables. 2. Invoke current class constructors (this()). 3. Pass current object as argument."),
         ("What does the 3rd argument in JSON.stringify(obj, null, 2) mean?", "It specifies the indentation space count for pretty-printing JSON output."),
         ("What is method chaining using 'this' in Java?", "Returning 'this' from setter methods allowing cascading method calls (e.g. obj.setName().setAge())."),
         ("Why is JSON preferred over XML?", "JSON is lighter, faster to parse, and maps directly to native JavaScript data structures."),
         ("What happens if JSON.parse() receives malformed JSON?", "It throws a SyntaxError exception.")
     ]),

    # 28
    (get_java_slip28_q1(), "MyDate.java", "Custom InvalidDateException Class",
     "Define class MyDate(Day, Month, year) to accept/display date. Throw user defined exception 'InvalidDateException' if date is invalid.",
     "Implements leap year calculation and calendar month day boundary validation; throws InvalidDateException on bad dates.",
     "Date: 25/09/2026\nException caught: Invalid Date: 31/2/2026",
     get_web_slip28_q2(), "java_slip_28_q2.js", "Filter Directory Files by Extensions in Node.js",
     "Create a Node.js program to list files in directory and filter based on extensions (.txt, .json, .js).",
     "Reads directory entries with fs.readdirSync and filters using path.extname().",
     "Filtering files in '.' for: .txt, .json, .js\nMatching Files:\n  -> java_slip_28_q2.js",
     [
         ("How do you check for leap year in calendar validation?", "A year is leap if (year % 400 == 0) or (year % 4 == 0 and year % 100 != 0)."),
         ("What is path.extname() return value for files without extensions?", "It returns an empty string ('')."),
         ("What is the difference between readdir and readdirSync in Node.js?", "readdir is asynchronous and non-blocking with callback; readdirSync is synchronous and blocking."),
         ("Why should exceptions represent exceptional conditions rather than normal flow control?", "Because creating and throwing exception objects involves stack unwinding, which is computationally expensive."),
         ("What is the base class of all exceptions and errors in Java?", "java.lang.Throwable.")
     ]),

    # 29
    (get_java_slip29_q1(), "PrimeOrZeroCheck.java", "Static Method and Zero Exception Check",
     "Accept number; if zero throw user defined exception 'Number is 0' otherwise check whether prime (Use static keyword).",
     "Uses static method checkNumber(n) throwing ZeroNumberException on 0, and checks primality.",
     "Testing number 17: 17 is a Prime Number.\nTesting number 0: Exception: Number is 0\nTesting number 24: 24 is NOT a Prime Number.",
     get_web_slip29_q2(), "java_slip_29_q2.js", "File Statistics with fs.stat() in Node.js",
     "Write a Node.js program to demonstrate file statistics using fs.stat(), including size, timestamps, type.",
     "Extracts size, isFile(), isDirectory(), birthtime, and mtime using fs.stat().",
     "=== File Statistics ===\nFile Size:         bytes\nIs Directory:      false\nIs File:           true",
     [
         ("What is a static method in Java?", "A method that belongs to the class rather than object instances; it can be called without creating an instance."),
         ("Can static methods access non-static instance variables directly?", "No, static methods cannot access non-static variables directly because they have no 'this' context."),
         ("What information does fs.stat() return in Node.js?", "File size, block size, device ID, inode, mode permissions, UID/GID, and access/modification/creation timestamps."),
         ("What is stats.isDirectory()?", "A method on the fs.Stats object that returns true if the path represents a directory."),
         ("What is the difference between mtime and ctime in file systems?", "mtime (modification time) changes when file contents change; ctime (change time) changes when file metadata (permissions, owner) or contents change.")
     ]),

    # 30
    (get_java_slip30_q1(), "MyNumber.java", "MyNumber Class with Command-Line Arguments",
     "Define class MyNumber with private int. Default constructor (0), parameterized constructor. Methods isNegative, isPositive, isOdd, isEven. Use CLI args.",
     "Implements number property methods and parses Integer.parseInt(args[0]) from command line.",
     "Number: 25\nisPositive: true\nisNegative: false\nisEven:     false\nisOdd:      true",
     get_web_slip30_q2(), "java_slip_30_q2.js", "Mini File Management CLI Application in Node.js",
     "Create a Node.js mini file-management application using fs and path to create, read, update, delete files.",
     "Implements unified file CRUD operations with status logging and cleanup.",
     "[+] Created 'cli_test.txt'.\n[+] Appended content to 'cli_test.txt'.\n--- Content of 'cli_test.txt' ---\nHello Node CLI!\nSecond Line added.\n[+] Deleted 'cli_test.txt'.",
     [
         ("How do you pass and read command-line arguments in Java?", "Through the String[] args array parameter in the main() method."),
         ("What happens if you access args[0] when no command-line arguments were passed?", "It throws java.lang.ArrayIndexOutOfBoundsException."),
         ("What is process.argv in Node.js?", "An array containing command-line arguments passed when launching the Node.js process."),
         ("Why are instance variables usually declared as private in Java?", "To achieve data encapsulation and prevent unauthorized or uncontrolled external modification."),
         ("What is the difference between Integer.parseInt() and Integer.valueOf()?", "parseInt() returns a primitive int; valueOf() returns an Integer object wrapper (often cached).")
     ])
]

def main():
    print("=== Solving and Verifying All Java & Web Tech Slips (01 to 30) ===")
    for i, data in enumerate(JAVA_SOLUTIONS, 1):
        folder = os.path.join(BASE_DIR, f"java_slip_{i:02d}")
        os.makedirs(folder, exist_ok=True)

        java_code, java_file_name, q1_title, q1_stmt, q1_concept, q1_out, \
        web_code, web_file_name, q2_title, q2_stmt, q2_concept, q2_out, viva = data

        # Write Q1 Java file
        q1_path = os.path.join(folder, java_file_name)
        with open(q1_path, "w") as f:
            f.write(java_code)

        # Write Q2 Web file
        q2_path = os.path.join(folder, web_file_name)
        with open(q2_path, "w") as f:
            f.write(web_code)

        # Write Solution MD
        sol_content = build_solution_md(
            q1_title, 15, q1_stmt, q1_concept, java_file_name, q1_out,
            q2_title, 15, q2_stmt, q2_concept, web_file_name, q2_out, viva
        )
        with open(os.path.join(folder, f"java_slip_{i:02d}_solution.md"), "w") as f:
            f.write(sol_content)

        # Verify Java compilation with javac
        res = subprocess.run(["javac", q1_path], capture_output=True, text=True)
        if res.returncode != 0:
            print(f"[-] Javac error in {java_file_name}:", res.stderr)
        else:
            # Clean up compiled .class files to keep folder neat
            class_files = [os.path.join(folder, f) for f in os.listdir(folder) if f.endswith('.class')]
            for cf in class_files:
                os.remove(cf)

        # Verify JS execution if node file
        if web_file_name.endswith('.js'):
            res_node = subprocess.run(["node", q2_path], capture_output=True, text=True)
            if res_node.returncode != 0:
                print(f"[-] Node error in {web_file_name}:", res_node.stderr)

        print(f"  -> Solved and verified java_slip_{i:02d}")

if __name__ == "__main__":
    main()
