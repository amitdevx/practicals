// Synchronous vs Asynchronous File Operations in Node.js
const fs = require('fs');

const syncFile = 'sync_test.txt';
const asyncFile = 'async_test.txt';

console.log('--- Starting Synchronous Execution ---');
fs.writeFileSync(syncFile, 'Synchronous file content.');
const syncData = fs.readFileSync(syncFile, 'utf8');
console.log('Read Synchronous:', syncData);
fs.unlinkSync(syncFile);
console.log('Synchronous operations completed (Blocking).\n');

console.log('--- Starting Asynchronous Execution ---');
fs.writeFile(asyncFile, 'Asynchronous file content.', () => {
    fs.readFile(asyncFile, 'utf8', (err, asyncData) => {
        console.log('Read Asynchronous:', asyncData);
        fs.unlinkSync(asyncFile);
        console.log('Asynchronous operations completed (Non-blocking).');
    });
});
