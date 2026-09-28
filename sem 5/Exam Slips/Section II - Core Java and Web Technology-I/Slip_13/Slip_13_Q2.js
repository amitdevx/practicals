// Swap two numbers without third variable using Array Destructuring
let a = 42;
let b = 99;

console.log(`Before Swap: a = ${a}, b = ${b}`);

// Destructuring assignment swap
[a, b] = [b, a];

console.log(`After Swap:  a = ${a}, b = ${b}`);
