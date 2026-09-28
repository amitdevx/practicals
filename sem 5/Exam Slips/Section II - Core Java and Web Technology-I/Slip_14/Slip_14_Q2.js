// Object Destructuring for Employee Details
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
