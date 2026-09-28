// Rest Parameter to accept any number of values and calculate sum
const sumAll = (...numbers) => {
    return numbers.reduce((acc, curr) => acc + curr, 0);
};

console.log("Sum of (10, 20, 30):", sumAll(10, 20, 30));
console.log("Sum of (5, 15, 25, 35, 45):", sumAll(5, 15, 25, 35, 45));
console.log("Sum of empty list:", sumAll());
