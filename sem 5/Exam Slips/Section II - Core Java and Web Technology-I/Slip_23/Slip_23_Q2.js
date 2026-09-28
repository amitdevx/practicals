// Node.js fs: Create, Write, Read and Append Data
const fs = require('fs');

const file = 'crud_demo.txt';

fs.writeFileSync(file, 'Initial Line 1.\n');
console.log('[+] Created and wrote to file.');

fs.appendFileSync(file, 'Appended Line 2.\n');
console.log('[+] Appended data to file.');

const data = fs.readFileSync(file, 'utf8');
console.log('--- Current File Contents ---');
console.log(data);

fs.unlinkSync(file);
console.log('[+] File deleted.');
