// Promise to Divide Two Numbers with Zero Handling
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
