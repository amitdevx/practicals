// ES6 Module Export / Import Demonstration
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
